#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "LCD.h"
#include <string.h>
#include "keypad.h"
#include "user_app.h"



void other_task(void* arg){
  while(1){
    vTaskDelay(1000/portTICK_RATE_MS);
    printf("other_task\n");
  }
}


void app_main(){
  xTaskCreate(other_task,"other_task",2000,NULL,2,NULL);
  xTaskCreate(userr_app,"user_app",4000,NULL,5,NULL);
}