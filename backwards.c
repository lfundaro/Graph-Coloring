# include "backwards.h"


void backwards(int * trace, int * max_used_color,
               int * first_max_color, int * current_vertex,
               int * satur_degree, Graph * graph, tuple * base,
               int * ties_num, int * popularity, int * coloring,
               int depth, int upper_bound) {
  
  // Se decolorean todos los vértices subiendo en el 
  // árbol hasta llegar al vértice de mínimo rango 
  // con el mayor color usado en la coloración parcial actual
  update_all(trace, graph, base, popularity, depth,
             *first_max_color, satur_degree);

  // Se procede a hacer el etiquetado partiendo del vértice 
  // con coloración más alta y de rango mínimo.
  tuple_list * candidates = label(graph, first_max_color, 
                                  max_used_color, trace);

  // Se verifica que la lista de candidatos del label 
  // sea distinta de Nula. En caso contrario no hay más 
  // backtracking que hacer y se consiguió una coloración
  while (candidates != NULL) {

    // Se decolorean todos los vértices que están entre 
    // el vértice donde se hizo el labeling hasta el 
    // vértice de rango máximo entre todos los etiquetados
    update_all(trace, graph, base, popularity, 
               *first_max_color - 1, candidates->position, 
               satur_degree);
    
    // Se determina el máximo color utilizado hasta ahora

    max_color(popularity, max_used_color, upper_bound);

    // Se verifica que el vértice de máximo rango etiquetado 
    // no tenga un FC vacío
    
    if (valid_FC(graph, candidates->vertex, max_used_color)) {
      // Como el FC es válido, es decir, distinto de vacío 
      // entonces se procede a decolorearlo y quitarle de su 
      // conjunto FC el color que tiene actualmente

      update_all(trace, graph, base, popularity,
                 candidates->position, candidates->position,
                 satur_degree);

      // Modificación de FC
      int vertex_color = graph[candidates->vertex].color;
      graph[candidates->vertex].FC[vertex_color] = 0;

      // Se procede a inicializar current_vertex
      *current_vertex = candidates->vertex;
      *first_max_color = candidates->position;
      free_tuple_list(candidates);
      return;
    }
    else {
      tuple_list * tmp = candidates;
      candidates = candidates->next;
      tmp->next = NULL;
      free_tuple_list(tmp);
    }
  }
  
  // La lista CP está vacía por lo tanto se retorna el 
  // algoritmo con current_vertex siendo cero.
  *current_vertex = 0;
  return;
}

void max_color(int * popularity, int * max_used_color, int upper_bound) {
  // Se recorre la tabla de popularidad desde el color 
  // upper_bound hasta el inicio de la tabla en busca del
  // primer color que tenga popularidad distinta de cero.
  int i;
  for(i = upper_bound; i >= 0; i--) {
    if (popularity[i] > 0) 
      *max_used_color = i;
  } 
}



int valid_FC(Graph * graph, int vertex, int max_used_color) {
  int vertex_color = graph[vertex].color;
  int i = 0;
  int is_valid = 1;
  while(i < vertex_color) {
    is_valid = is_valid & graph[vertex].FC[i];
    i++;
  }
  i++;
  while(i <= max_used_color) {
    is_valid = is_valid & graph[vertex].FC[i];
  }
  return is_valid;
}

/*************************************************************/
/* Función que al vértice donde se reanuda el backtrack le   */
/* quita de su estructura FC todos los colores comprendidos  */
/* entre max_used_color y upper_bound.                       */
/*************************************************************/
/* void set_new_FC(Graph * graph, int start_point, */
/*                 int upper_bound, int coloring) { */
/*   int i; */
/*   for(i = max_used_color; i < coloring; i++)  */
/*     graph[start_point].FC[i] = 0; */
/* } */

tuple_list * label(Graph * graph, int * first_max_color, 
                    int * max_used_color, int * trace) {
  int i;
  tuple_list * candidates = NULL;
  int * colors = (int *) malloc(sizeof(int) * (*max_used_color));
  // Inicialización de estructura de control de los
  // colores que se encuentran mientras se desdeciende 
  // en el arbol para hacer labeling
  for(i = 0; i < *max_used_color; i++) 
    colors[i] = 0;

  i = 0;
  // Se comienza a etiquetar los vértices
  while(trace[i] != *first_max_color) {
    if (is_adjacent(&trace[i],*first_max_color, graph)) {
      int color_candidate = graph[i].color;
      if (colors[color_candidate] == 0) {
        colors[color_candidate] = 1;
        tuple_list * tmp =  (tuple_list *) malloc(sizeof(tuple_list));
        tmp->vertex = trace[i];
        tmp->position = i;
        tmp->next = candidates;
        candidates = tmp;
      }
    }
    else {
      
    }
    i++;
  }
  free(colors);
  return candidates;
}

int * is_adjacent(int * key, int first_max_color,
                Graph * graph) {
  int * base = graph[first_max_color].adjacents;
  int nmemb = graph[first_max_color].adj_size;
  size_t size = sizeof(int);
  int * result;
  result = (int *) bsearch((void *) key, base, nmemb, size, compare_vertices);
  return result;
}



/***************************************************/
/* Mientras se va subiendo los niveles del árbol   */
/* se va decoloreando los vértices, por lo que se  */
/* deben actualizar las estructuras popularity,    */
/* color_around, FC, satur_degree, graph y base.   */
/***************************************************/
void update_all(int * trace, Graph * graph, 
                tuple * base, int * popularity, 
                int depth, int start_point, 
                int * satur_degree) {

  // Actualizamos todos los vértices desde el nivel 
  // de más profundo del árbol (depth) donde se detuvo 
  // el procedimiento forwards.
  int i = depth;
  while(i >= start_point) {
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
    i--;
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

