# ifndef _GNU_SOURCE
# define _GNU_SOURCE
# endif
# include <regex.h>
# include "structs.h"
# include <stdio.h>
# include <stdlib.h>

/***************************************************************/
/* Función que lee la entrada estándar y usando una expresión  */
/* regular determina el número de vértices de la instancia     */
/***************************************************************/
int get_vertex_num();

/**************************************************************/
/* Crea       la estructura graph. Pone todos los colores en  */
/* -1, para cada vértice reserva memoria para la estructura   */
/* color_around. Pone los apuntadores a lista enlazada        */
/* (vértices adyacentes) en nulo.                             */
/**************************************************************/
Graph * create_graph(int);


/**************************************************************/
/* Función que crea una estructura temporal de grafo.         */
/* Esta estructura consiste de un arreglo de listas enlazadas */
/* donde se guardan los vecinos de cada vértice. La funció    */
/* utiliza expresiones regulares para detectar los lados en   */
/* el archivo. Los bucles son ignorados.                      */
/**************************************************************/
struct linked_list ** fill_tmp_graph(int);

/****************************************************/
/* Llena la matriz de adyacencias con los vértices  */
/* de la instancia. Utiliza una expresión regular   */
/* para detectar los lados en el archivo.           */
/* Los bucles son ignorados.                        */
/****************************************************/
void fill_graph(int, struct linked_list **, Graph *);

/****************************************************************/
/* Funcion que inicializa la estructura FC que tiene cada       */
/* vértice del grafo. Por defecto, el tamano de esta estructura */
/* será igual a upper_bound.                                    */
/****************************************************************/
void init_FC(Graph *, int, int);


