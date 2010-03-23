# include "implicit_enum.h"


void implicit_enum(int upper_bound, int lower_bound,
                   int * members, Graph * graph,
                   tuple * deg_vert, int vertex_num) {
  

  // Se comienza por colorear la clique máxima encontrada
  // por Brelaz+Interchange

  // IMPLEMENTAR FUNCION COLOR-CLIQUE


  // Se aumenta la cota para hacer converger el algoritmo 
  // en caso de no encontrarse mejor coloracion que upper_bound
  upper_bound += 1;

  // Se crea la traza que contiene la secuencia de vértices
  // coloreados cuando se hace backtracking
  int * trace = (int *) malloc(sizeof(int) * vertex_num);

  // Máximo color utilizado hasta el momento 
  int * max_used_color = (int *) malloc(sizeof(int));

  // Posición en la traza del vértice con máximo color
  int * vertex_max_color = (int *) malloc(sizeof(int));

  // Vértice de partida para forwards
  int * current_vertex = (int *) malloc(sizeof(int));

  //Inicialización de arreglo de grados de saturación
  int * satur_degree = (int *) malloc(sizeof(int)*vertex_num);
  int i;
  for(i = 0; i < vertex_num; i++) 
    satur_degree[i] = 0;

  
  // Apuntador a la primera casilla de arreglo vértice-grado
  tuple * base = deg_vert;

  // Tabla de popularidad de un color
  int * popularity = (int *) malloc(sizeof(int) * upper_bound);
  for(i = 0; i < vertex_num; i++) 
    popularity[i] = 0;
  
  // Coloración conseguida hasta el momento
  int * coloring = (int *) malloc(sizeof(int) * upper_bound);

  // Profundidad alcanzada en el árbol de backtrack
  int * depth = (int *) malloc(sizeof(int));
  
  while(1) {
    //    Forward(*args);
    if (*coloring == lower_bound)
      break;
    else {
      backwards(trace, max_used_color, vertex_max_color,
                current_vertex, satur_degree, graph, base,
                popularity, coloring, depth, upper_bound);
      if (*current_vertex == -1)
        // Ya no hay vértices para hacer backtrack
        break;
      }
    }
  // Se imprime el número cromático
  printf("");

  free(trace);
  free(max_used_color);
  free(vertex_max_color);
  free(current_vertex);
  free(satur_degree);
  free(popularity);
  free(coloring);
  free(depth);
}


