# ifndef UTILITIES
# define UTILITIES

# include "structs.h"
# include <signal.h>
# include <sys/time.h>


/***********************************************************/
/* Función que permite determinar la longitud de una lista */
/***********************************************************/
int list_length(linked_list *);

/***********************************************/
/* Funcion que inicializa un arreglo en ceros. */
/***********************************************/
void initialize(int*,int);

/****************************************************************/
/* Inicialización de la estructura de grafo. Pone todos         */
/* los colores en -1 para indicar que ningún vértice está       */
/* coloreado. También inicializa la estructura color around     */
/* con todas sus casillas en 0 para indicar que ningún vértice  */
/* adyacente está coloreado.                                    */
/****************************************************************/
void graph_init(struct Graph *, int);

/**********************************************************/
/* Función que libera toda la memoria que ocupada por la  */
/* estructura grafo                                       */
/**********************************************************/
void free_graph(struct Graph *, int);

/************************************************************/
/* Función que obtiene el tiempo con 4 décimas de precisión */
/************************************************************/
double timer();

/***************************************************************/
/* Manejador de alarma. La alarma se activa cuando han pasado  */
/* 5 minutos y el algoritmo de enumeración implícita no ha     */
/* terminado de colorear la instancia                          */
/***************************************************************/
void alarmHandler();

/********************************************************/
/* Función que libera toda la memoria ocupada           */
/* por la lista enlazada que almacena el grafo temporal */
/********************************************************/
void free_tmp_graph(int, struct linked_list **);

#endif
