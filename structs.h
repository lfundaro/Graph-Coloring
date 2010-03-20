#ifndef STRUCTS
#define STRUCTS 

/************************************************/
/* Tipo lista enlazada que contiene un entero   */
/* que representa    un vertice y un apuntador  */
/* a la próxima estructura de lista enlazada    */
/************************************************/
typedef struct linked_list {
  int vertex;
  struct linked_list * next;
} linked_list;

typedef struct linked_array_list {
  int* array;
  int color;
  struct linked_array_list * next;
} linked_array_list;



/**********************************************************/
/* Estructura que se utiliza para construir temporalmente */
/* la estructura de grafo. Esto es así porque el formato  */
/* DIMACS no permite saber a priori cuántos vecinos       */
/* tiene un nodo, sino hasta cuando se leen. Los vecinos  */
/* se pondrán temporaralmente en una lista enlazada para  */
/* luego ser pasados a la estructura Graph.               */
/**********************************************************/ 
/* typedef struct Temp { */
/*   int vertex; */
/*   struct linked_list * pt; */
/* } Temp; */


/**********************************************************************/
/* Estructura que almacena el color de un vértice. El apuntador       */
/* a adjacents permite saber cuáles son los vecinos de un vértice.    */
/* Adjacents es un arreglo que está ordenado por número de vértice    */
/* en orden creciente, esto es útil para aplicar búsqueda binaria     */
/* y así saber si un vértice es vecino de otro en complejidad log(n). */
/* La estructura color_around permite saber cuáles son los colores    */
/* de los vértices que tiene adyacentes.                              */
/**********************************************************************/
typedef struct Graph {
  int color;
  int * adjacents;
  int * color_around;
} Graph;

/************************************************************/
/* Tupla que sirve para representar los vertices con su     */
/* grado en el arreglo ordenado por grados que pide DSTATUR */
/************************************************************/
typedef struct tuple {
  int vertex;
  int degree;
} tuple;

/**************************************************************/
/* Pair es la estructura que retorna Dsatur.                  */
/* Clique representa la cota inferior de coloración.          */
/* Coloring representa la cota superior.                      */
/* Members es un arreglo que contiene los miembros            */
/* que conforman la clique máxima encontrada por el algoritmo */
/**************************************************************/
typedef struct pair {
  int clique;
  int coloring;
  int * members;
} pair;

#endif
