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
//------MBED CLOUD TUTORIAL-------
#include "mbed.h"
#include "C12832.h"
#include "CCS811.h"
#include "Sht31.h"
#include "TSL2561.h"
#include "MMA7660.h"

// GLOBAL VARIABLES HERE
MMA7660 accel(PF_0, PF_1);
C12832  lcd(PE_14, PE_12, PD_12, PD_11, PE_9);

// FUNCTION DEFINTIONS HERE
void read_accel() {
    float x = accel.x();
    float y = accel.y();
    float z = accel.z();
    char val[32];
    sprintf(val, "x=%.2f y=%.2f z=%.2f", x, y, z);
    lcd_print(val);
}

void lcd_print(const char* message) {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf(message);
}

int main() {

    // MAIN CODE HERE
    while(1)
    {
        read_accel();
        wait_ms(2000);
    }
}
