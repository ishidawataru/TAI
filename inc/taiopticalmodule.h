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
 * @file    taiopticalmodule.h
 *
 * @brief   This module defines TAI optical terminal module interface
 */

#ifndef __TAI_OPTICAL_MODULE_H__
#define __TAI_OPTICAL_MODULE_H__

#include <saitypes.h>
#include <saistatus.h>

typedef enum _tai_optical_module_oper_status_t
{
    /** Unknown */
    TAI_OPTICAL_MODULE_STATUS_UNKNOWN,

    /** Down */
    TAI_OPTICAL_MODULE_STATUS_DOWN,

    /** Booting */
    TAI_OPTICAL_MODULE_STATUS_BOOTING,

    /** Up */
    TAI_OPTICAL_MODULE_STATUS_UP,

    /** Test Running */
    TAI_OPTICAL_MODULE_STATUS_TESTING,

} tai_optical_module_oper_status_t;

typedef enum _tai_optical_module_modulation_format_t
{
    TAI_OPTICAL_MODULE_MODULATION_FORMAT_UNKNOWN,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_BPSK,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_DC_DP_BPSK,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_QPSK,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_DP_QPSK,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_16QAM,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_DP_16QAM,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_DC_DP_16QAM,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_8QAM,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_DP_8QAM,

    TAI_OPTICAL_MODULE_MODULATION_FORMAT_DC_DP_8QAM,

} tai_optical_module_modulation_format_t;

typedef enum _tai_optical_module_attr_t
{

    /**
     * @brief Start of attributes
     */
    TAI_OPTICAL_MODULE_ATTR_START,

    /* READ-ONLY */

    /**
     * @brief Operational Status
     *
     * @type tai_optical_module_oper_status_t
     * @flags READ_ONLY
     */
    TAI_OPTICAL_MODULE_ATTR_OPER_STATUS = TAI_OPTICAL_MODULE_ATTR_START,

    /* READ-WRITE */

    /**
     * @brief Module Index
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_ONLY | KEY
     */
    TAI_OPTICAL_MODULE_ATTR_MODULE_INDEX,

    /**
     * @brief Frequency (GHz)
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_AND_SET
     */
    TAI_OPTICAL_MODULE_ATTR_FREQUENCY,

    /**
     * @brief Width (GHz)
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_AND_SET
     */
    TAI_OPTICAL_MODULE_ATTR_WIDTH,

    /**
     * @brief Modulation Format
     *
     * @type tai_optical_module_modulation_format_t
     * @flags MANDATORY_ON_CREATE | CREATE_AND_SET
     */
    TAI_OPTICAL_MODULE_ATTR_MODULATION_FORMAT,

    /**
     * @brief Target transmit power (unit: power-dBm)
     *
     * @type sai_uint32_t
     * @flags MANDATORY_ON_CREATE | CREATE_AND_SET
     */
    TAI_OPTICAL_MODULE_ATTR_TRANSMIT_POWER,

    /**
     * @brief End of attributes
     */
    TAI_OPTICAL_MODULE_ATTR_END,

    /** Custom range base value */
    TAI_OPTICAL_MODULE_ATTR_CUSTOM_RANGE_START = 0x10000000,

    /** End of custom range base */
    TAI_OPTICAL_MODULE_ATTR_CUSTOM_RANGE_END
} tai_optical_module_attr_t;

typedef enum _tai_optical_module_stat_t
{

    TAI_OPTICAL_MODULE_STAT_IF_IN_OCTETS,

} tai_optical_module_stat_t;

typedef struct _tai_optical_module_oper_status_notification_t
{
    sai_object_id_t id;

    tai_optical_module_oper_status_t state;

} tai_optical_module_oper_status_notification_t;

/**
 * @brief Create optical module
 *
 * @param[out] optical_module_id Optical Module id
 * @param[in] device_id Device id
 * @param[in] attr_count Number of attributes
 * @param[in] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_create_optical_module_fn)(
        _Out_ sai_object_id_t *optical_module_id,
        _In_ sai_object_id_t device_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list);

/**
 * @brief Remove optical module
 *
 * @param[in] optical_module_id Optical module id
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_remove_optical_module_fn)(
        _In_ sai_object_id_t optical_module_id);

/**
 * @brief Set port attribute value.
 *
 * @param[in] optical_module_id Optical module id
 * @param[in] attr Attribute
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_set_optical_module_attribute_fn)(
        _In_ sai_object_id_t optical_module_id,
        _In_ const sai_attribute_t *attr);

/**
 * @brief Get port attribute value.
 *
 * @param[in] optical_module_id Optical module id
 * @param[in] attr_count Number of attributes
 * @param[inout] attr_list Array of attributes
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_get_optical_module_attribute_fn)(
        _In_ sai_object_id_t optical_module_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

/**
 * @brief Get optical module statistics counters.
 *
 * @param[in] optical_module_id Optical module id
 * @param[in] number_of_counters Number of counters in the array
 * @param[in] counter_ids Specifies the array of counter ids
 * @param[out] counters Array of resulting counter values.
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_get_optical_module_stats_fn)(
        _In_ sai_object_id_t optical_module_id,
        _In_ uint32_t number_of_counters,
        _In_ const tai_optical_module_stat_t *counter_ids,
        _Out_ uint64_t *counters);

/**
 * @brief Clear optical module statistics counters.
 *
 * @param[in] optical_module_id Optical module id
 * @param[in] number_of_counters Number of counters in the array
 * @param[in] counter_ids Specifies the array of counter ids
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_clear_optical_module_stats_fn)(
        _In_ sai_object_id_t optical_module_id,
        _In_ uint32_t number_of_counters,
        _In_ const tai_optical_module_stat_t *counter_ids);

/**
 * @brief Clear optical module's all statistics counters.
 *
 * @param[in] optical_module_id Optical module id
 *
 * @return #SAI_STATUS_SUCCESS on success Failure status code on error
 */
typedef sai_status_t (*tai_clear_optical_module_all_stats_fn)(
        _In_ sai_object_id_t optical_module_id);

/**
 * @brief Optical module state change notification
 *
 * Passed as a parameter into sai_initialize_device()
 *
 * @param[in] count Number of notifications
 * @param[in] data Array of port operational status
 */
typedef void (*tai_optical_module_state_change_notification_fn)(
        _In_ uint32_t count,
        _In_ tai_optical_module_oper_status_notification_t *data);

/**
 * @brief Optical module methods table retrieved with tai_api_query()
 */
typedef struct _tai_optical_module_api_t
{
    tai_create_optical_module_fn              create_optical_module;
    tai_remove_optical_module_fn              remove_optical_module;
    tai_set_optical_module_attribute_fn       set_optical_module_attribute;
    tai_get_optical_module_attribute_fn       get_optical_module_attribute;
    tai_get_optical_module_stats_fn           get_optical_module_stats;
    tai_clear_optical_module_stats_fn         clear_optical_module_stats;
    tai_clear_optical_module_all_stats_fn     clear_optical_module_all_stats;
} tai_optical_module_api_t;

#endif // __TAI_OPTICAL_MODULE_H__
