#ifndef SINONIMOS_O_ANTONIMOS_H_INCLUDED
#define SINONIMOS_O_ANTONIMOS_H_INCLUDED

//Estructura que guarda los sinonimos y antonimos de una palabra.
typedef struct sin_y_ant sin_y_ant;

//Crea una estructura sin_y_ant.
sin_y_ant* crear_sin_y_ant();

//Libera el espacio ocupado por una estructura sin_y_ant.
void free_sin_y_ant(sin_y_ant* guardar_sin_ant);

//Libera el espacio ocupado por toda una lista de estructura sin_y_ant.
void free_all_sin_y_ant(sin_y_ant* guardar_sin_ant);

//Agrega un sinonimo a la estructura.
sin_y_ant* agregar_sinonimo(sin_y_ant* guardar_sin, char* sinonimo);

//Agrega un antonimo a la estructura.
sin_y_ant* agregar_antonimo(sin_y_ant* guardar_ant, char* antonimo);

//Escribe los sinonimos guardados en la estructura.
void escribir_sinonimos(sin_y_ant* guardar_sin);

//Escribe los antonimos guardados en la estructura.
void escribir_antonimos(sin_y_ant* guardar_ant);

//Añade contenedor2 al final de contenedor1.
sin_y_ant* sin_y_ant_append(void* contenedor1, sin_y_ant* contenedor2);

//Devuelve un apuntador al siguiente elemento del contenedor.
sin_y_ant* elemento_siguiente(sin_y_ant* contenedor);

#endif // SINONIMOS_O_ANTONIMOS_H_INCLUDED
