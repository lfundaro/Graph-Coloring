#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

int list_length(linked_list * list){
  int len = 0;
  while (list != NULL){
    len += 1;
    list = list->next;
  }
  return len;
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
  for(i = 0; i < vertex_num; i++) 
    free(graph[i].color_around);
  free(graph);
}

void free_tmp_graph(int vertex_num, struct linked_list * tmp_graph) {
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






