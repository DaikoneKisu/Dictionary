#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manejo_archivos.h"
#include "cadenas.h"

//Abre el archivo "nombre_archivo" en modo lectura.
FILE* abrir_archivo_lec(char* nombre_archivo){
    return fopen(nombre_archivo, "r");
}

//Cierra el archivo "nombre_archivo"
void cerrar_archivo(FILE* archivo){
    fclose(archivo);
}

//Abre el archivo "nombre_archivo" en modo escritura.
static FILE* abrir_archivo_esc(char* nombre_archivo){
    return fopen(nombre_archivo, "w");
}

//Escribe  el string "cadena" en el archivo "archivo".
void escribir_en_archivo(char* nombre_archivo, char* cadena){
    FILE* archivo = abrir_archivo_esc(nombre_archivo);

    fputs(cadena, archivo);
    cerrar_archivo(archivo);
}

//Retorna 1 si el archivo esta vacio, 0 en caso contrario.
int archivo_esta_vacio(char* nombre_archivo){
    FILE* archivo = abrir_archivo_lec(nombre_archivo);
    char vacio = fgetc(archivo);

    if (vacio == EOF){
        cerrar_archivo(archivo);
        return 1;
    }

    cerrar_archivo(archivo);
    return 0;
}

//Recupera de la cache un string, que contiene el nombre del archivo diccionario.
char* recuperar_de_cache(char* cache){
    FILE* cache_file = abrir_archivo_lec(cache);
    char* nombre_archivo = (char*) malloc(30 * sizeof(char));

    if (nombre_archivo == NULL){
        printf("Error al asignar espacio para leer de la cache.");
        exit(1);
    }

    fgets(nombre_archivo, 30, cache_file);
    cerrar_archivo(cache_file);

    return nombre_archivo;
}

//Intenta abrir el archivo "nombre_archivo" en modo lectura. Retorna 1 si lo logra, 0 en caso contrario.
int intento_de_apertura_archivo(char* nombre_archivo){
    FILE* archivo = abrir_archivo_lec(nombre_archivo);
    if (archivo == NULL){
        free(archivo);
        return 0;
    }

    cerrar_archivo(archivo);
    return 1;
}

//Abre el caché de archivos y retorna el nombre del archivo previamente cargado como diccionario, o NULL si no se ha cargado ninguno previamente.
char* comprobar_cache(char* cache){
    FILE* cache_file = abrir_archivo_lec(cache);

    if (cache_file == NULL || feof(cache_file))
        return NULL;

    char* nombre_archivo = malloc(30 * sizeof(char));
    fgets(nombre_archivo, 30, cache_file);
    cerrar_archivo(cache_file);

    return nombre_archivo;
}
