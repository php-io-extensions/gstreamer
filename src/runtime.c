#include "runtime.h"

static zend_object_handlers gstreamer_handle_handlers;
static zend_object_handlers gstreamer_map_handlers;

static zend_object *gstreamer_create_object(zend_class_entry *ce)
{
	gstreamer_handle *intern = zend_object_alloc(sizeof(gstreamer_handle), ce);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = &gstreamer_handle_handlers;
	intern->ptr = NULL;
	intern->refs = 0;

	return &intern->std;
}

/* Dropping the PHP object does not unref the native object: only the binding's *_unref and *_free functions do. */
static void gstreamer_free_object(zend_object *object)
{
	gstreamer_handle *intern = gstreamer_handle_from(object);

	if (intern->ptr != NULL) {
		zend_hash_index_del(&GSTREAMER_G(boxes), (zend_ulong) (uintptr_t) intern->ptr);
		intern->ptr = NULL;
	}
	zend_object_std_dtor(object);
}

void gstreamer_handle_setup(zend_class_entry *ce)
{
	static bool handlers_ready = false;

	if (!handlers_ready) {
		memcpy(&gstreamer_handle_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
		gstreamer_handle_handlers.offset = XtOffsetOf(gstreamer_handle, std);
		gstreamer_handle_handlers.free_obj = gstreamer_free_object;
		gstreamer_handle_handlers.clone_obj = NULL;
		handlers_ready = true;
	}

	ce->create_object = gstreamer_create_object;
	ce->default_object_handlers = &gstreamer_handle_handlers;
}

static zend_object *gstreamer_map_create(zend_class_entry *ce)
{
	gstreamer_map *intern = zend_object_alloc(sizeof(gstreamer_map), ce);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = &gstreamer_map_handlers;
	memset(&intern->info, 0, sizeof(intern->info));
	intern->buffer = NULL;

	return &intern->std;
}

/* Dropping a mapped GstMapInfo does not unmap: only gst_buffer_unmap() does, as in C. */
void gstreamer_map_setup(zend_class_entry *ce)
{
	memcpy(&gstreamer_map_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	gstreamer_map_handlers.offset = XtOffsetOf(gstreamer_map, std);
	gstreamer_map_handlers.clone_obj = NULL;

	ce->create_object = gstreamer_map_create;
	ce->default_object_handlers = &gstreamer_map_handlers;
}

void gstreamer_release(zend_object *obj)
{
	gstreamer_handle *intern = gstreamer_handle_from(obj);

	if (intern->ptr != NULL) {
		zend_hash_index_del(&GSTREAMER_G(boxes), (zend_ulong) (uintptr_t) intern->ptr);
		intern->ptr = NULL;
	}
	intern->refs = 0;
}

void gstreamer_ref(zend_object *obj)
{
	gstreamer_handle_from(obj)->refs++;
}

void gstreamer_unref(zend_object *obj)
{
	gstreamer_handle *intern = gstreamer_handle_from(obj);

	if (intern->refs <= 1) {
		gstreamer_release(obj);
		return;
	}
	intern->refs--;
}

bool gstreamer_gobject_arg(zend_object *arg, uint32_t arg_num)
{
	if (instanceof_function(arg->ce, gstreamer_ce_GstObject)
		|| instanceof_function(arg->ce, gstreamer_ce_GstDiscoverer)
		|| instanceof_function(arg->ce, gstreamer_ce_GstDiscovererInfo)
		|| instanceof_function(arg->ce, gstreamer_ce_GstDiscovererStreamInfo)) {
		return true;
	}
	zend_argument_type_error(arg_num, "must be of type GstObject|GstDiscoverer|GstDiscovererInfo|GstDiscovererStreamInfo, %s given", ZSTR_VAL(arg->ce->name));
	return false;
}

void gstreamer_disown(zend_object *obj)
{
	gstreamer_handle *intern = gstreamer_handle_from(obj);

	if (intern->refs > 0) {
		intern->refs--;
	}
}

void gstreamer_box(zval *rv, void *ptr, zend_class_entry *ce)
{
	zend_object *existing;

	if (ptr == NULL) {
		ZVAL_NULL(rv);
		return;
	}

	existing = zend_hash_index_find_ptr(&GSTREAMER_G(boxes), (zend_ulong) (uintptr_t) ptr);
	if (existing != NULL && instanceof_function(existing->ce, ce)) {
		ZVAL_OBJ_COPY(rv, existing);
		return;
	}
	if (existing != NULL) {
		/* Another class boxed this address. Detach it so its free_obj cannot drop the new entry. */
		gstreamer_handle_from(existing)->ptr = NULL;
	}

	object_init_ex(rv, ce);
	gstreamer_handle_from(Z_OBJ_P(rv))->ptr = ptr;
	zend_hash_index_update_ptr(&GSTREAMER_G(boxes), (zend_ulong) (uintptr_t) ptr, Z_OBJ_P(rv));
}

/* Most derived first: the first type the object is gives its class. */
static const struct {
	GType (*type)(void);
	zend_class_entry **ce;
} gstreamer_gtypes[] = {
	{gst_pipeline_get_type, &gstreamer_ce_GstPipeline},
	{gst_bin_get_type, &gstreamer_ce_GstBin},
	{gst_app_sink_get_type, &gstreamer_ce_GstAppSink},
	{gst_element_get_type, &gstreamer_ce_GstElement},
	{gst_bus_get_type, &gstreamer_ce_GstBus},
	{gst_object_get_type, &gstreamer_ce_GstObject},
	{gst_discoverer_get_type, &gstreamer_ce_GstDiscoverer},
	{gst_discoverer_info_get_type, &gstreamer_ce_GstDiscovererInfo},
	{gst_discoverer_video_info_get_type, &gstreamer_ce_GstDiscovererVideoInfo},
	{gst_discoverer_audio_info_get_type, &gstreamer_ce_GstDiscovererAudioInfo},
	{gst_discoverer_stream_info_get_type, &gstreamer_ce_GstDiscovererStreamInfo},
};

void gstreamer_box_gobject(zval *rv, gpointer object)
{
	size_t i;

	if (object == NULL) {
		ZVAL_NULL(rv);
		return;
	}
	for (i = 0; i < sizeof(gstreamer_gtypes) / sizeof(gstreamer_gtypes[0]); i++) {
		if (G_TYPE_CHECK_INSTANCE_TYPE(object, gstreamer_gtypes[i].type())) {
			gstreamer_box(rv, object, *gstreamer_gtypes[i].ce);
			return;
		}
	}
	/* The table ends with GstObject and GstDiscovererStreamInfo: every object a bound function or field returns is one of them. */
	ZVAL_NULL(rv);
}

void gstreamer_throw_gerror(const GError *error)
{
	const char *domain = g_quark_to_string(error->domain);
	zval exception;

	if (EG(exception) != NULL) {
		return;
	}

	object_init_ex(&exception, gstreamer_ce_GstError);
	zend_update_property_string(gstreamer_ce_GstError, Z_OBJ(exception), ZEND_STRL("message"), error->message != NULL ? error->message : "");
	zend_update_property_long(gstreamer_ce_GstError, Z_OBJ(exception), ZEND_STRL("code"), error->code);
	zend_update_property_string(gstreamer_ce_GstError, Z_OBJ(exception), ZEND_STRL("domain"), domain != NULL ? domain : "");
	zend_throw_exception_object(&exception);
}

#ifdef GSTREAMER_PROBES
bool gstreamer_probe_off(const char *id)
{
	const char *off = getenv("GSTREAMER_PROBE_OFF");

	return off != NULL && strcmp(off, id) == 0;
}
#endif
