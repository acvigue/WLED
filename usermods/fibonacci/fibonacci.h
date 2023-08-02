#pragma once

#include "wled.h"

class FibonacciUsermod : public Usermod {
   public:
    void setup() {}
    void connected() {}

    void loop() {}

    void handleOverlayDraw() {
        if (minute(localTime) != lastMinute) {
            setTime(hour(localTime) % 12, minute(localTime) / 5);
            lastMinute = minute(localTime);
        }

        for (int i = 0; i < 5; i++) {
            setPixel(i, colors[0][bits[i]]);
        }
    }

    void setTime(byte hours, byte minutes) {
        for (int i = 0; i < 5; i++) bits[i] = 0;

        setBits(hours, 0x01);
        setBits(minutes, 0x02);
    }

    void setBits(byte value, byte offset) {
        switch (value) {
            case 1:
                switch (random(2)) {
                    case 0:
                        bits[0] |= offset;
                        break;
                    case 1:
                        bits[1] |= offset;
                        break;
                }
                break;
            case 2:
                switch (random(2)) {
                    case 0:
                        bits[2] |= offset;
                        break;
                    case 1:
                        bits[0] |= offset;
                        bits[1] |= offset;
                        break;
                }
                break;
            case 3:
                switch (random(3)) {
                    case 0:
                        bits[3] |= offset;
                        break;
                    case 1:
                        bits[0] |= offset;
                        bits[2] |= offset;
                        break;
                    case 2:
                        bits[1] |= offset;
                        bits[2] |= offset;
                        break;
                }
                break;
            case 4:
                switch (random(3)) {
                    case 0:
                        bits[0] |= offset;
                        bits[3] |= offset;
                        break;
                    case 1:
                        bits[1] |= offset;
                        bits[3] |= offset;
                        break;
                    case 2:
                        bits[0] |= offset;
                        bits[1] |= offset;
                        bits[2] |= offset;
                        break;
                }
                break;
            case 5:
                switch (random(3)) {
                    case 0:
                        bits[4] |= offset;
                        break;
                    case 1:
                        bits[2] |= offset;
                        bits[3] |= offset;
                        break;
                    case 2:
                        bits[0] |= offset;
                        bits[1] |= offset;
                        bits[3] |= offset;
                        break;
                }
                break;
            case 6:
                switch (random(4)) {
                    case 0:
                        bits[0] |= offset;
                        bits[4] |= offset;
                        break;
                    case 1:
                        bits[1] |= offset;
                        bits[4] |= offset;
                        break;
                    case 2:
                        bits[0] |= offset;
                        bits[2] |= offset;
                        bits[3] |= offset;
                        break;
                    case 3:
                        bits[1] |= offset;
                        bits[2] |= offset;
                        bits[3] |= offset;
                        break;
                }
                break;
            case 7:
                switch (random(3)) {
                    case 0:
                        bits[2] |= offset;
                        bits[4] |= offset;
                        break;
                    case 1:
                        bits[0] |= offset;
                        bits[1] |= offset;
                        bits[4] |= offset;
                        break;
                    case 2:
                        bits[0] |= offset;
                        bits[1] |= offset;
                        bits[2] |= offset;
                        bits[3] |= offset;
                        break;
                }
                break;
            case 8:
                switch (random(3)) {
                    case 0:
                        bits[3] |= offset;
                        bits[4] |= offset;
                        break;
                    case 1:
                        bits[0] |= offset;
                        bits[2] |= offset;
                        bits[4] |= offset;
                        break;
                    case 2:
                        bits[1] |= offset;
                        bits[2] |= offset;
                        bits[4] |= offset;
                        break;
                }
                break;
            case 9:
                switch (random(2)) {
                    case 0:
                        bits[0] |= offset;
                        bits[3] |= offset;
                        bits[4] |= offset;
                        break;
                    case 1:
                        bits[1] |= offset;
                        bits[3] |= offset;
                        bits[4] |= offset;
                        break;
                }
                break;
            case 10:
                switch (random(2)) {
                    case 0:
                        bits[2] |= offset;
                        bits[3] |= offset;
                        bits[4] |= offset;
                        break;
                    case 1:
                        bits[0] |= offset;
                        bits[1] |= offset;
                        bits[3] |= offset;
                        bits[4] |= offset;
                        break;
                }
                break;
            case 11:
                switch (random(2)) {
                    case 0:
                        bits[0] |= offset;
                        bits[2] |= offset;
                        bits[3] |= offset;
                        bits[4] |= offset;
                        break;
                    case 1:
                        bits[1] |= offset;
                        bits[2] |= offset;
                        bits[3] |= offset;
                        bits[4] |= offset;
                        break;
                }

                break;
            case 12:
                bits[0] |= offset;
                bits[1] |= offset;
                bits[2] |= offset;
                bits[3] |= offset;
                bits[4] |= offset;

                break;
        }
    }

    void setPixel(byte pixel, uint32_t color) {
        switch (pixel) {
            case 0:
                strip.setPixelColor(0, color);
                break;
            case 1:
                strip.setPixelColor(1, color);
                break;
            case 2:
                strip.setPixelColor(2, color);
                break;
            case 3:
                strip.setPixelColor(3, color);
                strip.setPixelColor(4, color);
                break;
            case 4:
                strip.setPixelColor(5, color);
                strip.setPixelColor(6, color);
                strip.setPixelColor(7, color);
                strip.setPixelColor(8, color);
                strip.setPixelColor(9, color);
                break;
        };
    }

    uint16_t getId() { return USERMOD_ID_FIBONACCI; }

   private:
    byte bits[5];
    uint32_t colors[1][4] = {
        {// #1 RGB
         0xFFFFFF, 0xFF1111, 0x11FF11, 0x1111FF},
    };
    uint8_t lastMinute = 99;
};