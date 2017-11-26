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
InterruptIn put_button(PF_2);
volatile bool put_clicked = false;

// FUNCTION DEFINITIONS HERE
void lcd_print(const char* message) {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf(message);
}

//Adding button inturrupts
void send_put() {
    put_clicked = true;
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
    put_button.rise(&send_put);
    while (true) {
        //PUT REQUESTS
         if (put_clicked) {
            lcd_print("Button pressed!");
            put_clicked = false;
            NetworkInterface* net = &wifi;
            HttpRequest* request = new HttpRequest(net, HTTP_POST, "http://10.25.2.118:8080");
            
            //Debugging purposes, displays request on lcd screen
            //char s[64];
//            sprintf(s, "%x", request);
//            lcd_print(s);

            request->set_header("Content-Type", "application/json");
            const char body[] = "test";
            HttpResponse* response = request->send(body, strlen(body));
            lcd_print(response->get_body_as_string().c_str());
            delete request;
        }
    }
}
