#include <driver/i2c.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "esp32/rom/ets_sys.h"
#include <esp_log.h>
#include <string.h>
#include "keypad.h"
#include <stdlib.h>
#include "freertos/semphr.h"

SemaphoreHandle_t mi_semaforo;

int pines_filas[TAM] = {25,26,27,16};
int pines_columnas[TAM] = {17,5,18,19};

void IRAM_ATTR pulsador(void *arg){
    xSemaphoreGiveFromISR(mi_semaforo,NULL);
    for(int i =0; i<TAM; i++){
      gpio_set_level(pines_filas[i],1);
    }
}


void keypad_init(void){
  gpio_install_isr_service(ESP_ISR_FLAG);
    for(int i = 0;i<TAM;i++){

        gpio_set_direction(pines_filas[i],GPIO_MODE_DEF_OUTPUT);
        gpio_set_direction(pines_columnas[i],GPIO_MODE_DEF_INPUT);
        gpio_pullup_en(pines_columnas[i]);
        gpio_pullup_en(pines_filas[i]);
        
        //gpio_install_isr_service(ESP_ISR_FLAG);
        gpio_isr_handler_add(pines_filas[i],pulsador,NULL);
        gpio_isr_handler_add(pines_columnas[i],pulsador,NULL);
        gpio_set_intr_type(pines_columnas[i],GPIO_INTR_NEGEDGE);
        gpio_set_intr_type(pines_filas[i],GPIO_INTR_POSEDGE);

        //gpio_pullup_en(pines_filas[i]);
        //gpio_set_level(pines_filas[i],1);
  }
  vTaskDelay(10/portTICK_RATE_MS);
}

void keypad_isr_handler_remove(){
    vTaskDelay(10/portTICK_RATE_MS);
    for(int i = 0; i<TAM; i++){
      gpio_isr_handler_remove(pines_filas[i]);
      gpio_isr_handler_remove(pines_columnas[i]);
    }
    vTaskDelay(10/portTICK_RATE_MS);
}

void keypad_isr_handler_add(){
  vTaskDelay(10/portTICK_RATE_MS);
    for(int i = 0; i<TAM; i++){
        gpio_isr_handler_add(pines_filas[i],pulsador,NULL);
        gpio_isr_handler_add(pines_columnas[i],pulsador,NULL);
    }
  vTaskDelay(10/portTICK_RATE_MS);

}

char keypad_get_char(){
  vTaskDelay(10/portTICK_RATE_MS);
  char k = 'n';
  char teclas[TAM][TAM] = {{'1','2','3','A'}, 
                     {'4','5','6','B'}, 
                     {'7','8','9','C'}, 
                     {'*','0','#','D'}};
  for(int i = 0; i<TAM; i++){
      gpio_set_level(pines_filas[i],0);
      //barrido en columnas
      for(int j = 0; j<TAM;j++){
        if(gpio_get_level(pines_columnas[j]) == 0 ){
          //printf("Tecla : %c\n", teclas[i][j]);
          k = teclas[i][j];
          while(gpio_get_level(pines_columnas[j]) == 0){}
        }
      }
      //gpio_set_level(pines_filas[i],1);
    }
    return k;
    vTaskDelay(2/portTICK_PERIOD_MS);
}

char *keypad_get_string(){
    char *string = malloc(6);

      for(int i =0; i<=5;i++){
          if(keypad_get_char() != 'n'){
            string[i] = keypad_get_char();
          }
          //string[i] = keypad_get_char();
      }

    //printf("Esto contiene un string : %s\n",string);
    vTaskDelay(2/portTICK_RATE_MS);
    return string;
}

void task_keypad(void *arg){
    mi_semaforo = xSemaphoreCreateBinary();
    char k = 'n';
    printf("first example task\n");
    while (1){
        if(xSemaphoreTake(mi_semaforo,portMAX_DELAY)== pdTRUE){
          keypad_isr_handler_remove();
            k = keypad_get_char();
            vTaskDelay(1/portTICK_RATE_MS);
            if(k!='n'){
                printf("char k: %c\n",k);
                keypad_isr_handler_add();
            }
        }
    }
}