# include "Forward.h"

/*Funcion que calcula la cantidad de colores posibles
  para un vertice*/
/*
  Recibe un arreglo que representa un conjunto vectorial
  con los colores posibles marcados con 1 y el tamano ese
  arreglo
*/
int number_of_FCs(int* FC, int FC_size){
  int n = 0;
  int i = 0;

  while(i<FC_size){
    if (FC[i]<1)
      ++n;
    ++i;
  }

  return n;
}


/*Funcion que calcula el proximo color a utilizar*/
/*Recibe el conjunto de colores posibles y el registro con el
  uso que tiene cada color hasta el momento*/
int nxt_color(int* FC, int FC_size, int* color_use_record){
  int i = 0;
  int nxt_color = 0;
  int max_use = 0;

  while (i<FC_size){
    if (FC[i]<1 && color_use_record[i] > max_use)
      nxt_color=i;
    ++i;
  }

  return nxt_color;
}


/*Actualiza el color around de los vertices cuando se colorea un vertice
  y su grado de saturacion tambien*/
void color_ca_and_satur(Graph * graph, int* satur_degree, int v_i, int color){
  // Buscar los adyacentes a v_i
  // Si el vértice ya fue coloreado entonces no actualizo 
  // su grado de saturación
  int i;
  int * adjacents = graph[v_i].adjacents;
  
  satur_degree[v_i] = -1; //Por ya estoy coloreando v_i
    
  for(i = 0; i < graph[v_i].adj_size; i++) {
    if (satur_degree[adjacents[i]] != -1) {
      // Quiero saber si el vértice adyacente a v_i tiene en su 
      // arreglo de colores adyacentes el color "color".
      if (graph[adjacents[i]].color_around[color] == 0) 
        satur_degree[adjacents[i]] = 1;
      graph[adjacents[i]].color_around[color]++;
    }
  }
}


/*Funcion que actualiza el color mas alto usado y el primer nodo con ese color
  cuando se pone un color*/
/*Modifica el color mas alto usado y el primer nodo en tener ese color a traves
  de efectos de borde, recibe apuntadores a ambos valores*/
void color_maxcolor(int* max_color, int* st_max_color, int v_i, int v_i_color){
  if (v_i_color > *max_color){
    *max_color = v_i_color;
    *st_max_color = v_i;
  }
}


/*Devuelve cual es el proximo vertice a colorear basado en el 
  grado de saturacion y en el grado de los vertices*/
int nxt_vertex(int* satur, int vertex_num, Graph* graph, int* base){
  int i;
  int max_satur_degree;
  int nxt_vert;

  for(i = 0; i < vertex_num; i++) {
    if (max_satur_degree < satur[i]) {
      max_satur_degree = satur[i];
      nxt_vert = i;
    }
  }

  if (repeated(max_satur_degree, satur, vertex_num, nxt_vert))
    nxt_vert = get_max_degree(base,graph,vertex_num);

  return nxt_vert;
}
