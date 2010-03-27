# include "backwards.h"


void backwards(int * trace, int * max_used_color,
               int * vertex_max_color, int * current_vertex,
               int * satur_degree, Graph * graph, tuple * base,
               int * popularity, int * coloring,
               int * depth, int upper_bound, int lower_bound, 
               int vertex_num, int * members) {
  
  // Se determina la posición en la traza donde se encuentra
  // el vértice desde el cual se hace backtracking
  int vertex_position = lin_search(trace, *current_vertex, *depth);
  
  // Se averigua si el vértice de donde se parte
  // el backtracking es la raiz
  if (vertex_position == 0) {
    int vertex_color = graph[trace[vertex_position]].color;
    update_all(trace, graph, base, popularity, *depth,
               vertex_position, satur_degree);
    // Quitamos su color del FC
    graph[trace[vertex_position]].FC[vertex_color] = 0;

    // Se determina el máximo color utilizado hasta ahora
    max_color(popularity, max_used_color, upper_bound);
    
    if (valid_FC(graph, trace[vertex_position],lower_bound+1)) {
      *current_vertex = trace[vertex_position];
      *vertex_max_color = 0;
      *depth = 0;
      return;
    }
    else {
      // Se ha llegado a la raiz y no hay mas colores 
      // posibles que introducir
      *current_vertex = -1;
      return;
    }
  }
  // Caso en el que el vértice no es raiz
  else {

    // Variable aux que lleva el último vértice descoloreado en 
    // mientras se busca un vértice entre todos los etiquetados
    // que sea útil para el forward, es decir, que su U(x) sea 
    // no vacío.
    int aux;

    if (vertex_position == *depth) {
      // Significa que el vértice donde quedó forward 
      // tuvo FC vació, por lo tanto no se encontró en 
      // la traza. Se llama directamente label
      label(graph, *depth,trace, *max_used_color,
            members);
      aux = *depth - 1;
      vertex_position = *depth - 1;
    }
    else {
      // Se quitan todos los labels a partir del vértice 
      // de máximo color
      unlabel(graph, trace, vertex_position, vertex_num);

      // Se logró una coloración completa. Por lo tanto:
      // Se decolorean todos los vértices subiendo en el 
      // árbol hasta llegar al vértice de mínimo rango 
      // con el mayor color usado en la coloración parcial actual
      update_all(trace, graph, base, popularity, *depth,
                 vertex_position, satur_degree);
      
      // Se determina el nuevo máximo color utilizado 
      // ya que se decolorearon vértices que estaban 
      // entre el último vértice del árbol y el que tiene 
      // el color q de rango mínimo.
      max_color(popularity, max_used_color, upper_bound);

      // Se procede a hacer el etiquetado partiendo del vértice
      // con coloración más alta y de rango mínimo.
      label(graph, vertex_position, trace, *max_used_color,
            members);
      
      aux = vertex_position;
    }

    // Se busca el vértice etiquetado con mayor rango
    // subiendo en el árbol tomando como punto de partida
    // el nodo padre del vértice con el mayor color utilizado
    // O aquel cuyo FC se hizo vació

    int i;

    for(i = vertex_position; i >= 0; i--) {
      // Se verifica si el nodo está etiquetado
      if (graph[trace[i]].label.flag) {
        int vertex_color = graph[trace[i]].color;
        // Se procede a decolorear y actualizar estructuras
        // Se decolorea desde el vértice aux hasta el 
        // vértice candidato etiquetado.
        update_all(trace, graph, base, popularity,
                   aux, i, satur_degree);

        // Se pone aux a un nivel arriba del vértice candidato 
        // en caso de que el vértice resulte no tener un FC 
        // válido.
        aux = i - 1;
      
        // Se elimina de su FC el color que tiene actualmente
        graph[trace[i]].FC[vertex_color] = 0;
      
        // Se determina el máximo color
        max_color(popularity, max_used_color, upper_bound);

        // Se elimina la etiqueta del vértice
        graph[trace[i]].label.flag = 0;
        
        // Se verifica que su FC no sea vacío
        // Al ser no vacío se retorna el algoritmo
        if (valid_FC(graph, trace[i], *max_used_color)) {
          // Se determina la posición en la traza
          // del vértice de mínimo rango que tiene
          // el color máximo utilizado
          det_vertex_max_color(graph, trace,*max_used_color,
                               vertex_max_color, i);
          // Se indica el vértice del cual se parte
          // y su posición en la traza (depth)
          *current_vertex = trace[i];
          *depth = i;
          return;
        }
        // Si su FC es vacío se busca el próximo vértice
        // de mayor rango entre los etiquetados
      }
    }
    // La lista CP está vacía por lo tanto se retorna el
    // algoritmo con current_vertex siendo -1.
    *current_vertex = -1;
    return;
  }
}



void max_color(int * popularity, int * max_used_color, int upper_bound) {
  // Se recorre la tabla de popularidad desde el color 
  // upper_bound hasta el inicio de la tabla en busca del
  // primer color que tenga popularidad distinta de cero.
  int i;
  for(i = (upper_bound-1); i >= 0; i--) {
    if (popularity[i] > 0) 
      *max_used_color = i;
  } 
}

/***********************************************************/
/* Procedimiento que determina el vértice de mínimo rango  */
/* con el máximo color utilizado hasta el momomento.       */
/***********************************************************/
void det_vertex_max_color(Graph * graph, int * trace,
                          int max_used_color, 
                          int * vertex_max_color, int bound) {
  int i;
  for(i = 0; i < bound; i++) {
    if (graph[trace[i]].color == max_used_color) 
      *vertex_max_color = trace[i];
  } 
}

/*******************************************************/
/* Función que indica si un conjunto FC es vacío o no. */
/*******************************************************/
int valid_FC(Graph * graph, int vertex, int max_used_color) {
  int i;
  int is_valid = 0;
  for(i = 0; i <= max_used_color + 1; i++)
    is_valid = is_valid | graph[vertex].FC[i];
  return is_valid;
}


/**************************************************************/
/* Procedimiento de etiquetado. Toma los vértices             */
/* de menor rango a partir del vértice que se                 */
/* encuentra en la posición vertex_position de                */
/* la traza y les aplica las propiedades que exige            */
/* el procedimiento label. Etiquetar un vértice significa     */
/* ir a su representación de nodo en la estructura graph      */
/* e indicar con un flag que ha sido marcado como etiquetado  */
/* y además se indica la posición que éste ocupa en la traza. */
/**************************************************************/
void label(Graph * graph, int vertex_position, int * trace, int max_used_color, int * members) {
  // Inicialización de estructura de control de los
  // colores que se encuentran mientras se asciende
  // en el arbol para hacer labeling
  int i;
  int * colors = (int *) malloc(sizeof(int)* (max_used_color+1));
  for(i = 0; i < max_used_color; i++)
    colors[i] = 0;

  // Se comienza a etiquetar los vértices
  // Nótese que el etiquetado se hace comenzando desde
  // la raíz, en vez de partir desde el vértice hasta
  // la raíz.
  for(i = 0; i < vertex_position; i++) {
    if (is_adjacent(&trace[i],trace[vertex_position], graph)
        && !clique_member(members,trace[i])) {
      int color_candidate = graph[trace[i]].color;
      if (colors[color_candidate] == 0) {
        colors[color_candidate] = 1;
        // Buscamos el vértice en el grafo para
        // marcarlo como etiquetado e indicar la
        // posición en la traza donde fue encontrado
        graph[trace[i]].label.flag = 1;
        graph[trace[i]].label.position = i;
      }
    }
  }
  free(colors);
}

/********************************************************/
/* Procedimiento utilizado para quitar etiquetas desde  */
/* el vértice X_k hasta el vértice X_n.                 */
/********************************************************/
void unlabel(Graph * graph, int * trace, int start_vertex,
             int vertex_num) {
  int i;
  for(i = start_vertex; i < vertex_num; i++)
    graph[trace[i]].label.flag = 0;
}


/*************************************************************/
/* Función que aplica búsqueda binaria sobre los vértices    */
/* adyacentes de v_2 para conseguir al vértice v_1. En caso  */
/* de encontrarlo retorna un apuntador distinto de nulo, de  */
/* lo contrario retorna un apuntador nulo.                   */
/*************************************************************/
int * is_adjacent(int * v_1, int v_2,
                  Graph * graph) {
  int * base = graph[v_2].adjacents;
  int nmemb = graph[v_2].adj_size;
  size_t size = sizeof(int);
  int * result;
  result = (int *) bsearch((void *) v_1, base, nmemb, size, compare_vertices);
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
    
    i--;
  }
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


int clique_member(int * members, int vertex) {
  if (members[vertex] == 1) {
    return 1;
  }
  else 
    return 0;
}



/*************************************************************/
/* El apuntador base se utiliza para dar el proximo vértice  */
/* a colorear en caso de que existe un empate en grados de   */
/* saturación. En el momento de decolorear un vértice,       */
/* si éste es igual al elemento apuntado por base, entonces  */
/* el apuntador se debe decrementar para restablecer         */
/* el orden de coloración en caso de existir un empate.      */
/*************************************************************/
/* void update_base(int * trace, int vertex, tuple * base) { */
/*   if (trace[vertex] == base->vertex)  */
/*     base--; */
/* } */



/* // Se procede a hacer el etiquetado partiendo del vértice  */
/* // con coloración más alta y de rango mínimo. */
/* label(graph,*vertex_max_color, *max_used_color, trace); */



/* tuple_list * label(Graph * graph, int trace_position,  */
/*                    int max_used_color, int * trace, */
/*                    int current_vertex) { */
/*   int i; */
/*   int * colors = (int *) malloc(sizeof(int) * max_used_color); */
/*   tuple_list * candidates = NULL; */
/*   // Inicialización de estructura de control de los */
/*   // colores que se encuentran mientras se desdeciende  */
/*   // en el arbol para hacer labeling */
/*   for(i = 0; i < max_used_color; i++)  */
/*     colors[i] = 0; */
 
/*   i = 0; */
/*   // Se comienza a etiquetar los vértices */
/*   // Nótese que el etiquetado se hace comenzando desde */
/*   // la raíz, en vez de partir desde el vértice hasta */
/*   // la raíz. */
/*   for(i = 0; i < trace_position; i++) { */
/*     if (is_adjacent(&trace[i], current_vertex, graph)) { */
/*       int color_candidate = graph[trace[i]].color; */
/*       if (colors[color_candidate] == 0) { */
/*         colors[color_candidate] = 1; */
/*         tuple_list * tmp =  (tuple_list *) malloc(sizeof(tuple_list)); */
/*         tmp->vertex = trace[i]; */
/*         tmp->position = i; */
/*         tmp->next = candidates; */
/*         candidates = tmp; */
/*       } */
/*     } */
/*   } */
/*   free(colors); */
/*   return candidates; */
/* } */


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

    

/*       int vertex_color = graph[candidates->vertex].color; */
 
/*       // Se decolorean todos los vértices que están a partir */
/*       // de una posición anterior desde donde se hizo labeling  */
/*       // hasta el vértice de rango máximo entre todos los  */
/*       // etiquetados */
/*       update_all(trace, graph, base, popularity, */
/*                  vertex_position - 1, candidates->position, */
/*                  satur_degree); */
 
/*       // Se elimina de su FC el color que tiene actualmente */
/*       graph[candidates->vertex].FC[vertex_color] = 0; */
    
/*       // Se determina el máximo color utilizado hasta ahora */
 
/*       max_color(popularity, max_used_color, upper_bound); */
 
/*       // Se verifica que el vértice de máximo rango etiquetado */
/*       // no tenga un FC vacío. Al ser su FC no vació se hace */
/*       // retornar el algoritmo */
    
/*       if (valid_FC(graph, candidates->vertex, *max_used_color)) { */
/*         // Se determina la posición en la traza */
/*         // del vértice de mínimo rango que tiene */
/*         // el color máximo utilizado */
/*         det_vertex_max_color(graph, trace,*max_used_color, */
/*                              vertex_max_color, candidates->position); */
/*         // Se indica la posición en la traza del vértice  */
/*         // del cual se parte para hacer forward. */
/*         *current_vertex = candidates->vertex; */
/*         *depth = candidates->position; */
/*         free_tuple_list(candidates); */
/*         return; */
/*       } */
/*       else { */
/*         tuple_list * tmp = candidates; */
/*         candidates = candidates->next; */
/*         tmp->next = NULL; */
/*         free_tuple_list(tmp); */
/*       } */
/*     } */
/*   } */
/*   // La lista CP está vacía por lo tanto se retorna el */
/*   // algoritmo con current_vertex siendo cero. */
/*   *current_vertex = -1; */
/*   return; */
/* } */

