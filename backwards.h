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
void backwards(int *, int *, int *, int *, int *, 
               Graph *, tuple *, int *, int *, 
               int *, int, int);


/***************************************************************/
/* Función que dado un vértice decoloreado, restablece su      */
/* grado de saturación a 0 y decrementa el grado de saturación */
/* de todos sus vecinos.                                       */
/***************************************************************/
void uncolor_satur(int *, Graph *, int);

/****************************************************/
/* Función que verifica si el elemento que se está  */
/* decoloreando está apuntado por base. De ser así  */
/* se decrementa base.                              */
/****************************************************/
void update_base(int *, int, tuple *);

/*********************************************************/
/* Función que actualiza estructuras a medida que se va  */
/* decoloreando.                                         */
/*********************************************************/
void update_all(int *, Graph *, tuple *, int *, 
                int, int, int *);

/********************************************************/
/* Función que arregla el FC del vértice donde forwards */
/* comenzará a colorear de nuevo.                       */
/********************************************************/
//void set_new_FC(Graph *,int,int, int);

/*************************************************************/
/* Función que determina si un elemento es adyacente a otro. */
/*************************************************************/
int * is_adjacent(int *, int, Graph *);


/**************************************/
/* Función que etiqueta los vértices  */
/**************************************/
tuple_list * label(Graph *, int *, int *, int *);

/*********************************************************/
/* Función que determina el máximo color utilizado hasta */
/* ahora.                                                */
/*********************************************************/
void max_color(int *, int *, int);

