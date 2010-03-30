# include "utilities.h"
# include "Forward.h"
# include "backwards.h"
# include <stdlib.h>
# include <stdio.h>


/*************************************************/
/* Algoritmo de enumeración implícita basado en  */
/* el paper de Kubake y Jackowski.               */
/*************************************************/
void implicit_enum(int *, int,int *, Graph *,tuple *, int);


/*
  Funcion que colorea una clique. Lo que hace es
  simplemente asignarle un color distinto a cada
  que le pasan por el arreglo clique, acutalizando
  los grados de saturacion y el registro de popularidad.
*/
//Graph graph, int* satur_degree, int* populariry, int* clique, int vertext_num
void color_clique(Graph*, int*, int*, int*, int);
