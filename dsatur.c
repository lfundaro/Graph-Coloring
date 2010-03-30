# include "dsatur.h"
# include "Forward.h"

pair dsatur(Graph graph[], tuple deg_vert[], int vertex_num, int start_point) {
  // Ordenamiento decreciente de grados de vertices
  tuple * base = &deg_vert[0];  // Apuntador a primer elemento
  size_t nmemb = vertex_num; // Número de elementos
  size_t size = sizeof deg_vert[0]; // Tamaño de un elemento
  int last_color; // Último color utilizado que sea mayor
  int num_colored = 0; // Número de vértices coloreados
  int used_colors[vertex_num]; 
  int upper_bound = 0; //Coloración lograda 
  int lower_bound = 0; //Clique máxima encontrada
  int * highest_color = (int *) malloc(sizeof(int));  
  *highest_color = 0;
  int flag = 1;
  int i; 

  for(i = 0; i < vertex_num; i++) 
    used_colors[i] = 0;   
  int v_i;
  // Arreglo de grados de saturación
  int * satur_degree = (int *) malloc(sizeof(int)*vertex_num);
  // Inicialización de estructura de grados de saturación
  for(i = 0; i < vertex_num; i++) 
    satur_degree[i] = 0;
  
  // Coloración del primer vértice
  if (start_point == -1) { //Se parte del vértice de grado mayor
    //Ordenamiento decreciente
    qsort(base, nmemb, size, compare_tuples);
    v_i = get_max_degree(base,graph,vertex_num);
  }
  else
    //Start_point se usa cuando se corre el algoritmo N veces
    v_i = start_point; 


  graph[v_i].color = 0;
  last_color = 0;
  used_colors[last_color] = 1;  //Color se marca como usado
  lower_bound++;
  num_colored++;
  int * members = (int *) malloc(sizeof(int) * vertex_num);
  initialize(members, vertex_num);
  members[v_i] = 1;
  // El grado de saturación de un vértice coloreado ya no nos 
  // interesa, por lo tanto lo ponemos en -1
  satur_degree[v_i] = -1;  
  // Actualizar saturación de vecinos
  update_satur(graph, satur_degree, v_i, last_color);
  // Pasos 3, 4, 5 de DSATUR, agregando intercambio
  int max; //Lleva la máxima saturación
  int found; //Dice dónde se encontró vértice de máx. saturación
  while (num_colored < vertex_num) {
    max = -1; //Elemento neutro de saturación;
    //Se busca el elemento con mayor grado saturación
    for(i = 0; i < vertex_num; i++) {
      if (max < satur_degree[i]) {
        max = satur_degree[i];
        found = i;
      }
    }
    //Busco repeticiones del mayor
    if (repeated(max, satur_degree, vertex_num, found)) {
      v_i = get_max_degree(base,graph,vertex_num);
      last_color = leastp_color(graph, v_i, vertex_num);
      //Hacer intercambio si es posible
      check_interchange(&last_color,highest_color,used_colors,
                        graph, num_colored, satur_degree,
                        vertex_num, v_i);
      //Se colorea finalmente el vértice
      graph[v_i].color = last_color;
    }
    else {
      v_i = found;
      last_color = leastp_color(graph, v_i, vertex_num);
      //Hacer intercambio si es posible
      check_interchange(&last_color,highest_color,used_colors,
                        graph, num_colored, satur_degree,
                        vertex_num, v_i);


      //Se colorea finalmente el vértice
      graph[v_i].color = last_color;
    }

    if (used_colors[last_color] == 0) { //Coloración de clique
      if (makes_clique(graph, v_i, members, vertex_num)) {
        members[v_i] = 1;
        lower_bound++;
      }
    }
    else {
      if (start_point != -1) {
        //Verificamos si v_i hace clique con los vértices que 
        //ya conocemos hacen clique
        if (makes_clique(graph, v_i, members, vertex_num)) {
          lower_bound++;
          members[v_i] = 1;
        }
      }
    }
    //Se marca el color usado como usado solo cuando 
    //corremos DSATUR para encontrar 
    used_colors[last_color] = 1;
    //Grado de saturación en -1 porque no nos interesa 
    //actualizar tal grado para un vértice ya coloreado
    satur_degree[v_i] = -1;  
    //Se actualiza el arreglo color_around de los vértices
    //adyacentes a v_i
    update_satur(graph, satur_degree, v_i, last_color);
    //Si estamos buscando la máxima clique entonces 
    //a los vértices adyacentes a v_i le quitamos el color
    //"last_color" en su arreglo de colores adyacentes
    
    num_colored++; 
  }
  
  if (start_point != -1) { //Hacemos retornar el algoritmo
    pair early_result;
    early_result.clique = lower_bound;
    early_result.members = members;
    free(satur_degree);
    free(highest_color);
    return early_result;
  }
  
  
  for(i = 0; i < vertex_num; i++){
    if (used_colors[i] == 1)
      upper_bound++;  //Se cuenta número de colores usados
  }
  free(members);
  free(highest_color);
  free(satur_degree);
  pair result;
  result.clique = lower_bound;
  result.coloring = upper_bound;

  return result;
}

//Determina repeticiones en dsatur_degree
//Cuando se elige un vértice con mayor grado de saturación
//se quiere saber si existe otro que tiene el mismo grado 
//para así descartar la posibilidad de buscar el de grado
//mayor de incidencias.
int repeated(int max, int * satur_degree, int vertex_num, int found) {
  int i;
  for(i = 0; i < vertex_num; i++) {
    if (max == satur_degree[i] && i != found)
      return 1;
  } 
  return 0;
} 

// Actualiza los grados de saturación de colores adyacentes
void update_satur(Graph * graph, int * satur_degree, int v_i, int color) {
  // Buscar los adyacentes a v_i
  // Si el vértice ya fue coloreado entonces no actualizo 
  // su grado de saturación
  int i;
  int * adjacents = graph[v_i].adjacents;
  int adj_size = graph[v_i].adj_size;
  for(i = 0; i < adj_size; i++) {
    if (satur_degree[adjacents[i]] != -1) {
      // Quiero saber si el vértice adyacente a v_i tiene en su 
      // arreglo de colores adyacentes el color "color".
      if (graph[adjacents[i]].color_around[color] == 0) 
        satur_degree[adjacents[i]] += 1;
      graph[adjacents[i]].color_around[color]++;
    }
  }
}


// Devuelve el próximo vértice de grado mayor e incrementa
// el apuntador base al próximo elemento.
int get_max_degree(tuple * base, struct Graph * graph, int vertex_num) {
  int vertex;
  while(1) {
    //Vértice que se devuelve no puede estar ya coloreado
    if (graph[base->vertex].color == -1) {
      vertex = base->vertex;
      base++;
      return vertex;
    }
    else
      base++;
  }
}

//Función que retorna el color más pequeño
//Revisa en el arreglo color_around del vértice v_i que se 
//quiere colorear cuál es la primera casilla que aparece en 0 
//para así utiliza dicho color. 
//Cuando la casilla está en 0 indica ausencia de color.
//Cuando está en 1 indica presencia de color.
int leastp_color(struct Graph * graph,int v_i,int vertex_num) {
  int i;
  for(i = 0; i < vertex_num; i++) {
    if (graph[v_i].color_around[i] == 0)
      return i;
  }
}

//Función que descolorea un vértice para detectar 
//más fácilmente una clique máxima
void uncolor(struct Graph * graph, int v_i, int color) {
  int * adjacents = graph[v_i].adjacents;
  int i;
  for(i = 0; i < graph[v_i].adj_size; i++) {
    //if (graph[i].color == -1){
      graph[adjacents[i]].color_around[color]--;
      //caCheck(graph,20,adjacents[i],color);
      //}
  }
}

int makes_clique(struct Graph * graph, int v_i, int * members, int vertex_num) {
  int i;
  int j;
  int is_there = 0;
  int decision = 1;
  int * adjacents;
  for(i = 0; i < vertex_num; i++) {
    is_there = 0;
    if (members[i] == 1) {
      adjacents = graph[v_i].adjacents;
      for(j = 0; j < graph[v_i].adj_size; j++) {
        if (adjacents[j] == i) {
          is_there = 1;
          break;
        }
      }
      decision = decision & is_there;
    }
  }
  return decision;
}

void check_interchange(int * last_color, int * highest_color, int * used_colors,
                       Graph * graph, int num_colored, int * satur_degree,
                       int vertex_num, int v_i) {
  if (*last_color > *highest_color)
    *highest_color = *last_color;
  //Chequeos para intercambio
  if (used_colors[*last_color] == 0) {
    //Se quiere hacer intercambio a partir del 4to vértice
    //que se va a colorear
    if (*highest_color > 0 && num_colored > 2) {
      interchange(graph, satur_degree, v_i, *highest_color, vertex_num);
      *last_color = leastp_color(graph, v_i, vertex_num);
    }
  }
}

/*****************************************/
/* Corrida de Brelaz+Interchange N veces */
/*****************************************/
int * determine_max_clique(Graph * graph, int vertex_num,
                           tuple * deg_vert, int * lower_bound) {
  int i;
  pair result;
  int * members;
  pair result_set[vertex_num];
  int chosen;
  for(i = 0; i < vertex_num; i++) {
    graph_init(graph, vertex_num);
    result_set[i] = dsatur(graph, deg_vert, vertex_num, i);
  }
  for(i = 0; i < vertex_num; i++) {
    if (result_set[i].clique > *lower_bound) {
      *lower_bound = result_set[i].clique;
      members = result_set[i].members;
      chosen = i;
    }
  }
  // Se libera memoria de las cliques candidatas que 
  // fueron descartadas
  for(i = 0; i < chosen; i++)
    free(result_set[i].members);
  for(i = chosen + 1; i < vertex_num; i++) 
    free(result_set[i].members);

  return members;
}
