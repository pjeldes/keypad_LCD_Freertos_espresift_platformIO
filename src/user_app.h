#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Macros
#define NUM_STRINGS          3
#define OUT_NOT_KNOW         0

bool str_compare(char arr1[],char arr2[]);
void PLOT_credential(uint8_t id);
bool checkout_credential(char uss_arr[],char pass_arr[]);