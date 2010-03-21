# include "Forward.h"
# include "utilities.h"

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

int complete_coloring(Graph* g, int n_of_vertex){
  int cc = 1;
  int i;

  for(i=0; i < n_of_vertex; ++i)
    if (g[i].color == -1)
      cc = 0;

  return cc;
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
void color_maxcolor(int max_color, int st_max_color, int v_i, int v_i_color){
  if (v_i_color > max_color){
    max_color = v_i_color;
    st_max_color = v_i;
  }
}


/*Devuelve cual es el proximo vertice a colorear basado en el 
  grado de saturacion y en el grado de los vertices*/
int nxt_vertex(int * satur, int vertex_num, Graph* graph, int* deg_vert){
  int i;
  int max_satur_degree = -1;
  int nxt_vert;

  for(i = 0; i < vertex_num; i++) {
    if (max_satur_degree < satur[i]) {
      max_satur_degree = satur[i];
      nxt_vert = i;
    }
  }

  if (repeated(max_satur_degree, satur, vertex_num, nxt_vert))
    nxt_vert = get_max_degree(deg_vert,graph,vertex_num);

  return nxt_vert;
}

void genFC(int* FC, int FC_size, int* color_around){
  int i;

  for(i=0; i < FC_size; ++i){
    if (color_around[i]>0)
      FC[i]=0;
    else
      FC[i]=1;
  }
}

int new_first_max_color(int color, int* trace, Graph* graph){
  int i = 0;

  while(graph[trace[i]].color != color){
    ++i;
  }

  return trace[i];
}

void Forward(int* start_vert,
	     int* max_used_color,
	     int* first_max_color,
	     int* upper_bound,
	     int* trace,
	     int* satur_degree,
	     int* popularity,
	     int* deg_vert,
	     int* ties_num,
	     Graph* graph,
	     int n_of_vertex,
	     int* coloring){

  int current_vert = *start_vert;
  int max_color = *max_used_color;
  int st_max_color = *first_max_color;
  int ub = *upper_bound;
  int ties = *ties_num;
  
  int* FC = graph[current_vert].FC;
  int FC_size = mix((ub-1),max_color);
  int nxt_col = 0;

  //Mientras: el FC no sea vacio Y
  //          no tenga una coloracion completa
  while (number_of_FCs(FC,FC_size)>0 &&
	 ! complete_coloring(graph,n_of_vertex)){
    
    //Busco el siguiente color y coloreo el nodo
    nxt_col = nxt_color(FC,FC_size,popularity);
    graph[current_vert].color = nxt_col;
    
    //Actualizo las estructuras auxiliares
    color_ca_and_satur(graph,satur_degree,current_vert,nxt_col);
    color_maxcolor(max_color,st_max_color,current_vert,nxt_col);
    popularity[nxt_col] += 1;
    
    //Busco el siguiente vertice a colorear y
    //calculo su FC
    current_vert = nxt_vertex(satur_degree,n_of_vertex,graph,deg_vert);
    FC_size = mix((ub-1),max_color);
    FC = graph[current_vert].FC;
    genFC(FC,
	  FC_size,
	  graph[current_vert].color_around);
  }
  
  //Si tengo una coloracion completa, actualizo
  //el upper_bound y el maximo color usado
  if (complete_coloring(graph,n_of_vertex)){
    *upper_bound = max_color;
    *max_used_color = (max_color-1);
    *first_max_color = new_first_max_color( (max_color-1) ,trace,graph);
    *start_vert = st_max_color;
  }
  //Si tengo que hacer backtrack, lo hago desde donde estoy.
  //El upperbound no cambia ni el max_used_color
  else{
    *max_used_color = max_color;
    *first_max_color = st_max_color;
    *start_vert = current_vert;
  }
}
