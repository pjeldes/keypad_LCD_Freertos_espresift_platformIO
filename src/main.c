#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "LCD.h"
#include <string.h>
#include "keypad.h"
#include "user_app.h"


void app_main(){
  keypad_init();
  LCD_init();
  LCD_clearScreen();
  char user[6]="00000";
  char pass[6] = "00000";
  char cadena[6] = "nnnnn";
  uint8_t col = 0;
  uint8_t row = 0;
  bool CHECK_OUT_CREDENTIAL = false;
  //indica si ha terminado el tomar el usuario
  bool GET_USER_FINISH = false;
  //indica si ha terminado de tomar el password
  bool GET_PASS_FINISH = false;
  
  char k = 'n';
    while (true) {
        LCD_home();
        LCD_Plot("User:",0,LCD_LINEONE);
        LCD_Plot("Pass:",0,LCD_LINETWO);
        k = keypad_get_char();
        if(k!='n' && k != '*'){
          if(row == LCD_LINEONE){
            LCD_PlotChar(k,5+col,row);
          }
          else{
            LCD_PlotChar('*',5+col,row);
          }
          //LCD_PlotChar(k,5+col,row);
          cadena[col] = k;
          printf("col: %d\n",col);
          col++;
          if(col >= 5 && row == LCD_LINEONE){
            strcpy(user,cadena);
            vTaskDelay(1/portTICK_PERIOD_MS);
            printf("Usario: %s\n",user);
            col = 0;
            row = LCD_LINETWO;
            GET_USER_FINISH = true;
          }
          if(col >=5 && row == LCD_LINETWO){
            strcpy(pass,cadena);
            row = LCD_LINEONE;
            printf("Contraseña: %s\n",pass);
            col = 0;
            GET_PASS_FINISH = true;
          }
          //corroboracion
          if (GET_USER_FINISH && GET_PASS_FINISH == true){
            GET_USER_FINISH = false;
            GET_PASS_FINISH = false;
            CHECK_OUT_CREDENTIAL = checkout_credential(user,pass);
            if(CHECK_OUT_CREDENTIAL){
              //CHECK_OUT_CREDENTIAL = false;
              user[6] = "ooooo";
              pass[6] = "ooooo";
              LCD_clearScreen();
              LCD_Plot("--Welcom--",0,LCD_LINEONE);
              LCD_Plot(user,5,LCD_LINETWO);
              vTaskDelay(5000/portTICK_RATE_MS);//tiempo para mostrar mensaje
              LCD_clearScreen();
            }
            if (CHECK_OUT_CREDENTIAL == 0){
              LCD_clearScreen();
              LCD_Plot("PASS WRONG",0,LCD_LINEONE);
              LCD_Plot("TRY AGAIN",5,LCD_LINETWO);
              vTaskDelay(3000/portTICK_RATE_MS);//tiempo de espera para mostrar mensaje
              LCD_clearScreen();
            }

            
          } 
        }
       
        if(k=='*'){
          GET_USER_FINISH = false;
          GET_PASS_FINISH = false;
          col = 0;
          row = 0;
          //PLOT_credential(1);
          printf("* PRESSED\n");
            vTaskDelay(1/portTICK_RATE_MS);
            LCD_clearScreen();
            vTaskDelay(10/portTICK_RATE_MS);

        }
}
}