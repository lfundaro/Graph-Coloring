#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

int max(int a, int b){
  if (a>b) return a;
  else return b;
}

int mix(int a, int b){
  if (a<b) return a;
  else return b;
}

int list_length(linked_list * list){
  int len = 0;
  while (list != NULL){
    len += 1;
    list = list->next;
  }
  return len;
}

void initialize(int* array,int N) {
  int i;
  for(i=0;i<N;i++) {
    array[i]=0;
  }
}

void graph_init(struct Graph * graph, int vertex_num) {
  int j;
  int k;
  for (j = 0; j < vertex_num ; j++) {
    graph[j].color = -1; // Color inicial
    for(k = 0; k < vertex_num; k++) 
      graph[j].color_around[k] = 0;
  }
}

//Función que libera de memoria la estructura del grafo
void free_graph(struct Graph * graph, int vertex_num) {
  int i;
  for(i = 0; i < vertex_num; i++) { 
    free(graph[i].color_around);
    free(graph[i].adjacents);
    free(graph[i].FC);
  }
  free(graph);
}

void free_tmp_graph(int vertex_num, struct linked_list ** tmp_graph) {
  int i;
  linked_list * back;
  linked_list * forward;
  //Se liberan los arreglos color_around
  //y las listas enlazadas de adyacencias
  for(i = 0; i < vertex_num; i++) {
    back = tmp_graph[i];
    forward = back;
    while(forward != NULL) {
      forward = back->next;
      free(back);
      back = forward;
    }
  }
  free(tmp_graph);
}

double timer() {
  struct timeval t_p;
  double time;
  if (!gettimeofday(&t_p, NULL))
    time = (double) t_p.tv_sec + ((double) t_p.tv_usec)/1000000.0;
  else
    printf("\n mal tiempo \n");
  return time;
}

void alarmHandler() {
  printf("Se ha excedido el límite de 5 minutos \n");
  exit(0);
}

void init_tmp_graph(linked_list ** tmp_graph, int vertex_num) {
  int i;
  for(i = 0; i < vertex_num; i++) 
    tmp_graph[i] = NULL;
}

void order_graph(int vertex_num, Graph * graph) {
  // Apuntador a la base del arreglo de adyacencias
  int * base;
  // Número de elementos del arreglo a ordenar 
  size_t nmemb;
  size_t size = sizeof(int);
  int i;
  for(i = 0; i < vertex_num; i++) {
    base = graph[i].adjacents;
    nmemb = graph[i].adj_size;
    qsort(base, nmemb, size, compare_vertices);
  }
}

/***************************************************************/
/* Función que compara vértices. Es usada como parámetro para  */
/* las funciones bsearch y qsort (Binary Search y Quicksort    */
/* respectivamente).                                           */
/***************************************************************/ 
int compare_vertices(const void * __a, const void * __b) {
  int * a = (int *) __a;
  int * b = (int *) __b;
  if (*a < *b)
    return -1;
  if (*a > *b) 
    return 1;
  if (*a == *b)
    return 0;
}

/* Funcion que compara dos elementos tuple segun los  */
/* grados de los vértices. */

int compare_tuples(const void * __a, const void * __b) { 
  tuple * a = (tuple *) __a;
  tuple * b = (tuple *) __b;
  if (a->degree < b->degree) 
    return 1;
  if (a->degree > b->degree)
    return -1;
  if (a->degree == b->degree)
    return 0;
}

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

void degree_no_clique(Graph * graph, int * members, int size, tuple * deg_vert) {
  int i;
  int j=0;
  for(i = 0; i < size; i++) {
    if(!members[i]) {
      tuple new_tuple = { i, graph[i].adj_size };
      deg_vert[j] = new_tuple;
      ++j;
    }
  }
  tuple * base = deg_vert;
  size_t nmemb = size; 
  size_t msize = sizeof deg_vert[0]; 
  qsort(base, nmemb, msize, compare_tuples);
}


void free_tuple_list(tuple_list * list) {
  tuple_list * back;
  tuple_list * forward;
  back = list;
  forward = list;
  while (forward != NULL) {
    forward = back->next;
    free(back);
  }
}

int break_tie(tuple * base, struct Graph * graph, int vertex_num) {
  int vertex;
  int i;
  for(i = 0; i < vertex_num; i++) {
    if(graph[base[i].vertex].color == -1) {
      vertex = base[i].vertex;
      return vertex;
    }
  }
  // Todos los vértices se han coloreado 
  return -1;
}

/***********************************************************/
/* Función que realiza búsqueda lineal sobre la traza para */
/* encontrar el índica donde ocurre un vértice             */
/***********************************************************/
int lin_search(int * trace, int vertex, int depth) {
  int i;
  for(i = 0; i <= depth; i++) {
    if (trace[i] == vertex) 
      return i;
  }
  // Si no se consiguió el vértice en la traza
  // significa que su FC no fue válido.
  return -1;
}






