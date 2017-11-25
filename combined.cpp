#include "mbed.h"
#include "C12832.h"
#include "CCS811.h"
#include "Sht31.h"
#include "TSL2561.h"
#include "MMA7660.h"

// GLOBAL VARIABLES HERE
C12832  lcd(PE_14, PE_12, PD_12, PD_11, PE_9);
DigitalOut  led(PB_8, 1);
InterruptIn button(PF_2);

// FUNCTION DEFINTIONS HERE
void lcd_print(const char* message) {
    lcd.cls();
    lcd.locate(0, 3);
    lcd.printf(message);
}

void toggle_led() {
    led = !led;
	lcd_print("button pressed");
	wait_ms(2000);
	lcd_print("Waiting for button input");
}

int main() {

    // MAIN CODE HERE
    button.rise(&toggle_led);
    lcd_print("Waiting for button input");
    /*while(1)
    {
        wait_ms(2000);
    }*/
}
