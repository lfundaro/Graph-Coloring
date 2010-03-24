# ifndef UTILITIES
# define UTILITIES

# include "structs.h"
# include <signal.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdlib.h>

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


/**************************************************/
/* Inicializa los apuntadores del grafo temporal. */
/**************************************************/
void init_tmp_graph(linked_list **, int);

/***********************************************************/
/* Función de comparación que se utiliza para comparar si  */
/* un vértice es mayor que otro. Esta función es pasada    */
/* como parámetro a la función qsort (Quicksort).          */
/***********************************************************/
int compare_vertices(const void *, const void *);

/*****************************************************/
/* Funcion que compara dos elementos tuple segun los */
/* grados de los vértices.                           */
/*****************************************************/
int compare_tuples(const void *, const void *);


/*********************************************************/
/* Funcion que dado un arreglo de lista de adyacencias   */
/* y el número de vértices del grafo, retorna un arreglo */
/* de tuplas vértice-grado                               */
/*********************************************************/
void degree(struct Graph *, int, struct tuple *);

/**********************************************************/
/* Función que libera los elementos de una lista enlazada */
/**********************************************************/
void free_tuple_list(tuple_list *);

void degree_no_clique(Graph *, int *, int, tuple *, int);

int lin_search(int *, int, int);

#endif
