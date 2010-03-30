# ifndef BACKWARDS
# define BACKWARDS


# include "structs.h"
# include "utilities.h"
# include <stdlib.h>
# include <stdio.h>


/**************************************************************/
/* Función que le indica a la función forwards desde donde    */
/* se debe partir para colorear. Esto se logra haciendo       */
/* un backtracking no cronológico y aplicando el algoritmo    */
/* de label. Mientras se sube por el arbol, es necesario      */
/* actualizar estructuras como color_around, popularity, etc. */
/**************************************************************/
void backwards(int *, int *, int *, int *,  int *, Graph *, 
               tuple *, int *, int *, int* , int, int, int, int*);

/***************************************************************/
/* Función que dado un vértice decoloreado, restablece su      */
/* grado de saturación a 0 y decrementa el grado de saturación */
/* de todos sus vecinos.                                       */
/***************************************************************/
void uncolor_satur(int *, Graph *, int, int);

/*********************************************************/
/* Función que actualiza estructuras a medida que se va  */
/* decoloreando.                                         */
/*********************************************************/
void update_all(int *, Graph *, tuple *, int *, 
                int, int, int *, int *);

/*************************************************************/
/* Función que determina si un elemento es adyacente a otro. */
/*************************************************************/
int * is_adjacent(int *, int, Graph *);


/**************************************/
/* Función que etiqueta los vértices  */
/**************************************/
void label(Graph *, int, int *, int, int*);

/*********************************************************/
/* Función que determina el máximo color utilizado hasta */
/* ahora.                                                */
/*********************************************************/
void max_color(int *, int *);

/********************************************************/
/* Procedimiento utilizado para quitar etiquetas desde  */
/* el vértice X_k hasta el vértice X_n.                 */
/********************************************************/
void unlabel(Graph *, int *, int, int);

/**********************************************************/
/* Procedimiento que determina el vértice de mínimo rango */
/* que tiene el máximo color utilizado hasta el momento.  */
/**********************************************************/
void det_first_max_color(Graph *, int *, int, int *, int);




/*********************************************************/
/* Función que determina si un vértice es miembro        */
/* de la clique. Esta función es necesaria porque        */
/* como partimos del nodo donde existe una coloración    */
/* parcial que incluye a la clique, entonces no queremos */
/* que en ningún momento el algoritmo de Forward         */
/* recoloree alguno de los miembros de la clique.        */
/*********************************************************/
int clique_member(int *, int);


/*************************************************************/
/* Función que se utiliza para recalcular los grados de      */
/* saturación de un vértice una vez que éste es decoloreado. */
/*************************************************************/
void calculate_satur_degree(int *, int, Graph *, int); 


// Labeling cuando se aplica lookahead
void label_ahead(Graph *, int, int, int *, int, int *);

#endif
