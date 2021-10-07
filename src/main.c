#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "LCD.h"
#include <string.h>
#include "keypad.h"


void app_main(){
  keypad_init();
  LCD_init();
  LCD_clearScreen();
  char k = 'n';
    while (true) {
        LCD_home();
        LCD_Plot("User:",0,LCD_LINEONE);
        LCD_Plot("Pass:",0,LCD_LINETWO);
        k = keypad_get_char();
        char *cadena = keypad_get_string();
        if(k!='n'){
          printf("%c",k);
          LCD_PlotChar(k,5,LCD_LINEONE);
          printf("%s",cadena);
        }
}
}