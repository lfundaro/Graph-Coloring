# include "backwards.h"


void backwards(int * trace, int * max_used_color,
               int * first_max_color, int * current_vertex,
               int * satur_degree, Graph * graph, tuple * base,
               int * ties_num, int * popularity, int * coloring,
               int depth, int upper_bound) {
  
  // Aplicar labeling
  
  printf("");
  
  
}

/*************************************************************/
/* Función que al vértice donde se reanuda el backtrack le   */
/* quita de su estructura FC todos los colores comprendidos  */
/* entre max_used_color y upper_bound.                       */
/*************************************************************/
void set_new_FC(Graph * graph, int start_point,
                int * max_used_color, int upper_bound) {
  int i;
  for(i = *max_used_color; i < upper_bound; i++) 
    graph[start_point].FC[i] = 0;
}

linked_list * label(Graph * graph, int * first_max_color, 
                    int * max_used_color, int upper_bound,
                    int * trace) {
  int i = 0;
  
  while(i < *first_max_color) {
    if (is_adjacent(trace,&i,*first_max_color, graph))
      printf("");
      }

}

int * is_adjacent(int * trace, int * key, int first_max_color,
                Graph * graph) {
  int * base = graph[first_max_color].adjacents;
  int nmemb = graph[first_max_color].adj_size;
  size_t size = sizeof(int);
  int * result;
  result = bsearch((void *) key, base, nmemb, size, compare_vertices);
  return result;
}

void new_max_color(int * popularity, int * trace,
                   int * first_max_color,
                   int * max_used_color) {
  // Esta función va a modificar el nuevo máximo 
  // color.
}


/***************************************************/
/* Mientras se va subiendo los niveles del árbol   */
/* se va decoloreando los vértices, por lo que se  */
/* deben actualizar las estructuras popularity,    */
/* color_around, FC, satur_degree, graph y base.   */
/***************************************************/
void update_all(int * trace, Graph * graph, 
                tuple * base, int * popularity, 
                int depth, int * first_max_color, 
                int * satur_degree) {


  int i;
  for(i = depth; i >= *first_max_color; i--) {
    // Actualizamos color_around de vértices adyacentes
    // al decolorear vértice que está en trace[i]
    uncolor(graph, trace[i], graph[trace[i]].color);

    //Actualización de tabla de popularidad
    popularity[graph[trace[i]].color]--;

    // Decoloreamos el vértice
    graph[trace[i]].color = -1;    
    
    // Bajamos grado de saturación a los vecinos
    // y restablecemos el grado de saturación a 0 
    // para el vértice decoloreado.
    uncolor_satur(satur_degree, graph, trace[i]);
    
  // Se actualiza la base que apunta al arreglo de 
  // vértice-grado (deg_vert)
    update_base(trace, trace[i], base);
  }
}
                

/*************************************************************/
/* El apuntador base se utiliza para dar el proximo vértice  */
/* a colorear en caso de que existe un empate en grados de   */
/* saturación. En el momento de decolorear un vértice,       */
/* si éste es igual al elemento apuntado por base, entonces  */
/* el apuntador se debe decrementar para restablecer         */
/* el orden de coloración en caso de existir un empate.      */
/*************************************************************/
void update_base(int * trace, int vertex, tuple * base) {
  if (trace[vertex] == base->vertex) 
    base--;
}


/**************************************************************/
/* Esta función se utiliza para bajar el grado de saturación  */
/* de los vécinos de un vértice que está siendo decoloreado   */
/**************************************************************/
void uncolor_satur(int * satur_degree, Graph * graph, int vertex) {
  int * adj = graph[vertex].adjacents;
  int adj_size = graph[vertex].adj_size;
  int i;
  satur_degree[vertex] = 0;
  for(i = 0; i < adj_size; i++) 
    satur_degree[graph[vertex].adjacents[i]]--;
}

