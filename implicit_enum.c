# include "implicit_enum.h"

void implicit_enum(int * upper_bound, int lower_bound,
                   int * members, Graph * graph,
                   tuple * deg_vert, int vertex_num) {
  int i;

  //Inicialización de arreglo de grados de saturación
  int * satur_degree = (int *) malloc(sizeof(int)*vertex_num);
  for(i = 0; i < vertex_num; i++) 
    satur_degree[i] = 0;

  // Se aumenta la cota para hacer converger el algoritmo 
  // en caso de no encontrarse mejor coloracion que upper_bound
  *upper_bound += 1;

  // Tabla de popularidad de un color
  int * popularity = (int *) malloc(sizeof(int) * (*upper_bound+1));
  for(i = 0; i < *upper_bound+1; i++) 
    popularity[i] = 0;

  // Se comienza por colorear la clique máxima encontrada
  // por Brelaz+Interchange
  color_clique(graph,satur_degree,popularity,members,vertex_num);

  // Se crea la traza que contiene la secuencia de vértices
  // coloreados cuando se hace backtracking
  int * trace = (int *) malloc(sizeof(int) * (vertex_num-(lower_bound+1)));
  for(i = 0; i < (vertex_num-(lower_bound+1)); i++) 
    trace[i] = 0;

  // Profundidad alcanzada en el árbol de backtrack
  int * depth = (int *) malloc(sizeof(int));
  *depth = 0;

  // Máximo color utilizado hasta el momento 
  int * max_used_color = (int *) malloc(sizeof(int));
  *max_used_color = lower_bound;

  // Posición en la traza del vértice con máximo color
  int * vertex_max_color = (int *) malloc(sizeof(int));
  *vertex_max_color = 0;

  // Apuntador a la primera casilla de arreglo vértice-grado
  tuple * base = deg_vert;

  // Vértice de partida para forwards
  int * current_vertex = (int *) malloc(sizeof(int));
  *current_vertex = nxt_vertex(satur_degree,members,vertex_num,graph,base, lower_bound);
  int FC_size = (lower_bound+1);
  int* FC = graph[*current_vertex].FC;
  genFC(*current_vertex,
        FC,
        FC_size,
        graph,
        satur_degree,
        *upper_bound,
	*depth,
	trace,
	*max_used_color,
	members);
  
  // Coloración conseguida hasta el momento
  int * coloring = (int *) malloc(sizeof(int) * vertex_num);
  int backtracks = 0;

  printf("------------------\n");
  printf("Enumeración implícita \n");

  while(1) {
    Forward(current_vertex,max_used_color,vertex_max_color,
	    upper_bound,trace, depth,members,satur_degree,popularity,
            base,graph,vertex_num,coloring, lower_bound);
    if (*upper_bound == lower_bound)
      break;
    else {
      backwards(trace, max_used_color, vertex_max_color,
                current_vertex, satur_degree, graph, base,
                popularity, coloring, depth, *upper_bound,
                lower_bound, vertex_num, members);
      if (*current_vertex == -1)
        // Ya no hay vértices para hacer backtrack
        break;
      backtracks++;
    }
  }

  // Se imprime el número cromático
  printf("Numero cromatico: %d\n",*upper_bound+1);
  printf("Backtracks: %d\n",backtracks);
  printf("Vertice --> Color\n");
  for (i=0; i<vertex_num; ++i){
    printf("%d --> %d\n",i+1,coloring[i]+1);
  }

  free(trace);
  free(max_used_color);
  free(vertex_max_color);
  free(current_vertex);
  free(satur_degree);
  free(popularity);
  free(coloring);
  free(depth);
}


void color_clique(Graph* graph, 
		  int* satur_degree, int* popularity,
		  int* clique, int vertex_num){
  int current_vert;
  int color=0;
  int i;

  for (i=0; i<vertex_num; ++i){
    if (clique[i]) {
      current_vert = i; 
      
      graph[current_vert].color = color;    
      
      color_ca_and_satur(graph,satur_degree,current_vert,color);
      popularity[color] += 1;
      
      ++color;
    }
  }
}


