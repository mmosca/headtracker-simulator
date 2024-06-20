#pragma once

#include <stdint.h>

#define MSP_LEAD_IN     '$'
#define MSP_VERSION_2   'X'

#define MSP2_SENSOR_HEADTRACKER     0x1F07

typedef enum {
    MSP_MESSAGE_REQUEST = '<',
    MSP_MESSAGE_RESPONSE = '>',
    MSP_MESSAGE_ERROR = '!'
} mspMessageType_e;

typedef struct msp_header_s {
    uint8_t lead_in;        // '$'
    uint8_t msp_version;    // 'X'
    uint8_t message_type;   // '>', '<', '!'
    uint8_t flag;           // 0
    uint16_t cmd;
    uint16_t payload_length;
} __attribute__((packed)) msp_header_t;

typedef struct msp_trailer_s {
    uint8_t crc;
} __attribute__((packed)) msp_trailer_t;