#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "LCD.h"
#include <string.h>
#include "keypad.h"
#include "user_app.h"

//SemaphoreHandle_t mi_semaforo;

void other_task(void* arg){
  keypad_init();
  while(1){
    vTaskDelay(1000/portTICK_RATE_MS);
    printf("other_task\n");
  }
}



void app_main(){

  xTaskCreate(userr_app,"user app",4000,NULL,5,NULL);
  xTaskCreate(task_keypad,"keypad",2000,NULL,2,NULL);
}