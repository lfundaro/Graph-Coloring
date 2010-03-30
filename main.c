# include "main.h"

int check_col(Graph * graph, int vertex_num) {
  int i;
  int j;
  
  for(i = 0; i < vertex_num; i++) {
    for(j = 0; j < graph[i].adj_size; j++) {
      if (graph[graph[i].adjacents[j]].color == graph[i].color 
          || graph[graph[i].adjacents[j]].color == -1
          || graph[i].color == -1) {
        exit(1);
        printf("error \n");
      }
      
    }
  }
  printf("correcto ! \n");
  return 1;
}

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
   signal(SIGALRM, alarmHandler);
   alarm(300);

  // Se obtiene cota superior
  result = dsatur(graph, deg_vert, vertex_num, -1);

  /* printf("coloracion %d \n", result.coloring); */
  /* if (check_col(graph,vertex_num)) */
  /*   printf("Yeeeeeeeeeei\n"); */
  /* else */
  /*   printf("Inutil\n"); */
  //  return EXIT_SUCCESS;
  
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
    printf("Número cromático = %d \n", upper_bound);
  else {
    upper_bound -= 1;
    lower_bound -= 1;
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




  /* int t; */
  /* int h; */
  /* for(h = 0; h < vertex_num; h++) { */
  /*   printf("Vértice %d \n", h+1); */
  /*   printf("----------\n"); */
  /*   int adj_size = graph[h].adj_size; */
  /*   for(t = 0; t < adj_size; t++) */
  /*     printf("%d \n", graph[h].adjacents[t]+1); */
  /*   printf("\n"); */
  /* } */
  /* return EXIT_SUCCESS; */


  //  int h;
  // linked_list * aux;
  /* for(h = 0; h < vertex_num-400; h++) { */
  /*   printf("Vértice %d \n", h+1); */
  /*   printf("----------\n"); */
  /*   aux = tmp_graph[h]; */
  /* while(aux != NULL) { */
  /*   printf("%d \n", aux->vertex+1); */
  /*   aux = aux->next; */
  /* } */
  /* printf("\n"); */
  /* } */



