#include <stdbool.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "LCD.h"
#include <string.h>
#include "keypad.h"
#include "user_app.h"

//memoria para usuarios
//el numero de usuario debe soinsidir con el
char* user_credential[NUM_STRINGS] = { "11111","2222B","5555A"};
char* pass_credential[NUM_STRINGS] = { "12345","54321","1234A"};

//compara cadena de caracteres
bool str_compare(char arr1[],char arr2[]){
    bool FLAG = 0;
    FLAG = strcmp(arr1,arr2);
    if (FLAG == 0){
        return 1;
    }
    else{
        return 0;
    }
}

//muestra las credenciales, recibe el argumento id
void PLOT_credential(uint8_t id){
    printf("USER Credential: %s\n",user_credential[id]);
    printf("PASS Credential: %s\n",pass_credential[id]);
}

// sirve para corroborar credenciales, busca si el usuari existe y corrobora si el usuario/contraseña
// es correcto
bool checkout_credential(char uss_arr[],char pass_arr[]){
    //buscar user por id
    bool THERE_IS_USER = false;
    bool COINCIDE_PASS = false;
    uint8_t out = OUT_NOT_KNOW;
    for(uint8_t id = 0;id < NUM_STRINGS; id++){
        THERE_IS_USER = str_compare(uss_arr,user_credential[id]);
        printf("IS_THERE_USER %d? %d\n",id,THERE_IS_USER);
        if(THERE_IS_USER){
            out = id;
            THERE_IS_USER = false;
        }
    }
    printf("OUT: %d\n",out);
    printf("FINDED USER: %s\n",user_credential[out]);
    
    // verificar pass
    COINCIDE_PASS = str_compare(pass_arr,pass_credential[out]);
    if(COINCIDE_PASS){
        printf("---------welcome %s------------\n",user_credential[out]);
        printf("PASS OK\n");
        return 1;
    }
    else{
        printf("pass or user wrong\n");
        out = OUT_NOT_KNOW;
        printf("OUT_NOT_KNOW: %d\n",out);
        return 0;
    }

}
//Tarea aplicacion de usuario
void userr_app(void *arg){
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
