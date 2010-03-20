# include "degree.h"

/* Funcion que dado un arreglo de lista de adyacencias */
/* y el número de vértices del grafo, retorna un arreglo */
/* de tuplas vértice-grado */

void degree(Graph * graph, int vertex_num, tuple deg_vert[]) {
  int i;
  int count = 0;
  linked_list * aux;
  for(i = 0; i < vertex_num; i++) {
    aux = (linked_list *) graph[i].pt; // Apunta al primer adyacente
      while (aux != NULL) {
        count++;
        aux = aux->next;
      }
      // Se asigna una tuple vertice-grado al arreglo deg_vert
      tuple new_tuple = { i, count };
      deg_vert[i] = new_tuple;
      count = 0;
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
