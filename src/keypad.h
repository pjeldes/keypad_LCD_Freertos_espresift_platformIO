#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"

#define keypad_H
#define TAM                     4
#define ESP_ISR_FLAG            0
#define TAM_COLA                20

SemaphoreHandle_t mi_semaforo;
xQueueHandle Q_keypad;

void keypad_init();
char keypad_get_char();
char *keypad_get_string();
void IRAM_ATTR pulsador(void *arg);
void keypad_isr_handler_remove();
void keypad_isr_handler_add();
void task_keypad(void *arg);
