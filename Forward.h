# include "structs.h"


/*Funcion que calcula la cantidad de colores posibles
  para un vertice*/
/*
  Recibe un arreglo que representa un conjunto vectorial
  con los colores posibles marcados con 1 y el tamano ese
  arreglo
*/
//int* FC, int FC_size
int number_of_FCs(int* , int );


/*Funcion que calcula el proximo color a utilizar*/
/*Recibe el conjunto de colores posibles y el registro con el
  uso que tiene cada color hasta el momento*/
//int* FC, int FC_size, int* color_use_record
int nxt_color(int* , int , int* );

/*Actualiza el color around de los vertices cuando se colorea un vertice
  y su grado de saturacion tambien*/
//Graph* graph, int* satur_degree, int v_i, int color
void color_ca_and_satur(Graph *, int* , int , int );

/*Funcion que actualiza el color mas alto usado y el primer nodo con ese color
  cuando se pone un color*/
/*Modifica el color mas alto usado y el primer nodo en tener ese color a traves
  de efectos de borde, recibe apuntadores a ambos valores*/
//int* max_color, int* st_max_color, int v_i, int v_i_color
void color_maxcolor(int* , int* , int , int );

/*Devuelve cual es el proximo vertice a colorear basado en el 
  grado de saturacion y en el grado de los vertices*/
//int* satur, int vertex_num, Graph graph, int* base
int nxt_vertex(int* , int , Graph* , int* );
