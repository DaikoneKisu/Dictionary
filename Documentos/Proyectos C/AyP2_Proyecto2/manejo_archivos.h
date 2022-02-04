#ifndef MANEJO_ARCHIVOS_H_INCLUDED
#define MANEJO_ARCHIVOS_H_INCLUDED

//Abre el archivo "nombre_archivo" en modo lectura
FILE* abrir_archivo_lec(char* nombre_archivo);

//Intenta abrir el archivo "nombre_archivo". Retorna 1 si lo logra, 0 en caso contrario.
int intento_de_apertura_archivo(char* nombre_archivo);

//Escribe  el string "cadena" en el archivo "archivo".
void escribir_en_archivo(char* nombre_archivo, char* cadena);

//Retorna 1 si el archivo esta vacio, 0 en caso contrario.
int archivo_esta_vacio(char* nombre_archivo);

//Recupera de la cache un string, que contiene el nombre del archivo diccionario.
char* recuperar_de_cache(char* cache);

//Busca la palabra "palabra" en el archivo "nombre_archivo". Returna 1 si la encontró, 0 en caso contrario.
int buscar_palabra(char* nombre_archivo, char* palabra);

//Escribe los sinonimos o antonimos (dependiendo de si tipo es 'S' o 'A') del string "palabra".
void sinonimos_o_antonimos_palabra(char tipo, char* palabra, char* nombre_archivo);

#endif // MANEJO_ARCHIVOS_H_INCLUDED
