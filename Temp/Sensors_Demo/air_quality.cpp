//----------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from ARM Limited or its affiliates.
//
// (C) COPYRIGHT 2016 ARM Limited or its affiliates.
// ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from ARM Limited or its affiliates.
//----------------------------------------------------------------------------
//---------------MBED CLOUD TUTORIAL------------
#include "mbed.h"
#include "C12832.h"
#include "CCS811.h"
#include "Sht31.h"
#include "TSL2561.h"
#include "MMA7660.h"

// GLOBAL VARIABLES HERE
Sht31 temp_sensor(PF_0, PF_1);
C12832  lcd(PE_14, PE_12, PD_12, PD_11, PE_9);
CCS811 air_sensor(PF_0, PF_1);

// FUNCTION DEFINTIONS HERE
void lcd_print(const char* message) {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf(message);
}

// Air quality
void read_air() {
    air_sensor.init();
    uint16_t eco2, tvoc;
    air_sensor.readData(&eco2, &tvoc);
    char val[32];
    sprintf(val, "eCO2: %dppm, TVOC: %dppb", eco2, tvoc);
    lcd_print(val);
}

int main() {
    
    // MAIN CODE HERE
    while(1) {
        // WHILE LOOP CODE HERE
        read_air();
        wait_ms(2000);
    }
}
