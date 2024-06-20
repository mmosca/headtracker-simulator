#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "msp-headtracker.h"
#include "crc.h"

void updateCrc(headtrackerMessageBuffer_t *buffer)
{
    uint8_t *bytes = (uint8_t *)buffer;
    bytes+=3;
    uint8_t crc = 0;
    for(int i = 0; i < (sizeof(headtrackerMessageBuffer_t) - 4); i++) {
        crc = crc8_dvb_s2(crc, bytes[i]);
    }

    buffer->trailer.crc = crc;
}

int getNextValue()
{
    static int value = -2048;
    static int direction = 1;

    value = value + direction;

    if (value > 2047) {
        direction = -1;
    } else if (value < -2048) {
        direction = 1;
    }

    return value;
}

void simulateHeadTracker(int fd)
{
    struct timespec delay = {
        .tv_sec = 0,
        .tv_nsec = 100 * 1e6 // 100ms
    };
    do {
        headtrackerMessageBuffer_t buffer = {
            .header = {
                .lead_in = MSP_LEAD_IN,
                .msp_version = MSP_VERSION_2,
                .message_type = MSP_MESSAGE_REQUEST,
                .flag = 0,
                .cmd = MSP2_SENSOR_HEADTRACKER,
                .payload_length = sizeof(headtrackerMspMessage_t)
            },
            .message = {
                .version = 0,
                .pan = 0,
                .tilt = 0,
                .roll = 0,
                .sensitivity = 0
            },
            .trailer = {
                .crc = 0
            }
        };

        int value = getNextValue();
        buffer.message.pan = value;
        buffer.message.tilt = value;
        buffer.message.roll = value;
        buffer.message.sensitivity = -1;

        updateCrc(&buffer);

        int ret = write(fd, &buffer, sizeof(buffer));
        if(ret < 0) {
            perror("write");
            break;
        }

        nanosleep(&delay, NULL);

    } while(1);
}