# include "build_graph.h"

int get_vertex_num() {
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  regex_t * __restrict compiled_num = (regex_t *) malloc(sizeof (regex_t)); 
  (void) regcomp(compiled_num, "^p", REG_EXTENDED);   //  Compilacion de RegEx para numero de vertices
  char * dump = (char *) malloc(sizeof(char)*12);
  int vertex_num;
  int dump2;
  // Comienza lectura de la entrada estandar
  while ((read = getline(&line, &len, stdin)) != -1) {
    if (regexec(compiled_num, line, 0, NULL, 0) == 0) {
      sscanf(line,"%c %s %d %d", dump, dump,&vertex_num,&dump2);
      break;
      // ahora vertex_num contiene numero de vertices en grafo
    }
  }
  free(compiled_num);
  free(dump);
  return vertex_num;
}

Graph * create_graph(int vertex_num) {
  struct Graph * graph = (Graph *) malloc(sizeof(Graph) * vertex_num);
  int i;
  for (i = 0; i < vertex_num ; i++) {
    graph[i].adjacents = NULL;
    graph[i].adj_size = 0;
    graph[i].color = -1; // Color inicial
    graph[i].color_around = (int *) malloc(sizeof(int)*vertex_num); 
    int j;
    for(j = 0; j < vertex_num; j++) 
      // Inicialización de arreglo de colores adyacentes
      graph[i].color_around[j] = 0;
  }
  return graph;
}
  
struct linked_list ** fill_tmp_graph(int vertex_num) {
  linked_list ** tmp_graph = (linked_list **) malloc(sizeof(linked_list *) * vertex_num);
  regex_t * __restrict compiled_edge = (regex_t *) malloc(sizeof (regex_t));
  (void) regcomp(compiled_edge,"^e (.) (.)", REG_EXTENDED);   // Compilacion de RegEx para vertices  
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int d1;  
  int d2;
  int dump;
  // Lectura del resto del archivo
  while ((read = getline(&line, &len, stdin)) != -1) {
    if (regexec(compiled_edge, line, 0, NULL, 0) == 0) { 
      sscanf(line,"%c %d %d", dump,&d1,&d2);
      d1 -= 1;
      d2 -= 1;
      if (d1 != d2) {
        // Arco d1 --> d2
        linked_list * adjacent1 = (linked_list *) malloc(sizeof(linked_list)); 
        adjacent1->vertex = d2;
        // Insercion de elementos de lista por la izquierda
        adjacent1->next = tmp_graph[d1];
        tmp_graph[d1] = (struct linked_list *) adjacent1;
        // Arco d2 --> d1
        linked_list * adjacent2 = malloc(sizeof(linked_list)); 
        adjacent2->vertex = d1;
        // Insercion de elementos de lista por la izquierda
        adjacent2->next = tmp_graph[d2];
        tmp_graph[d2] = (struct linked_list *) adjacent2;
      }
    }
  }
  free(compiled_edge);
  return tmp_graph;
}

void fill_graph(int vertex_num, struct linked_list ** tmp_graph, Graph * graph) {
  int i;
  int j;
  linked_list * aux;
  int len;
  for(i = 0; i < vertex_num; i++) {
    len = list_length(*tmp_graph[i]);
    graph[i].adj_size = len;
    graph->adjacents = (int *) malloc(sizeof(int) * len);
    aux = tmp_graph[i];
    for(j = 0; j < len; j++) {
        graph->adjacents[j] = aux->vertex;
        aux = aux->next;
    }
  }
  free_tmp_graph(tmp_graph);
}
