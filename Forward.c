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
    if (FC[i]==1)
      break;
    ++i;
  }

  return FC[i];
}


/*Funcion que revisa si ya se colorearon
  todos los nodos del grafo*/
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
void color_maxcolor(int* max_color, int* st_max_color, int depth, int v_i_color){
  if (v_i_color > *max_color){
    *max_color = v_i_color;
    *st_max_color = depth;
  }
}


/*Devuelve cual es el proximo vertice a colorear basado en el 
  grado de saturacion y en el grado de los vertices*/
int nxt_vertex(int * satur, int vertex_num, Graph* graph, tuple* deg_vert, int lower_bound){
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
    nxt_vert = break_tie(deg_vert,graph,vertex_num-lower_bound);

  return nxt_vert;
}


/*Regenera el FC de un vertice*/
void genFC(int vert,
	   int* FC,
	   int FC_size,
	   Graph* graph,
	   int* satur_degree,
	   int upper_bound){
  int i;
  int* color_around = graph[vert].color_around;
  
  for(i=0; i < FC_size; ++i){
    if (color_around[i]>0)
      FC[i]=0;
    else
      FC[i]=lookahead(vert,i,upper_bound,graph,satur_degree);
  }
}


/*Procedimiento de lookahead para reducir el tamano del FC*/
int lookahead(int vert,
	      int color,
	      int upper_bound,
	      Graph* graph,
	      int* satur_degree){
  int i;
  int adj_satur;

  int adj_num = graph[vert].adj_size;
  int* adjs = graph[vert].adjacents;

  //Recorro los vecinos del nodo
  for (i=0; i<adj_num; ++i){

    //Tomo la saturacion del vecino
    adj_satur = satur_degree[adjs[i]];

    //Si no tiene un nodo adyacente de menor rango
    //con este color, aumento su saturacion
    if (graph[adjs[i]].color_around[color] == 0)
      adj_satur += 1;

    //Si su saturacion es igual la cota superior
    //menos uno, su FC sera vacio, devuelvo falso.
    if (adj_satur == (upper_bound-1))
      return 0;
  }
  
  //Si ningun vecino devolvio falso,
  //devuelvo true.
  return 1;
}


/*Calcula el nodo de menor rango con el color que se
  se le pasa como primer argumento*/
int new_first_max_color(int color, int* trace, Graph* graph){
  int i = 0;

  while(graph[trace[i]].color != color){
    ++i;
  }

  return i;
}


/*
  Funcion que actualiza mejor coloracion alcanzada
 */
void update_coloring(Graph* g, int n_of_vertex, int* coloring){
  int i;
  
  for (i=0; i<n_of_vertex; ++i){
    coloring[i] = g[i].color;
  }
}


/*Funcion Forward*/
void Forward(int* start_vert,
	     int* max_used_color,
	     int* first_max_color,
	     int* upper_bound,
	     int* trace,
	     int* depth,
	     int* satur_degree,
	     int* popularity,
	     tuple* deg_vert,
	     Graph* graph,
	     int n_of_vertex,
         int* coloring,
         int lower_bound){

  int current_vert = *start_vert;
  int max_color = *max_used_color;
  int st_max_color = *first_max_color;
  int ub = *upper_bound;
  int dth = *depth;
  
  int* FC = graph[current_vert].FC;
  int FC_size = mix((ub-1),max((max_color+1),lower_bound));
  int nxt_col = 0;

  //Mientras: el FC no sea vacio Y
  //          no tenga una coloracion completa
  /* while (number_of_FCs(FC,FC_size)>0 && */
  /*    ! complete_coloring(graph,n_of_vertex)){ */
  while (number_of_FCs(FC,FC_size)>0 &&
         (current_vert != -1)) {
    
    //Busco el siguiente color y coloreo el nodo
    nxt_col = nxt_color(FC,FC_size,popularity);
    graph[current_vert].color = nxt_col;
    trace[dth] = current_vert;
    ++dth;
    
    //Actualizo las estructuras auxiliares
    color_ca_and_satur(graph,satur_degree,current_vert,nxt_col);
    color_maxcolor(&max_color,&st_max_color,(dth-1),nxt_col);
    popularity[nxt_col] += 1;
    
    //Busco el siguiente vertice a colorear y
    //calculo su FC
    current_vert = nxt_vertex(satur_degree,n_of_vertex-lower_bound,graph,deg_vert, lower_bound);
    FC_size = mix((ub-1),max((max_color+1),lower_bound));
    FC = graph[current_vert].FC;
    genFC(current_vert,
	  FC,
	  FC_size,
	  graph,
	  satur_degree,
	  ub);
  }
  
  //Si tengo una coloracion completa, actualizo
  //el upper_bound y el maximo color usado
  //  if (complete_coloring(graph,n_of_vertex)){
  if (current_vert == -1) {
    *upper_bound = max_color;
    *max_used_color = (max_color-1);
    *first_max_color = new_first_max_color( (max_color-1) ,trace,graph);
    *start_vert = st_max_color;
    *depth = (dth-1);
    update_coloring(graph,n_of_vertex,coloring);
  }
  //Si tengo que hacer backtrack, lo hago desde donde estoy.
  //El upperbound no cambia ni el max_used_color
  else{
    *max_used_color = max_color;
    *first_max_color = st_max_color;
    *start_vert = current_vert;
    *depth = (dth-1);
  }
}
