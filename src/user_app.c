#include <stdbool.h>
#include <stdio.h>
#include <string.h>
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
