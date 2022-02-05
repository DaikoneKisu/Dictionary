#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "trie.h"
#include "sinonimos_o_antonimos.h"
#include "manejo_archivos.h"
#include "cadenas.h"

//Busca y escribe los antonimos de la cadena "palabra" en el trie.
void antonimos_palabra(Trie* donde_buscar, char* palabra){
    palabra = cadena_minusculas(palabra, 25);

    escribir_antonimos(trie_get(donde_buscar, palabra));
}

//Busca y escribe los sinonimos de la cadena "palabra" en el trie.
void sinonimos_palabra(Trie* donde_buscar, char* palabra){
    palabra = cadena_minusculas(palabra, 25);

    escribir_sinonimos(trie_get(donde_buscar, palabra));
}

//
void e_expresion(Trie* donde_buscar, char* patron){
    GList* palabras_con_patron = trie_keys_matching(donde_buscar, patron);

    while(palabras_con_patron != NULL){
        printf("%s:\n", (char*) palabras_con_patron->data);

        printf("S: ");
        escribir_sinonimos(trie_get(donde_buscar, palabras_con_patron->data));
        printf("\n");

        printf("A: ");
        escribir_antonimos(trie_get(donde_buscar, palabras_con_patron->data));
        printf("\n");
    }

    g_list_free_full(palabras_con_patron, free);
    free(palabras_con_patron);
}

//Carga el archivo "nombre_archivo" al cache.
void cargar_archivo(char* nombre_archivo){
    escribir_en_archivo("cache.txt", nombre_archivo);
}

//Abre el archivo.dic y guarda todas las palabras, junto con sus sinonimos y antonimos, en el trie "diccionario".
Trie* crear_diccionario(){
    char tipo, *palabra1, *palabra2;
    palabra1 = (char*) malloc(25 * sizeof(char));
    palabra2 = (char*) malloc(25 * sizeof(char));

    if (palabra1 == NULL || palabra2 == NULL){
        printf("Error al asignar espacio para el almacenado de sinonimos/antonimos.");
        exit(1);
    }

    if (!intento_de_apertura_archivo("cache.txt") || archivo_esta_vacio("cache.txt")){
        printf("No se ha cargado ningun archivo .dic.\n");
        free(palabra1);
        free(palabra2);
        return NULL;
    }

    Trie* diccionario = trie_create(NULL);
    sin_y_ant* contenedor1 = crear_sin_y_ant();
    sin_y_ant* contenedor2 = crear_sin_y_ant();

    GString* nombre_archivo = g_string_new(recuperar_de_cache("cache.txt"));

    FILE* archivo = abrir_archivo_lec(nombre_archivo->str);
    if (archivo == NULL){
        printf("Error al abrir el archivo.");
        exit(1);
    }

    while(!feof(archivo)){

        fscanf(archivo, "%c %s %s\n", &tipo, palabra1, palabra2);
        palabra1 = cadena_minusculas(palabra1, 25);
        palabra2 = cadena_minusculas(palabra2, 25);

        if (tipo == 'S'){
            agregar_sinonimo(contenedor1, palabra2);
            agregar_sinonimo(contenedor2, palabra1);
        }

        if (tipo == 'A'){
            agregar_antonimo(contenedor1, palabra2);
            agregar_antonimo(contenedor2, palabra1);
        }

        trie_put(diccionario, palabra1, contenedor1);
        trie_put(diccionario, palabra2, contenedor2);

    }

    free_sin_y_ant(contenedor1);
    free_sin_y_ant(contenedor2);
    free(contenedor1);
    free(contenedor2);
    cerrar_archivo(archivo);

    return diccionario;
}

int main(){
    Trie* diccionario = crear_diccionario();

    printf("Sinonimos de bajo: ");
    sinonimos_palabra(diccionario, "bajo");
    printf("\n");

    return 0;
}
