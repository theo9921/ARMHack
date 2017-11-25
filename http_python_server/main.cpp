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
#include "OdinWiFiInterface.h"
#include "http_request.h"

// GLOBAL VARIABLES HERE
C12832  lcd(PE_14, PE_12, PD_12, PD_11, PE_9);
OdinWiFiInterface wifi;

//Adding button inturrupts
InterruptIn post_button(PF_2);
InterruptIn get_put_button(PG_4);
volatile bool post_clicked = false;
volatile bool get_clicked = false;
volatile bool put_clicked = false;

// FUNCTION DEFINITIONS HERE
void lcd_print(const char* message) {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf(message);
}

//Adding button inturrupts
void send_post() {
    post_clicked = true;
}
void send_get_put() {
    get_clicked = true;
}

int main() {

    // MAIN CODE HERE
    lcd_print("Connecting...");
    int ret = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        lcd_print("Connection error.");
        return -1;
    }
    lcd_print("Successfully connected!");
    
    //Adding button interrups
    post_button.rise(&send_post);
    get_put_button.rise(&send_get_put);
    while (true) {
        
    }
}
    
}
