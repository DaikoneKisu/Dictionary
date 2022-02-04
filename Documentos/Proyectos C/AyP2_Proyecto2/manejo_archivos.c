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
static void cerrar_archivo(FILE* archivo){
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
    if (archivo == NULL)
        return 0;

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

//Busca la palabra "palabra" en el archivo "nombre_archivo". Returna 1 si la encontró, 0 en caso contrario.
int buscar_palabra(char* nombre_archivo, char* palabra){
    FILE* archivo = abrir_archivo_lec(nombre_archivo);
    char tipo, *palabra1, *palabra2;
    palabra1 = (char*) malloc(25 * sizeof(char));
    palabra2 = (char*) malloc(25 * sizeof(char));

    if (palabra1 == NULL || palabra2 == NULL){
        printf("Error al asignar memoria para la busqueda de las palabras.");
        exit(1);
    }

    palabra = cadena_minusculas(palabra, 25);
    while (!feof(archivo)){
        fscanf(archivo, "%c %s %s\n", &tipo, palabra1, palabra2);
        palabra1 = cadena_minusculas(palabra1, 25);
        palabra2 = cadena_minusculas(palabra2, 25);

        if (strstr(palabra1, palabra) || strstr(palabra2, palabra)){
            free(palabra1);
            free(palabra2);
            cerrar_archivo(archivo);
            return 1;
        }
    }

    free(palabra1);
    free(palabra2);
    cerrar_archivo(archivo);
    return 0;
}

//Escribe los sinonimos o antonimos (dependiendo de si tipo es 'S' o 'A') del string "palabra".
void sinonimos_o_antonimos_palabra(char tipo, char* palabra, char* nombre_archivo){

    if (!buscar_palabra(nombre_archivo, palabra)){
        printf("No se encontro la palabra %s.\n", palabra);
        return;
    }

    FILE* archivo = abrir_archivo_lec(nombre_archivo);
    char tipo_en_arch, *palabra1, *palabra2;
    palabra1 = (char*) malloc(25 * sizeof(char));
    palabra2 = (char*) malloc(25 * sizeof(char));

    if (palabra1 == NULL || palabra2 == NULL){
        printf("Error al asignar memoria para la busqueda de sinonimos/antonimos de la palabra.");
        exit(1);
    }

    palabra = cadena_minusculas(palabra, 25);
    while(!feof(archivo)){
        fscanf(archivo, "%c %s %s\n", &tipo_en_arch, palabra1, palabra2);
        palabra1 = cadena_minusculas(palabra1, 25);
        palabra2 = cadena_minusculas(palabra2, 25);

        if (tipo_en_arch == tipo){
            if (strstr(palabra1, palabra))
                printf("%s ", palabra2);

            if (strstr(palabra2, palabra))
                printf("%s ", palabra1);

        }
    }

    cerrar_archivo(archivo);
    free(palabra1);
    free(palabra2);

    return;
}
