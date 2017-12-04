#include <tai.h>
#include <stdio.h>

tai_device_api_t *device_api;
tai_optical_module_api_t *optical_module_api;

sai_object_id_t g_device_id;
sai_object_id_t g_port_ids[8];

sai_status_t create_device() {
    sai_status_t status;
    sai_attribute_t attr;
    status = device_api->create_device(&g_device_id, 0, NULL);
    if ( status != SAI_STATUS_SUCCESS ) {
        return status;
    }
    attr.id = TAI_DEVICE_ATTR_OPTICAL_MODULE_NUMBER;
    attr.value.u32 = 0;
    status = device_api->get_device_attribute(g_device_id, 1, &attr);
    if ( status != SAI_STATUS_SUCCESS ) {
        return status;
    }
    printf("number of optical module: %d\n", attr.value.u32);

    return status;
}

sai_status_t create_port(int i) {
    sai_status_t status;
    sai_attribute_t attr_list[4];

    attr_list[0].id = TAI_OPTICAL_MODULE_ATTR_MODULE_INDEX;
    attr_list[0].value.u32 = (sai_uint32_t)i;

    attr_list[1].id = TAI_OPTICAL_MODULE_ATTR_MODULATION_FORMAT;
    attr_list[1].value.s32 = TAI_OPTICAL_MODULE_MODULATION_FORMAT_DP_16QAM;

    attr_list[2].id = TAI_OPTICAL_MODULE_ATTR_FREQUENCY;
    attr_list[2].value.u32 = 1912000; // 191.2THz

    attr_list[3].id = TAI_OPTICAL_MODULE_ATTR_WIDTH;
    attr_list[3].value.u32 = 50;  // 50GHz spacing

    status = optical_module_api->create_optical_module(&g_port_ids[i], g_device_id, 4, attr_list);
    if ( status != SAI_STATUS_SUCCESS ) {
        printf("failed to create optical module %d\n", i);
        return status;
    }
    return status;
}

int main() {
    sai_status_t status;
    int i;
    status = tai_api_initialize(0, NULL);
    if ( status != SAI_STATUS_SUCCESS ) {
        printf("failed to initialize TAI\n");
        return 1;
    }
    tai_log_set(TAI_API_DEVICE, TAI_LOG_LEVEL_INFO);
    tai_log_set(TAI_API_OPTICAL_MODULE, TAI_LOG_LEVEL_INFO);

    status = tai_api_query(TAI_API_DEVICE, (void**)&device_api);
    if ( status != SAI_STATUS_SUCCESS ) {
        printf("no api for TAI_API_DEVICE\n");
        return 1;
    }

    printf("device_api: %p\n", device_api);

    status = tai_api_query(TAI_API_OPTICAL_MODULE, (void**)&optical_module_api);
    if ( status != SAI_STATUS_SUCCESS ) {
        printf("no api for TAI_API_DEVICE\n");
        return 1;
    }

    printf("optical_module_api: %p\n", optical_module_api);

    create_device();
    for ( i = 0; i < 8; i++ ) {
        create_port(i);
    }

    status = tai_api_uninitialize();
    if ( status != SAI_STATUS_SUCCESS ) {
        printf("failed to uninitialize TAI\n");
        return 1;
    }
}
