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
#include "mbed.h"
#include "C12832.h"
#include "CCS811.h"
#include "Sht31.h"
#include "TSL2561.h"
#include "MMA7660.h"

// GLOBAL VARIABLES HERE
Sht31 temp_sensor(PF_0, PF_1);
C12832  lcd(PE_14, PE_12, PD_12, PD_11, PE_9);

// FUNCTION DEFINTIONS HERE
void lcd_print(const char* message) {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf(message);
}

void read_temp() {
    float t = temp_sensor.readTemperature();
    float h = temp_sensor.readHumidity();
    char val[32];
    sprintf(val, "TEMP: %3.2fc, HUM: %3.2f%%", t, h);
    lcd_print(val);
}

int main() {

    // MAIN CODE HERE
    while(1)
    {
        read_temp();
        wait_ms(2000);
    }
}
