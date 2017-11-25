#include "mbed.h"
#include "C12832.h"
#include "CCS811.h"
#include "Sht31.h"
#include "TSL2561.h"
#include "MMA7660.h"

// GLOBAL VARIABLES HERE
// var for printing messages
C12832  lcd(PE_14, PE_12, PD_12, PD_11, PE_9);

DigitalOut  led(PB_8, 1);
// required var for button press
InterruptIn button(PF_2);
// variable for temperature senser
Sht31 temp_sensor(PF_0, PF_1);
// variable for air sensor
CCS811 air_sensor(PF_0, PF_1);
// variable for switching functionality 
int current_func = 0;
void (*function_pt)();

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

void read_air() {
    air_sensor.init();
    uint16_t eco2, tvoc;
    air_sensor.readData(&eco2, &tvoc);
    char val[32];
    sprintf(val, "eCO2: %dppm, TVOC: %dppb", eco2, tvoc);
    lcd_print(val);
}

/*void toggle_led() {
    led = !led;
    lcd_print("switching functionality");
    wait_ms(500);
}*/

void switch_func() {
    if (current_func == 1) {
        current_func = 0;
    } else {
        current_func ++;
    }
    
    switch(current_func) {
        case 0:
            function_pt = &read_temp;
            break;
        case 1:
            function_pt = &read_air;
            break;
        default:
            break;
    }
}

int main() {

    // MAIN CODE HERE
    button.rise(&switch_func);
    //rval=string(current_func);
    //print(strval);
    function_pt = &read_temp;
    while(1)
    {
        function_pt();
        wait_ms(1000);
    }
}
