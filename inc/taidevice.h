/**
 * Copyright (c) 2017 Nippon Telegraph and Telephone Corporation.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABILITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 * @file    taidevice.h
 *
 * @brief   This module defines TAI optical terminal module interface
 */

#ifndef __TAI_DEVICE_H__
#define __TAI_DEVICE_H__

#include <saitypes.h>

/**
 * @brief Attribute Id in tai_set_device_attribute() and
 * tai_get_device_attribute() calls
 */
typedef enum _tai_device_attr_t
{
    /**
     * @brief Start of attributes
     */
    TAI_DEVICE_ATTR_START,

    /**
     * @brief The number of optical modules on the device 
     *
     * @type sai_uint32_t
     * @flags READ_ONLY
     */
    TAI_DEVICE_ATTR_OPTICAL_MODULE_NUMBER = TAI_DEVICE_ATTR_START,

    /**
     * @brief Get the optical module list
     *
     * @type sai_object_list_t
     * @flags READ_ONLY
     * @objects SAI_OBJECT_TYPE_PORT
     * @default internal
     */
    TAI_DEVICE_ATTR_OPTICAL_MODULE_LIST,

    /**
     * @brief Set Optical Module state change notification callback function passed to the adapter.
     *
     * Use tai_optical_module_state_change_notification_fn as notification function.
     *
     * @type sai_pointer_t tai_optical_module_state_change_notification_fn
     * @flags CREATE_AND_SET
     * @default NULL
     */
    TAI_DEVICE_ATTR_OPTICAL_MODULE_STATE_CHANGE_NOTIFY,

    /**
     * @brief End of attributes
     */
    TAI_DEVICE_ATTR_END,

    /** Custom range base value */
    TAI_DEVICE_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    TAI_DEVICE_ATTR_CUSTOM_RANGE_END
} sai_device_attr_t;



/**
 * @brief Create device
 *
 * SDK initialization/connect to SDK. After the call the capability attributes should be
 * ready for retrieval via tai_get_device_attribute(). Same Device Object id should be
 * given for create/connect for each NPU.
 *
 * @param[out] device_id The Device Object ID
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t(*tai_create_device_fn)(
        _Out_ sai_object_id_t* device_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove/disconnect Device
 *
 * Release all resources associated with currently opened device
 *
 * @param[in] device_id The Device id
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_remove_device_fn)(
        _In_ sai_object_id_t device_id);

/**
 * @brief Set device attribute value
 *
 * @param[in] device_id Device id
 * @param[in] attr Device attribute
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_set_device_attribute_fn)(
        _In_ sai_object_id_t device_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get device attribute value
 *
 * @param[in] device_id Device id
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Array of device attributes
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_get_device_attribute_fn)(
        _In_ sai_object_id_t device_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Device method table retrieved with tai_api_query()
 */
typedef struct _tai_device_api_t
{
    tai_create_device_fn            create_device;
    tai_remove_device_fn            remove_device;
    tai_set_device_attribute_fn     set_device_attribute;
    tai_get_device_attribute_fn     get_device_attribute;

} tai_device_api_t;

#endif /** __TAI_DEVICE_H__ */
