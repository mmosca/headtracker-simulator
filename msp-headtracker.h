#pragma once

#include "msp.h"

typedef struct headtrackerMspMessage_s {
    uint8_t version;	    // 0
    int16_t pan;            // -2048~2047. Scale is min/max angle for gimbal
    int16_t tilt;           // -2048~2047. Scale is min/max angle for gimbal
    int16_t roll;           // -2048~2047. Scale is min/max angle for gimbal
    int16_t sensitivity;    // -16~15. Scale is min/max angle for gimbal
} __attribute__((packed)) headtrackerMspMessage_t;

typedef struct headtrackerMessageBuffer_s {
    msp_header_t header;
    headtrackerMspMessage_t message;
    msp_trailer_t trailer;
} __attribute__((packed)) headtrackerMessageBuffer_t;


void simulateHeadTracker(int fd);
