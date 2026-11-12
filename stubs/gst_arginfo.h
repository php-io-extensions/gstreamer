/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: c6afa1b1ef97e7600a212e4bacffa00699e45b80 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_init_check, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(1, argv, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_version, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(1, major, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, minor, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, micro, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, nano, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_version_string, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_parse_launch, 0, 1, GstElement, 1)
	ZEND_ARG_TYPE_INFO(0, pipeline_description, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_pipeline_new, 0, 1, GstElement, 1)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_element_factory_make, 0, 2, GstElement, 1)
	ZEND_ARG_TYPE_INFO(0, factoryname, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_bin_add, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, bin, GstBin, 0)
	ZEND_ARG_OBJ_INFO(0, element, GstElement, 0)
ZEND_END_ARG_INFO()

#define arginfo_gst_bin_remove arginfo_gst_bin_add

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_bin_get_by_name, 0, 2, GstElement, 1)
	ZEND_ARG_OBJ_INFO(0, bin, GstBin, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_link, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, src, GstElement, 0)
	ZEND_ARG_OBJ_INFO(0, dest, GstElement, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_link_filtered, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, src, GstElement, 0)
	ZEND_ARG_OBJ_INFO(0, dest, GstElement, 0)
	ZEND_ARG_OBJ_INFO(0, filter, GstCaps, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_unlink, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, src, GstElement, 0)
	ZEND_ARG_OBJ_INFO(0, dest, GstElement, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_set_state, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, element, GstElement, 0)
	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_get_state, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, element, GstElement, 0)
	ZEND_ARG_TYPE_INFO(1, state, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, pending, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_element_get_bus, 0, 1, GstBus, 1)
	ZEND_ARG_OBJ_INFO(0, element, GstElement, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_seek_simple, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, element, GstElement, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, seek_flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, seek_pos, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_query_position, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, element, GstElement, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, cur, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_query_duration, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, element, GstElement, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, duration, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_state_get_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, state, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_element_state_change_return_get_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, state_ret, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(arginfo_gst_object_ref, 0, 1, GstObject|GstDiscoverer|GstDiscovererInfo|GstDiscovererStreamInfo, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, object, GstObject|GstDiscoverer|GstDiscovererInfo|GstDiscovererStreamInfo, 0, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_object_unref, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, object, GstObject|GstDiscoverer|GstDiscovererInfo|GstDiscovererStreamInfo, 0, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_object_get_name, 0, 1, IS_STRING, 1)
	ZEND_ARG_OBJ_INFO(0, object, GstObject, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_util_set_object_arg, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, object, GstObject|GstDiscoverer|GstDiscovererInfo|GstDiscovererStreamInfo, 0, NULL)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_bus_timed_pop_filtered, 0, 3, GstMessage, 1)
	ZEND_ARG_OBJ_INFO(0, bus, GstBus, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, types, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_message_unref, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, msg, GstMessage, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_message_type_get_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_message_parse_error, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, message, GstMessage, 0)
	ZEND_ARG_TYPE_INFO(1, debug, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_gst_message_parse_warning arginfo_gst_message_parse_error

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_message_parse_state_changed, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, message, GstMessage, 0)
	ZEND_ARG_TYPE_INFO(1, oldstate, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, newstate, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, pending, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_caps_from_string, 0, 1, GstCaps, 1)
	ZEND_ARG_TYPE_INFO(0, string, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_caps_to_string, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, caps, GstCaps, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_caps_unref, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, caps, GstCaps, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_caps_get_size, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, caps, GstCaps, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_caps_get_structure, 0, 2, GstStructure, 1)
	ZEND_ARG_OBJ_INFO(0, caps, GstCaps, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_structure_get_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, structure, GstStructure, 0)
ZEND_END_ARG_INFO()

#define arginfo_gst_structure_to_string arginfo_gst_structure_get_name

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_structure_get_int, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, structure, GstStructure, 0)
	ZEND_ARG_TYPE_INFO(0, fieldname, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(1, value, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_structure_get_fraction, 0, 4, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, structure, GstStructure, 0)
	ZEND_ARG_TYPE_INFO(0, fieldname, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(1, value_numerator, IS_LONG, 1)
	ZEND_ARG_TYPE_INFO(1, value_denominator, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_sample_get_buffer, 0, 1, GstBuffer, 1)
	ZEND_ARG_OBJ_INFO(0, sample, GstSample, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_gst_sample_get_caps, 0, 1, GstCaps, 1)
	ZEND_ARG_OBJ_INFO(0, sample, GstSample, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_sample_unref, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, sample, GstSample, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_buffer_get_size, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GstBuffer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_buffer_extract, 0, 4, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GstBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, dest, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_buffer_map, 0, 3, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GstBuffer, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstMapInfo, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_buffer_unmap, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GstBuffer, 0)
	ZEND_ARG_OBJ_INFO(0, info, GstMapInfo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_gst_format_get_name, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GstMapInfo___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GstObject___construct arginfo_class_GstMapInfo___construct

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GstObject_pointer, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GstObject_fromPointer, 0, 1, IS_STATIC, 1)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GstMessage___construct arginfo_class_GstMapInfo___construct

#define arginfo_class_GstMessage_pointer arginfo_class_GstObject_pointer

#define arginfo_class_GstMessage_fromPointer arginfo_class_GstObject_fromPointer

#define arginfo_class_GstMessage_type arginfo_class_GstObject_pointer

#define arginfo_class_GstMessage_timestamp arginfo_class_GstObject_pointer

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GstMessage_src, 0, 0, GstObject, 1)
ZEND_END_ARG_INFO()

#define arginfo_class_GstCaps___construct arginfo_class_GstMapInfo___construct

#define arginfo_class_GstCaps_pointer arginfo_class_GstObject_pointer

#define arginfo_class_GstCaps_fromPointer arginfo_class_GstObject_fromPointer

#define arginfo_class_GstStructure___construct arginfo_class_GstMapInfo___construct

#define arginfo_class_GstStructure_pointer arginfo_class_GstObject_pointer

#define arginfo_class_GstStructure_fromPointer arginfo_class_GstObject_fromPointer

#define arginfo_class_GstSample___construct arginfo_class_GstMapInfo___construct

#define arginfo_class_GstSample_pointer arginfo_class_GstObject_pointer

#define arginfo_class_GstSample_fromPointer arginfo_class_GstObject_fromPointer

#define arginfo_class_GstBuffer___construct arginfo_class_GstMapInfo___construct

#define arginfo_class_GstBuffer_pointer arginfo_class_GstObject_pointer

#define arginfo_class_GstBuffer_fromPointer arginfo_class_GstObject_fromPointer

#define arginfo_class_GstBuffer_pts arginfo_class_GstObject_pointer

#define arginfo_class_GstBuffer_dts arginfo_class_GstObject_pointer

#define arginfo_class_GstBuffer_duration arginfo_class_GstObject_pointer

#define arginfo_class_GstBuffer_offset arginfo_class_GstObject_pointer

ZEND_FUNCTION(gst_init_check);
ZEND_FUNCTION(gst_version);
ZEND_FUNCTION(gst_version_string);
ZEND_FUNCTION(gst_parse_launch);
ZEND_FUNCTION(gst_pipeline_new);
ZEND_FUNCTION(gst_element_factory_make);
ZEND_FUNCTION(gst_bin_add);
ZEND_FUNCTION(gst_bin_remove);
ZEND_FUNCTION(gst_bin_get_by_name);
ZEND_FUNCTION(gst_element_link);
ZEND_FUNCTION(gst_element_link_filtered);
ZEND_FUNCTION(gst_element_unlink);
ZEND_FUNCTION(gst_element_set_state);
ZEND_FUNCTION(gst_element_get_state);
ZEND_FUNCTION(gst_element_get_bus);
ZEND_FUNCTION(gst_element_seek_simple);
ZEND_FUNCTION(gst_element_query_position);
ZEND_FUNCTION(gst_element_query_duration);
ZEND_FUNCTION(gst_element_state_get_name);
ZEND_FUNCTION(gst_element_state_change_return_get_name);
ZEND_FUNCTION(gst_object_ref);
ZEND_FUNCTION(gst_object_unref);
ZEND_FUNCTION(gst_object_get_name);
ZEND_FUNCTION(gst_util_set_object_arg);
ZEND_FUNCTION(gst_bus_timed_pop_filtered);
ZEND_FUNCTION(gst_message_unref);
ZEND_FUNCTION(gst_message_type_get_name);
ZEND_FUNCTION(gst_message_parse_error);
ZEND_FUNCTION(gst_message_parse_warning);
ZEND_FUNCTION(gst_message_parse_state_changed);
ZEND_FUNCTION(gst_caps_from_string);
ZEND_FUNCTION(gst_caps_to_string);
ZEND_FUNCTION(gst_caps_unref);
ZEND_FUNCTION(gst_caps_get_size);
ZEND_FUNCTION(gst_caps_get_structure);
ZEND_FUNCTION(gst_structure_get_name);
ZEND_FUNCTION(gst_structure_to_string);
ZEND_FUNCTION(gst_structure_get_int);
ZEND_FUNCTION(gst_structure_get_fraction);
ZEND_FUNCTION(gst_sample_get_buffer);
ZEND_FUNCTION(gst_sample_get_caps);
ZEND_FUNCTION(gst_sample_unref);
ZEND_FUNCTION(gst_buffer_get_size);
ZEND_FUNCTION(gst_buffer_extract);
ZEND_FUNCTION(gst_buffer_map);
ZEND_FUNCTION(gst_buffer_unmap);
ZEND_FUNCTION(gst_format_get_name);
ZEND_METHOD(GstMapInfo, __construct);
ZEND_METHOD(GstObject, __construct);
ZEND_METHOD(GstObject, pointer);
ZEND_METHOD(GstObject, fromPointer);
ZEND_METHOD(GstMessage, __construct);
ZEND_METHOD(GstMessage, pointer);
ZEND_METHOD(GstMessage, fromPointer);
ZEND_METHOD(GstMessage, type);
ZEND_METHOD(GstMessage, timestamp);
ZEND_METHOD(GstMessage, src);
ZEND_METHOD(GstCaps, __construct);
ZEND_METHOD(GstCaps, pointer);
ZEND_METHOD(GstCaps, fromPointer);
ZEND_METHOD(GstStructure, __construct);
ZEND_METHOD(GstStructure, pointer);
ZEND_METHOD(GstStructure, fromPointer);
ZEND_METHOD(GstSample, __construct);
ZEND_METHOD(GstSample, pointer);
ZEND_METHOD(GstSample, fromPointer);
ZEND_METHOD(GstBuffer, __construct);
ZEND_METHOD(GstBuffer, pointer);
ZEND_METHOD(GstBuffer, fromPointer);
ZEND_METHOD(GstBuffer, pts);
ZEND_METHOD(GstBuffer, dts);
ZEND_METHOD(GstBuffer, duration);
ZEND_METHOD(GstBuffer, offset);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(gst_init_check, arginfo_gst_init_check)
	ZEND_FE(gst_version, arginfo_gst_version)
	ZEND_FE(gst_version_string, arginfo_gst_version_string)
	ZEND_FE(gst_parse_launch, arginfo_gst_parse_launch)
	ZEND_FE(gst_pipeline_new, arginfo_gst_pipeline_new)
	ZEND_FE(gst_element_factory_make, arginfo_gst_element_factory_make)
	ZEND_FE(gst_bin_add, arginfo_gst_bin_add)
	ZEND_FE(gst_bin_remove, arginfo_gst_bin_remove)
	ZEND_FE(gst_bin_get_by_name, arginfo_gst_bin_get_by_name)
	ZEND_FE(gst_element_link, arginfo_gst_element_link)
	ZEND_FE(gst_element_link_filtered, arginfo_gst_element_link_filtered)
	ZEND_FE(gst_element_unlink, arginfo_gst_element_unlink)
	ZEND_FE(gst_element_set_state, arginfo_gst_element_set_state)
	ZEND_FE(gst_element_get_state, arginfo_gst_element_get_state)
	ZEND_FE(gst_element_get_bus, arginfo_gst_element_get_bus)
	ZEND_FE(gst_element_seek_simple, arginfo_gst_element_seek_simple)
	ZEND_FE(gst_element_query_position, arginfo_gst_element_query_position)
	ZEND_FE(gst_element_query_duration, arginfo_gst_element_query_duration)
	ZEND_FE(gst_element_state_get_name, arginfo_gst_element_state_get_name)
	ZEND_FE(gst_element_state_change_return_get_name, arginfo_gst_element_state_change_return_get_name)
	ZEND_FE(gst_object_ref, arginfo_gst_object_ref)
	ZEND_FE(gst_object_unref, arginfo_gst_object_unref)
	ZEND_FE(gst_object_get_name, arginfo_gst_object_get_name)
	ZEND_FE(gst_util_set_object_arg, arginfo_gst_util_set_object_arg)
	ZEND_FE(gst_bus_timed_pop_filtered, arginfo_gst_bus_timed_pop_filtered)
	ZEND_FE(gst_message_unref, arginfo_gst_message_unref)
	ZEND_FE(gst_message_type_get_name, arginfo_gst_message_type_get_name)
	ZEND_FE(gst_message_parse_error, arginfo_gst_message_parse_error)
	ZEND_FE(gst_message_parse_warning, arginfo_gst_message_parse_warning)
	ZEND_FE(gst_message_parse_state_changed, arginfo_gst_message_parse_state_changed)
	ZEND_FE(gst_caps_from_string, arginfo_gst_caps_from_string)
	ZEND_FE(gst_caps_to_string, arginfo_gst_caps_to_string)
	ZEND_FE(gst_caps_unref, arginfo_gst_caps_unref)
	ZEND_FE(gst_caps_get_size, arginfo_gst_caps_get_size)
	ZEND_FE(gst_caps_get_structure, arginfo_gst_caps_get_structure)
	ZEND_FE(gst_structure_get_name, arginfo_gst_structure_get_name)
	ZEND_FE(gst_structure_to_string, arginfo_gst_structure_to_string)
	ZEND_FE(gst_structure_get_int, arginfo_gst_structure_get_int)
	ZEND_FE(gst_structure_get_fraction, arginfo_gst_structure_get_fraction)
	ZEND_FE(gst_sample_get_buffer, arginfo_gst_sample_get_buffer)
	ZEND_FE(gst_sample_get_caps, arginfo_gst_sample_get_caps)
	ZEND_FE(gst_sample_unref, arginfo_gst_sample_unref)
	ZEND_FE(gst_buffer_get_size, arginfo_gst_buffer_get_size)
	ZEND_FE(gst_buffer_extract, arginfo_gst_buffer_extract)
	ZEND_FE(gst_buffer_map, arginfo_gst_buffer_map)
	ZEND_FE(gst_buffer_unmap, arginfo_gst_buffer_unmap)
	ZEND_FE(gst_format_get_name, arginfo_gst_format_get_name)
	ZEND_FE_END
};

static const zend_function_entry class_GstMapInfo_methods[] = {
	ZEND_ME(GstMapInfo, __construct, arginfo_class_GstMapInfo___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_GstObject_methods[] = {
	ZEND_ME(GstObject, __construct, arginfo_class_GstObject___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstObject, pointer, arginfo_class_GstObject_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstObject, fromPointer, arginfo_class_GstObject_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_GstMessage_methods[] = {
	ZEND_ME(GstMessage, __construct, arginfo_class_GstMessage___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstMessage, pointer, arginfo_class_GstMessage_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstMessage, fromPointer, arginfo_class_GstMessage_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GstMessage, type, arginfo_class_GstMessage_type, ZEND_ACC_PUBLIC)
	ZEND_ME(GstMessage, timestamp, arginfo_class_GstMessage_timestamp, ZEND_ACC_PUBLIC)
	ZEND_ME(GstMessage, src, arginfo_class_GstMessage_src, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_GstCaps_methods[] = {
	ZEND_ME(GstCaps, __construct, arginfo_class_GstCaps___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstCaps, pointer, arginfo_class_GstCaps_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstCaps, fromPointer, arginfo_class_GstCaps_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_GstStructure_methods[] = {
	ZEND_ME(GstStructure, __construct, arginfo_class_GstStructure___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstStructure, pointer, arginfo_class_GstStructure_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstStructure, fromPointer, arginfo_class_GstStructure_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_GstSample_methods[] = {
	ZEND_ME(GstSample, __construct, arginfo_class_GstSample___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstSample, pointer, arginfo_class_GstSample_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstSample, fromPointer, arginfo_class_GstSample_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_GstBuffer_methods[] = {
	ZEND_ME(GstBuffer, __construct, arginfo_class_GstBuffer___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(GstBuffer, pointer, arginfo_class_GstBuffer_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(GstBuffer, fromPointer, arginfo_class_GstBuffer_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GstBuffer, pts, arginfo_class_GstBuffer_pts, ZEND_ACC_PUBLIC)
	ZEND_ME(GstBuffer, dts, arginfo_class_GstBuffer_dts, ZEND_ACC_PUBLIC)
	ZEND_ME(GstBuffer, duration, arginfo_class_GstBuffer_duration, ZEND_ACC_PUBLIC)
	ZEND_ME(GstBuffer, offset, arginfo_class_GstBuffer_offset, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static void register_gst_symbols(int module_number)
{
	REGISTER_LONG_CONSTANT("GST_VERSION_MAJOR", GST_VERSION_MAJOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_VERSION_MINOR", GST_VERSION_MINOR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_VERSION_MICRO", GST_VERSION_MICRO, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_VERSION_NANO", GST_VERSION_NANO, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_CLOCK_TIME_NONE", GST_CLOCK_TIME_NONE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SECOND", GST_SECOND, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MSECOND", GST_MSECOND, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_USECOND", GST_USECOND, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_NSECOND", GST_NSECOND, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_VOID_PENDING", GST_STATE_VOID_PENDING, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_NULL", GST_STATE_NULL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_READY", GST_STATE_READY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_PAUSED", GST_STATE_PAUSED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_PLAYING", GST_STATE_PLAYING, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_CHANGE_FAILURE", GST_STATE_CHANGE_FAILURE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_CHANGE_SUCCESS", GST_STATE_CHANGE_SUCCESS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_CHANGE_ASYNC", GST_STATE_CHANGE_ASYNC, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_STATE_CHANGE_NO_PREROLL", GST_STATE_CHANGE_NO_PREROLL, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_UNKNOWN", GST_MESSAGE_UNKNOWN, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_EOS", GST_MESSAGE_EOS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_ERROR", GST_MESSAGE_ERROR, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_WARNING", GST_MESSAGE_WARNING, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_INFO", GST_MESSAGE_INFO, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_TAG", GST_MESSAGE_TAG, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_BUFFERING", GST_MESSAGE_BUFFERING, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STATE_CHANGED", GST_MESSAGE_STATE_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STATE_DIRTY", GST_MESSAGE_STATE_DIRTY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STEP_DONE", GST_MESSAGE_STEP_DONE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_CLOCK_PROVIDE", GST_MESSAGE_CLOCK_PROVIDE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_CLOCK_LOST", GST_MESSAGE_CLOCK_LOST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_NEW_CLOCK", GST_MESSAGE_NEW_CLOCK, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STRUCTURE_CHANGE", GST_MESSAGE_STRUCTURE_CHANGE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STREAM_STATUS", GST_MESSAGE_STREAM_STATUS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_APPLICATION", GST_MESSAGE_APPLICATION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_ELEMENT", GST_MESSAGE_ELEMENT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_SEGMENT_START", GST_MESSAGE_SEGMENT_START, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_SEGMENT_DONE", GST_MESSAGE_SEGMENT_DONE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_DURATION_CHANGED", GST_MESSAGE_DURATION_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_LATENCY", GST_MESSAGE_LATENCY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_ASYNC_START", GST_MESSAGE_ASYNC_START, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_ASYNC_DONE", GST_MESSAGE_ASYNC_DONE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_REQUEST_STATE", GST_MESSAGE_REQUEST_STATE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STEP_START", GST_MESSAGE_STEP_START, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_QOS", GST_MESSAGE_QOS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_PROGRESS", GST_MESSAGE_PROGRESS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_TOC", GST_MESSAGE_TOC, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_RESET_TIME", GST_MESSAGE_RESET_TIME, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STREAM_START", GST_MESSAGE_STREAM_START, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_NEED_CONTEXT", GST_MESSAGE_NEED_CONTEXT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_HAVE_CONTEXT", GST_MESSAGE_HAVE_CONTEXT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_EXTENDED", GST_MESSAGE_EXTENDED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_DEVICE_ADDED", GST_MESSAGE_DEVICE_ADDED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_DEVICE_REMOVED", GST_MESSAGE_DEVICE_REMOVED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_PROPERTY_NOTIFY", GST_MESSAGE_PROPERTY_NOTIFY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STREAM_COLLECTION", GST_MESSAGE_STREAM_COLLECTION, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_STREAMS_SELECTED", GST_MESSAGE_STREAMS_SELECTED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_REDIRECT", GST_MESSAGE_REDIRECT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_DEVICE_CHANGED", GST_MESSAGE_DEVICE_CHANGED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_INSTANT_RATE_REQUEST", GST_MESSAGE_INSTANT_RATE_REQUEST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MESSAGE_ANY", GST_MESSAGE_ANY, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_FORMAT_UNDEFINED", GST_FORMAT_UNDEFINED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_FORMAT_DEFAULT", GST_FORMAT_DEFAULT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_FORMAT_BYTES", GST_FORMAT_BYTES, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_FORMAT_TIME", GST_FORMAT_TIME, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_FORMAT_BUFFERS", GST_FORMAT_BUFFERS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_FORMAT_PERCENT", GST_FORMAT_PERCENT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_NONE", GST_SEEK_FLAG_NONE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_FLUSH", GST_SEEK_FLAG_FLUSH, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_ACCURATE", GST_SEEK_FLAG_ACCURATE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_KEY_UNIT", GST_SEEK_FLAG_KEY_UNIT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_SEGMENT", GST_SEEK_FLAG_SEGMENT, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_TRICKMODE", GST_SEEK_FLAG_TRICKMODE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_SKIP", GST_SEEK_FLAG_SKIP, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_SNAP_BEFORE", GST_SEEK_FLAG_SNAP_BEFORE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_SNAP_AFTER", GST_SEEK_FLAG_SNAP_AFTER, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_SNAP_NEAREST", GST_SEEK_FLAG_SNAP_NEAREST, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_TRICKMODE_KEY_UNITS", GST_SEEK_FLAG_TRICKMODE_KEY_UNITS, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_TRICKMODE_NO_AUDIO", GST_SEEK_FLAG_TRICKMODE_NO_AUDIO, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_TRICKMODE_FORWARD_PREDICTED", GST_SEEK_FLAG_TRICKMODE_FORWARD_PREDICTED, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_SEEK_FLAG_INSTANT_RATE_CHANGE", GST_SEEK_FLAG_INSTANT_RATE_CHANGE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MAP_READ", GST_MAP_READ, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MAP_WRITE", GST_MAP_WRITE, CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GST_MAP_FLAG_LAST", GST_MAP_FLAG_LAST, CONST_PERSISTENT);
}

static zend_class_entry *register_class_GstError(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstError", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_RuntimeException, 0);

	zval property_domain_default_value;
	ZVAL_UNDEF(&property_domain_default_value);
	zend_string *property_domain_name = zend_string_init("domain", sizeof("domain") - 1, 1);
	zend_declare_typed_property(class_entry, property_domain_name, &property_domain_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
	zend_string_release(property_domain_name);

	return class_entry;
}

static zend_class_entry *register_class_GstMapInfo(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstMapInfo", class_GstMapInfo_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_flags_default_value;
	ZVAL_LONG(&property_flags_default_value, 0);
	zend_string *property_flags_name = zend_string_init("flags", sizeof("flags") - 1, 1);
	zend_declare_typed_property(class_entry, property_flags_name, &property_flags_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_flags_name);

	zval property_data_default_value;
	ZVAL_EMPTY_STRING(&property_data_default_value);
	zend_string *property_data_name = zend_string_init("data", sizeof("data") - 1, 1);
	zend_declare_typed_property(class_entry, property_data_name, &property_data_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
	zend_string_release(property_data_name);

	zval property_size_default_value;
	ZVAL_LONG(&property_size_default_value, 0);
	zend_string *property_size_name = zend_string_init("size", sizeof("size") - 1, 1);
	zend_declare_typed_property(class_entry, property_size_name, &property_size_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_size_name);

	zval property_maxsize_default_value;
	ZVAL_LONG(&property_maxsize_default_value, 0);
	zend_string *property_maxsize_name = zend_string_init("maxsize", sizeof("maxsize") - 1, 1);
	zend_declare_typed_property(class_entry, property_maxsize_name, &property_maxsize_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_maxsize_name);

	return class_entry;
}

static zend_class_entry *register_class_GstObject(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstObject", class_GstObject_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstElement(zend_class_entry *class_entry_GstObject)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstElement", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_GstObject, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstBin(zend_class_entry *class_entry_GstElement)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstBin", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_GstElement, ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstPipeline(zend_class_entry *class_entry_GstBin)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstPipeline", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_GstBin, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstBus(zend_class_entry *class_entry_GstObject)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstBus", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_GstObject, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstMessage(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstMessage", class_GstMessage_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstCaps(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstCaps", class_GstCaps_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstStructure(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstStructure", class_GstStructure_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstSample(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstSample", class_GstSample_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_GstBuffer(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "GstBuffer", class_GstBuffer_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}
