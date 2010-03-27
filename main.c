# include "main.h"

int main() {
  // Se calcula el número de vértices del grafo
  int vertex_num = get_vertex_num();
  Graph * graph = create_graph(vertex_num);
  
  // Se llena la estructura temporal con los vértices del grafo
  linked_list ** tmp_graph = fill_tmp_graph(vertex_num);

  //Se llena la estructura Graph con los vértices del grafo

  fill_graph(vertex_num, tmp_graph, graph);

  order_graph(vertex_num, graph);

  // Se prepara la estructura que contiene los vértices 
  // ordenados por orden decreciente de grados
  tuple * deg_vert = (tuple *) malloc(sizeof(tuple)*vertex_num);
  degree(graph, vertex_num, deg_vert);
  
  // Par clique-coloración
  pair result;

  double tiempo_inicial = timer();

  //COMIENZA ALGORITMO
  
  //Se activa la alarma que dará la señal de
  // terminación al programa si el algoritmo
  // excede los 5 minutos.
  //  signal(SIGALRM, alarmHandler);
  //  alarm(300);

  // Se obtiene cota superior
  result = dsatur(graph, deg_vert, vertex_num, -1);
  int upper_bound = result.coloring;
  // Se obtiene cota inferior corriendo
  // Brelaz+Interchange N veces
  int lower_bound = -1;

  // Arreglo que contiene los miembros de la máxima 
  // clique encontrada por Brelaz+Interchange
  int * members = determine_max_clique(graph, vertex_num,
                                       deg_vert,&lower_bound);
  
  free(deg_vert);
  deg_vert = (tuple *) malloc(sizeof(tuple)* (vertex_num - lower_bound));
  degree_no_clique(graph, members,vertex_num, deg_vert, lower_bound);
  printf("Resultados de Brelaz+interchange \n");
  printf("Cota superior = %d \n", upper_bound);
  printf("Cota inferior = %d \n", lower_bound);

  init_FC(graph, vertex_num, upper_bound);
  graph_init(graph, vertex_num);

  if (lower_bound == upper_bound)
    printf("Número cromático = %d \n", upper_bound+1);
  else {
    implicit_enum(&upper_bound, lower_bound, members, graph,
                  deg_vert, vertex_num);
  }
  
  // TERMINA ALGORITMO
  double tiempo_final = timer();
  
  printf("Tiempo en segundos de ejecución del programa: %1.4f \n", (tiempo_inicial - tiempo_final)*-1);

  free_graph(graph, vertex_num);
  free(deg_vert);
  free(members);
  return EXIT_SUCCESS;
}

/* CEMENTERIO */


/*   int i; */
/*   linked_list * aux; */
/*   for(i = 0; i < vertex_num; i++) { */
/*     printf("vértice %d \n",i+1); */
/*     printf("-------------\n"); */
/*     aux = tmp_graph[i]; */
/*     while(aux != NULL) { */
/*       printf("%d \n", aux->vertex+1); */
/*       aux = aux->next; */
/*     } */
/*     printf("-------------\n"); */
/*   } */



  /* int i; */
  /* int j; */
  /* int * k; */
  /* for(i = 0; i < vertex_num; i++) { */
  /*   printf("vértice %d \n",i+1); */
  /*   printf("-------------\n"); */
  /*   k = graph[i].adjacents; */
  /*   for(j = 0; j < graph[i].adj_size; j++) */
  /*     printf("%d \n", k[j]+1); */
  /*   printf("-------------\n"); */
  /* } */


