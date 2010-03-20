# include "degree.h"

/* Funcion que dado un arreglo de lista de adyacencias */
/* y el número de vértices del grafo, retorna un arreglo */
/* de tuplas vértice-grado */

void degree(Graph * graph, int vertex_num, tuple deg_vert[]) {
  int i;
  for(i = 0; i < vertex_num; i++) {
      tuple new_tuple = { i, graph[i].adj_size };
      deg_vert[i] = new_tuple;
  }
}

/* Funcion que compara dos elementos tuple segun los  */
/* grados de los vértices. */

int compare(const void * __a, const void * __b) { 
  tuple * a = (tuple *) __a;
  tuple * b = (tuple *) __b;
  if (a->degree < b->degree) 
    return 1;
  if (a->degree > b->degree)
    return -1;
  if (a->degree == b->degree)
    return 0;
}
