#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "cadenas.h"

//Convierte el string "cadena" de tamaño "tamanio" a minusculas.
char* cadena_minusculas(char* cadena, int tamanio){
    char* cadena_minus = (char*) malloc(tamanio * sizeof(char));

    if (cadena_minus == NULL){
        printf("Error al asignar memoria a la cadena del archivo en minusculas.");
        exit(1);
    }

    int index;
    for (index = 0; index < tamanio; index++)
        cadena_minus[index] = (char) tolower(cadena[index]);

    return cadena_minus;
}

