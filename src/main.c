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
  mi_semaforo = xSemaphoreCreateBinary();
  Q_keypad = xQueueCreate(TAM_COLA,1);
  xTaskCreate(userr_app,"user app",4000,NULL,5,NULL);
  xTaskCreate(task_keypad,"keypad",2000,NULL,2,NULL);
  vTaskStartScheduler();

}