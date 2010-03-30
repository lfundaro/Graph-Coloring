# include "structs.h"

/*
  Funcion que calcula la cantidad de colores posibles
  para un vertice

  Recibe un arreglo que representa un conjunto vectorial
  con los colores posibles marcados con 1 y el tamano ese
  arreglo
*/
//int* FC, int FC_size
int number_of_FCs(int*,int);


/*Funcion que revisa si ya se colorearon
  todos los nodos del grafo*/
//Graph* g, int n_of_vertex
int complete_coloring(Graph*,int);


/*
  Funcion que calcula el proximo color a utilizar

  Recibe el conjunto de colores posibles y el registro con el
  uso que tiene cada color hasta el momento
*/
//int* FC, int FC_size, int* color_use_record
int nxt_color(int*,int,int*);


/*
  Actualiza el color around de los vertices cuando
  se colorea un vertice y su grado de saturacion tambien
*/
//Graph* graph, int* satur_degree, int v_i, int color
void color_ca_and_satur(Graph*,int*,int,int);


/*
  Funcion que actualiza el color mas alto usado y el primer
  nodo con ese color cuando se pone un color.
*/
//int* max_color, int* st_max_color, int v_i, int v_i_color
void color_maxcolor(int*,int*,int,int);


/*
  Devuelve cual es el proximo vertice a colorear basado en el 
  grado de saturacion y en el grado de los vertices
*/
//int* satur, int vertex_num, Graph graph, int* base
int nxt_vertex(int*,int*,int,Graph*,tuple*, int);


/*
  Regenera el FC de un vertice

  Usa el espacio del anterior conjunto FC
  del nodo y lo reescribe con un nuevo conjunto
  FC
*/
//int vert, int* FC,int FC_size,Graph* graph,int* satur_degree,int upper_bound
void genFC(int,int*,int,Graph*,int*,int,int,int*,int,int*);


/*
  Procedimiento de lookahead para reducir el tamano del FC
*/
//int vert,int color,int upper_bound,int upper_bound,Graph* graph,int* satur_degree
int lookahead(int,int,int,Graph*,int*,int,int*,int,int*);


/*
  Calcula el nodo de menor rango con el color que se
  se le pasa como primer argumento
  
  Se utiliza cuando se quiere recalcular el primer
  nodo con el color mas alto usado
*/
//int color, int* trace, Graph* graph
int new_first_max_color(int,int*,Graph*);


//Graph* g, int n_of_vertex, int* coloring
void update_coloring(Graph*,int,int*);


/*
Funcion Forward
*/
//int* start_vert,      <- Vertice desde donde parte Forward
//int* max_used_color,  <- Color mas alto usado hasta el momento
//int* first_max_color, <- Nodo me menor rango con el color mas
//                         alto usado hasta el momento
//int* upper_bound,
//int* trace,           <- Traza con el orden en que se han elegido
//                         los nodos hasta el momento
//int* depth,           <- Posicion de la traza hasta donde existen nodos validos
//int* satur_degree,    <- Arreglo con los grados de saturacion de los nodos
//int* popularity,      <- Arreglo con el numero de veces que se ha usado cada color
//tuple* deg_vert,        <- Arreglo con los nodos ordenados por grado
//Graph* graph,
//int n_of_vertex,      <- Grado del grafo
//int* coloring         <- Mejor coloracion encontrada hasta el momento
void Forward(int*,int*,int*,int*,int*,int*,int*,int*,int*,tuple*,Graph*,int,int*, int);


void new_max_color(int *, int,int *);
