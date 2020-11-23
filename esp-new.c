// Implements the RMT peripheral on Espressif SoCs
// Copyright (c) 2020 Lucian Copeland for Adafruit Industries

/* Uses code from Espressif RGB LED Strip demo and drivers
 * Copyright 2015-2020 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined(ESP32not)

#include <Arduino.h>
#include "driver/rmt.h"

// #define WS2812_T0H_NS (400)
// #define WS2812_T0L_NS (850)
// #define WS2812_T1H_NS (800)
// #define WS2812_T1L_NS (450)

// #define WS2811_T0H_NS (500)
// #define WS2811_T0L_NS (2000)
// #define WS2811_T1H_NS (1200)
// #define WS2811_T1L_NS (1300)

#define WS2812_T0H_NS (4)
#define WS2812_T0L_NS (8)
#define WS2812_T1H_NS (8)
#define WS2812_T1L_NS (4)

#define WS2811_T0H_NS (5)
#define WS2811_T0L_NS (20)
#define WS2811_T1H_NS (12)
#define WS2811_T1L_NS (13)

// Limit the number of RMT channels available for the Neopixels. Defaults to all
// channels (8 on ESP32, 4 on ESP32-S2 and S3). Redefining this value will free
// any channels with a higher number for other uses, such as IR send-and-recieve
// libraries. Redefine as 1 to restrict Neopixels to only a single channel.

void espShow(rmt_obj_t* rmt, uint8_t pin, uint8_t *pixels, uint32_t numBytes, boolean is800KHz) {
    rmt_data_t led_data[8*numBytes];
    uint8_t i=0;
    for (size_t len=0; len < numBytes; len++ ) {
        for (uint8_t bit=0; bit<8; bit++){
            if ( (pixels[len] & (1<<(7-bit)))) {
                led_data[i].level0 = 1;
                led_data[i].duration0 = 8;
                led_data[i].level1 = 0;
                led_data[i].duration1 = 4;
            } else {
                led_data[i].level0 = 1;
                led_data[i].duration0 = 4;
                led_data[i].level1 = 0;
                led_data[i].duration1 = 8;
            }
            i++;
        }
    }
    // Send the data
    rmtWrite(rmt, led_data, numBytes * 8);
}

#endif
