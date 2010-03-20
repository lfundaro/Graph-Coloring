# include "main.h"

int main() {
  // Se calcula el número de vértices del grafo
  //  int vertex_num = get_vertex_num();
  // Graph * graph = create_graph(vertex_num);
  
  // Se llena la estructura con los vértices del grafo
  // fill_graph(vertex_num, graph);

  // Se prepara la estructura que contiene los vértices 
  // ordenados por orden decreciente de grados
  /* tuple * deg_vert = (tuple *) malloc(sizeof(tuple)*vertex_num); */
  /* degree(graph, vertex_num, deg_vert); */
  
  /* // Par clique-coloración */
  /* pair result;  */

  /* double tiempo_inicial = timer(); */

  /* //COMIENZA ALGORITMO */
  
  /* //Se activa la alarma que dará la señal de  */
  /* // terminación al programa si el algoritmo  */
  /* // excede los 5 minutos. */
  /* signal(SIGALRM, alarmHandler); */
  /* alarm(300);  */

  /* // Se obtiene cota superior */
  /* result = dsatur(graph, deg_vert, vertex_num, -1); */
  /* int upper_bound = result.coloring; */
  /* // Se obtiene cota inferior corriendo */
  /* // Brelaz+Interchange N veces */
  /* int lower_bound = -1; */
  /* // Arreglo donde están los vértices  */
  /* // que forman la clique máxima. */
  /* int * members; */

  /* int i; */
  /* for(i = 0; i < vertex_num; i++) { */
  /*   graph_init(graph, vertex_num); */
  /*   result = dsatur(graph, deg_vert, vertex_num, i); */
  /*   if (result.clique > lower_bound) { */
  /*     lower_bound = result.clique; */
  /*     members = result.members; */
  /*     continue; */
  /*   } */
  /*   free(result.members); */
  /* } */

  /* printf("Resultados de Brelaz+interchange \n"); */
  /* printf("Cota superior = %d \n", upper_bound); */
  /* printf("Cota inferior = %d \n", lower_bound); */
  /* if (lower_bound == upper_bound) */
  /*   printf("Número cromático = %d \n", upper_bound); */
  /* else { */
  /*   // Aqui va el algoritmo de Enumeracion Implicita nuevo. */
  /* } */

  /* // TERMINA ALGORITMO */
  /* double tiempo_final = timer(); */
  
  /* printf("Tiempo en segundos de ejecución del programa: %1.4f \n", (tiempo_inicial - tiempo_final)*-1); */

  /* free_graph(graph, vertex_num); */
  /* free(deg_vert); */
  /* free(members); */
  return EXIT_SUCCESS;
}


