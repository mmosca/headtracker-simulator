# headtracker-simulator
A simple simulator of a MSP headtracker device.

This will move all three axis back and forth, with a sensitivity setting of -1

Can be used with INAV SITL.

* device can send a periodic MSPv2 message with current headtracker position information, similar to uart protocol.
* #define MSP2_SENSOR_HEADTRACKER     0x1F07
* msp-headtracker.h contains the MSP payload definition
```
typedef struct headtrackerMspMessage_s {
    uint8_t version;	    // 0
    int16_t pan;            // -2048~2047. Scale is min/max angle for gimbal
    int16_t tilt;           // -2048~2047. Scale is min/max angle for gimbal
    int16_t roll;           // -2048~2047. Scale is min/max angle for gimbal
    int16_t sensitivity;    // -16~15. Scale is min/max angle for gimbal
} __attribute__((packed)) headtrackerMspMessage_t;
```
