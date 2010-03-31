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

/*************************************************************/
/* Función que construye el arreglo de tuplas grado-vértice  */
/* y los ordena de forma decreciente. En este arreglo están  */
/* excluidos los miembros de la clique máxima encontrada     */
/* por Brelaz+Interchange.                                   */
/*************************************************************/
void degree_no_clique(Graph *, int *, int, tuple *, int);

/*********************************************************/
/* Búsqueda lineal sobre la traza. Es útil para saber    */
/* la posición del vértice desde donde se parte a hacer  */
/* el labeling.                                          */
/*********************************************************/
int lin_search(int *, int, int);


/******************************************************/
/* Función que sirve para romper los empates cuando   */
/* no se puede decidir el próximo vértice a colorear  */
/* según los grados de saturación.                    */
/******************************************************/
int break_tie(tuple *, struct Graph *, int);


/*******************************************************/
/* Ordena los vértices adyacentes a un vértice v_i     */
/* en orden creciente, de manera tal que los vértices  */
/* puedan encontrarse haciendo búsqueda binaria.       */
/*******************************************************/
void order_graph(int, Graph *);

/**********************************************/
/* Salva coloreaciones de Brelaz+Interchange. */
/**********************************************/
void save_brelaz_col(Graph *, int *, int);

/********************************************/
/* Imprime coloración de Brelas+Interchange */
/********************************************/
void print_brelaz_col(int *, int);
#endif
