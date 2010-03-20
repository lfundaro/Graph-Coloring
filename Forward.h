# include <stdlib.h>
# include "structs.h"


/*Funcion que calcula la cantidad de colores posibles
  para un vertice*/
/*
  Recibe un arreglo que representa un conjunto vectorial
  con los colores posibles marcados con 1 y el tamano ese
  arreglo
*/
int number_of_FCs(int* , int );


/*Funcion que calcula el proximo color a utilizar*/
/*Recibe el conjunto de colores posibles y el registro con el
  uso que tiene cada color hasta el momento*/
int nxt_color(int* , int , int* );

void color_ca_and_satur(Graph * , int * , int , int );

/*Funcion que actualiza el color mas alto usado y el primer nodo con ese color
  cuando se pone un color*/
/*Modifica el color mas alto usado y el primer nodo en tener ese color a traves
  de efectos de borde, recibe apuntadores a ambos valores*/
void color_maxcolor(int* , int* , int , int );

int nxt_vertex(int* , int , Graph , int* );
