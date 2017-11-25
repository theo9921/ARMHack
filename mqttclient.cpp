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
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"

// GLOBAL VARIABLES HERE
C12832  lcd(PE_14, PE_12, PD_12, PD_11, PE_9);
OdinWiFiInterface wifi;
InterruptIn button(PF_2);
volatile bool publish = false;
volatile int message_num = 0;

// FUNCTION DEFINITIONS HERE
void lcd_print(const char* message) {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf(message);
}

void messageArrived(MQTT::MessageData& md) {
    MQTT::Message &message = md.message;
    char msg[300];
    sprintf(msg, "Message arrived: QoS%d, retained %d, dup %d, packetID %d\r\n", message.qos, message.retained, message.dup, message.id);
    lcd_print(msg);
    wait_ms(1000);
    char payload[300];
    sprintf(payload, "Payload %.*s\r\n", message.payloadlen, (char*)message.payload);
    lcd_print(payload);
}

void publish_message() {
    publish = true;
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
    
    NetworkInterface* net = &wifi;
    MQTTNetwork mqttNetwork(net);
    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);
     
    const char* host = "129.169.18.81";
    const char* topic = "Mbed";
    lcd_print("Connecting to MQTT network...");
    int rc = mqttNetwork.connect(host, 10792);
    if (rc != 0) {
        lcd_print("Connection error.");
        return -1;
    }
    lcd_print("Successfully connected!");

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "connect-cloud-board";
    // data.username.cstring = "";  // Your mqtt username if required
    // data.password.cstring = ""; // Your mqtt password if required
    client.connect(data);
    client.subscribe(topic, MQTT::QOS2, messageArrived);
    
    button.fall(&publish_message);
    while (true) {
        // WHILE LOOP CODE HERE
        if (publish) {
            message_num++;
            MQTT::Message message;
            char buff[100];
            sprintf(buff, "QoS0 Hello, Python! #%d", message_num);
            message.qos = MQTT::QOS2;
            message.retained = false;
            message.dup = false;
            message.payload = (void*) buff;
            message.payloadlen = strlen(buff) + 1;
            rc = client.publish(topic, message);
            client.yield(100);
            publish = false;
        }
    }

}
