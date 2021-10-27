

#define keypad_H
#define TAM                     4
#define ESP_ISR_FLAG            0

//SemaphoreHandle_t mi_semaforo;

void keypad_init();
char keypad_get_char();
char *keypad_get_string();
void IRAM_ATTR pulsador(void *arg);
void keypad_isr_handler_remove();
void keypad_isr_handler_add();
void task_keypad(void *arg);
