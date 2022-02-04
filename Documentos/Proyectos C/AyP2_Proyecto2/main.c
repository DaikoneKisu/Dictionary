#include <stdio.h>
#include <stdlib.h>
#include "manejo_archivos.h"

int main()
{
    char *nombre_archivo, palabra[25];
    nombre_archivo = (char*) malloc(30 * sizeof(char));

    if (!intento_de_apertura_archivo("cache.txt") || archivo_esta_vacio("cache.txt")){

        printf("Introduzca el nombre del archivo diccionario (incluyendo la extension y respetando mayusculas y minusculas): ");
        scanf("%s", nombre_archivo);

        escribir_en_archivo("cache.txt", nombre_archivo);
    }

    nombre_archivo = recuperar_de_cache("cache.txt");

    if (intento_de_apertura_archivo(nombre_archivo)){

        printf("Introduzca la palabra a buscar: ");
        scanf("%s", palabra);

        if (buscar_palabra(nombre_archivo, palabra))
            printf("Se encontro la palabra.\n");
        else
            printf("No se encontro la palabra.\n");

        printf("Los sinonimos de la palabra %s son:\n", palabra);
        sinonimos_o_antonimos_palabra('S', palabra, nombre_archivo);
        printf("\n");

        printf("Los antonimos de la palabra %s son:\n", palabra);
        sinonimos_o_antonimos_palabra('A', palabra, nombre_archivo);
        printf("\n");
    }
    else
        printf("No se pudo abrir el archivo.");

    free(nombre_archivo);
    return 0;
}
