#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "sinonimos_o_antonimos.h"

//Estructura que guarda los sinonimos y antonimos de una palabra.
typedef struct sin_y_ant {
    GString* sinonimo;
    GString* antonimo;
    sin_y_ant* next;
} sin_y_ant;

//Crea una estructura sin_y_ant.
sin_y_ant* crear_sin_y_ant(){
    sin_y_ant* guardar_sin_ant = (sin_y_ant*) malloc(sizeof(sin_y_ant));
    if (guardar_sin_ant == NULL){
        printf("Error al asignar espacio a la estructura de sinonimos y antonimos.\n");
        exit(1);
    }

    guardar_sin_ant->sinonimo = g_string_sized_new(25);
    guardar_sin_ant->antonimo = g_string_sized_new(25);
    if (guardar_sin_ant->sinonimo == NULL || guardar_sin_ant->antonimo == NULL){
        printf("Error al asignar espacio a la subestructura de sinonimos y antonimos.\n");
        exit(1);
    }

    guardar_sin_ant->next = NULL;

    return guardar_sin_ant;
}

//Libera el espacio ocupado por una estructura sin_y_ant.
void free_sin_y_ant(sin_y_ant* guardar_sin_ant){
    gboolean freed = 1;

    g_string_free(guardar_sin_ant->sinonimo, freed);
    g_string_free(guardar_sin_ant->antonimo, freed);

}

//Libera el espacio ocupado por toda una lista de estructura sin_y_ant.
void free_all_sin_y_ant(sin_y_ant* guardar_sin_ant){
    sin_y_ant* pos_actual;

    while(pos_actual != NULL){
        pos_actual = guardar_sin_ant;
        guardar_sin_ant = guardar_sin_ant->next;
        free_sin_y_ant(pos_actual);
    }

    free(pos_actual);
}

//Agrega un sinonimo a la estructura.
sin_y_ant* agregar_sinonimo(sin_y_ant* guardar_sin, char* sinonimo){
        guardar_sin->sinonimo = g_string_new(sinonimo);
        return guardar_sin;
}

//Agrega un antonimo a la estructura.
sin_y_ant* agregar_antonimo(sin_y_ant* guardar_ant, char* antonimo){
    guardar_ant->antonimo = g_string_new(antonimo);
    return guardar_ant;
}

//Escribe los sinonimos guardados en la estructura.
void escribir_sinonimos(sin_y_ant* guardar_sin){
    sin_y_ant* pos_actual;

    for(pos_actual = guardar_sin; pos_actual != NULL; pos_actual = pos_actual->next)
        printf("%s ", pos_actual->sinonimo->str);

    free(pos_actual);
}

//Escribe los antonimos guardados en la estructura.
void escribir_antonimos(sin_y_ant* guardar_ant){
    sin_y_ant* pos_actual;

    for(pos_actual = guardar_ant; pos_actual != NULL; pos_actual = pos_actual->next)
        printf("%s ", guardar_ant->antonimo->str);
    free(pos_actual);
}

//Añade contenedor2 al final de contenedor1.
sin_y_ant* sin_y_ant_append(void* contenedor1, sin_y_ant* contenedor2){

    if (contenedor1 == NULL)
        return contenedor2;

    sin_y_ant* pos_actual;

    for(pos_actual = contenedor1; pos_actual->next != NULL; pos_actual = pos_actual->next);
    pos_actual->next = contenedor2;
    free(pos_actual);

    return contenedor1;
}

//Devuelve un apuntador al siguiente elemento del contenedor.
sin_y_ant* elemento_siguiente(sin_y_ant* contenedor){
    sin_y_ant* siguiente = crear_sin_y_ant();
    contenedor->next = siguiente;

    free(siguiente);
    return contenedor->next;
}
