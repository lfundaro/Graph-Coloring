# include "interchange.h"

/*Funcion que recorre con DFS los nodos coloreados con colors[0] o colors[1]
  y que son alcanzables desde el nodo neighbour.*/
/*La funcion guarda los nodos alcanzados en el conjunto vectorial control_set,
  el cual se pasa por referencia.*/
void dfs(int neighbour, int* colors, Graph graph[],int* control_set){
  int* adjs = graph[neighbour].adjacents; //Arreglo con los nodos adyacentes a neighbour
  int adjs_size = graph[neighbour].adj_size;
  int i = 0;
  int vertex;

  //Marco neighbour como visitado.
  control_set[neighbour]=1;

  //Aplico dfs sobre sus adyacentes.
  while (i<adjs_size){
    vertex=adjs[i];
    //Chequeo que no halla visitado al adyacente actual
    //y que tenga un color que me interese.
    if (! control_set[vertex]&&
        (colors[0]==graph[vertex].color||
         colors[1]==graph[vertex].color) ){
      dfs(vertex,colors,graph,control_set);
    }
    ++i;
  }
}


/*Funcion que calcula el proximo vecino a partir del cual se aplicara DFS*/
//--Se asegura de que el vecino no halla sido alcanzado por un DFS anterior,
//es decir, que no pertenesca a una componente ya explorara.
int get_nxt_neighbour(int last_neighbour,int* neighbours,int n_of_neighbours,linked_array_list* components){

  int i=1;//i sera 1 mientras no consiga un proximo vecino
  linked_array_list* aux;//Recorrera las componentes
  int next_neighbour = ++last_neighbour;

  while (i==1&&next_neighbour<n_of_neighbours){
    aux = components;
    //Recorro las componentes
    while (aux!=NULL){
      //Si el vecino actual pertenece a la componente,
      //hago i=2 y reviso el proximo vecino.
      if ((aux->array)[neighbours[next_neighbour]]==1) {
        i=2;
        next_neighbour++;
        break;
      }
      else
        aux=aux->next;
    }
    //Si i==1, termina el ciclo en la siguiente iteracion.
    //Si i==2, revisa el siguiente vecino.
    i-=1;
  }

  //En caso de no encontrar nada, devuelve n_of_neighbours
  return next_neighbour;
}


/*Funcion que revisa la validez y utilidad del grafo inducido por intercambio*/
//--Se asegura de que el nodo sobre el cual se hace el intercambio no sea 
//adyacente a dos nodos de distinto color y de la misma componente (Validez).
//--Se asegura de que existan al menos dos componentes a las cuales el nodo esta
//conectado por nodos de colores distintos (Utilidad).
int check_subgraph(int* neighbours,int n_of_neighbours,linked_array_list* components){
  int validity = 0; //Contador para chequear la validez del intercambio
  linked_array_list* aux = components;
  int j=0;

  /*CHEQUEO DE VALIDEZ*/
  //Recorro las componentes
  while (aux!=NULL){
    //Cuento los vecinos del nodo que son parte
    //de la componente actual.
    while (j<n_of_neighbours){
      if ((aux->array)[neighbours[j]]==1)
        validity++;
      j++;
    }
    //Si hay al menos dos vecinos que son parte
    //de la componente actual, retorno falso.
    if (validity>2)
      return 0;
    validity=0;
    j=0;
    aux=aux->next;
  }


  /*CHEQUEO DE UTILIDAD*/
  /*Tomo el primer color. Si mas adelante
    encuentro al menos uno diferente, el
    intercambio para este nodo es util*/
  aux=components;
  j=aux->color;
  aux=aux->next;
  while (aux!=NULL){
    if (j!=aux->color)
      return 1;
    aux=aux->next;
  }

  return 0;
}


/*Funcion que actualiza los grados de saturacion y arreglos de colores adyacentes
  del la estructura que representa el grafo cuando intercambio cambia el color de
  un nodo.*/
void update_saturation(int vertex, int new_color,int old_color,Graph graph[],int* satur_degree){

  int* adjs = graph[vertex].adjacents; //Lista de nodos adyacentes al nodo recoloreado
  int adjs_size = graph[vertex].adj_size;
  int v; //Guarda el vecino que va a procesar
  int i = 0;

  //Recorro los vecinos
  while(i<adjs_size){
    v=adjs[i];

    //Si el vecino ya fue coloreado, sigo con el siguiente.
    if (satur_degree[v]==-1){
      ++i;
      continue;
    }

    //Si el vecino no era adyacente al nuevo color 
    //del nodo, aumento su saturacion.
    if (graph[v].color_around[new_color]==0)
      satur_degree[v]+=1;
    graph[v].color_around[new_color]+=1;

    /*Si despues de descontar el viejo color al vecino
      no le restan vecinos adyacentes de ese color,
      disminuyo su saturacion.*/
    graph[v].color_around[old_color]-=1;
    if (graph[v].color_around[old_color]==0)
      satur_degree[v]-=1;

    ++i;
  }
}

//Funcion recursiva que libera una lista enlazada
//simple con apuntadores a arreglos.
void del_array_list(linked_array_list* al){
  linked_array_list* next = al->next;
  free(al->array);
  free(al);
  del_array_list(next);
  /* if(al->next!=NULL){ */
  /*   del_array_list(al->next); */
  /* } */
  /* free(al->array); */
  /* free(al); */
}


/*Funcion que recolorea las componentes que sean necesarias
  para realizar el intercambio.*/
//satur_degree es un arreglo de N que registra las
//saturaciones de todos los nodos
void interch(int min_col,int max_col,int vertex,linked_array_list* components,Graph graph[],int vertex_num,int* satur_degree){
  int i=0;
  linked_array_list* aux = components;

  //Recorro las componentes
  while (aux!=NULL){
    if(aux->color==min_col)
      //Recorro la componente
      while (i<vertex_num){
        if ((aux->array)[i]==1)

          /*Si el nodo de la componente tiene
            min_col, le pongo max_col y actualizo
            la saturacion. Viceversa para el caso
            contrario*/
          if (graph[i].color==min_col){
            graph[i].color=max_col;
            update_saturation(i,max_col,min_col,graph,satur_degree);
          }
          else{
            graph[i].color=min_col;
            update_saturation(i,min_col,max_col,graph,satur_degree);
          }
        i++;//Proximo nodo a considerar
      }
    i=0;
    aux=aux->next;//Siguiente componente
  }
}

/*Funcion principal de intercambio*/
//--Revisa si para un vertice dado existe un intercambio util*/
//--Devuelve el grafo con las componentes necesarias intercambiadas. 
//--No colorea el nodo sobre el cual se hizo el intercambio.
Graph* interchange(Graph graph[],int* satur_degree,int vertex, int high_color, int vertex_num){
  //Estructuras para determinar los colores y nodos adyacentes
  int* color_set = (int*)malloc((high_color+1) * sizeof (int));//Conjunto vectorial de colores adyacentes
  int* neighbours = graph[vertex].adjacents;//Vecinos del nodo para el cual se hara intercambio
  int n_of_neightbours = graph[verters].adj_size;
  int* colors;
  int n_of_colors;

  //Estructuras para el calculo de componentes
  linked_array_list* components;
  linked_array_list* tail;
  int* control_set;//Conjunto vectorial con los nodos de una componente

  //Estructuras para el calculo de la combinatoria de colores
  int* pair;//Arreglo de dos que guarda una combinacion
  int* next_swap = (int*)malloc(2 * sizeof (int));
  
  //Contadores genericos
  int i;
  int j;

  //Inicializacion del arreglo color_set
  initialize(color_set,high_color+1);

  /*Calculo de colores adyacentes
    Los colores quedan guardados en un conjunto vectorial*/

  //Recorro los vecinos
  i=0;
  while (i < n_of_neightbours){
    //Si esta coloreado, marco el color en el arreglo vectorial
    if (graph[neightbours[i]].color > -1){
      color_set[graph[neightbours[i]].color]]=1;
    
    ++i;
  }
  
  //Calculo del numero de colores distintos adyacentes
  for(i=0;i<high_color+1;i++){
    n_of_colors += color_set[i];
  }

  //Guardo los colores adyacentes en un arreglo
  colors = (int*)malloc(n_of_colors * sizeof (int));
  j=0;
  for(i=0;i<high_color+1;i++){
    if (color_set[i]==1){
      colors[j]=i;
      ++j;
    }
  }

  //Inicializo la estructura necesaria para el calculo
  //de las combinaciones de colores
  next_swap[0]=0;
  next_swap[1]=2;


  /*CICLO PRINCIPAL*/

  pair=(int*)twoOnN(colors,next_swap,n_of_colors);
  j=0; //j recorrera el arreglo de adyacentes neighbours[]

  //Mientras queden combinaciones
  while (pair!=NULL){

    /*El ciclo que viene asume que siempre agrega una componente al final
      de la lista de componentes que guarda los resultados del DFS. Para que ese
      ciclo no ocasione Segmentation Fault, se crea un primer elemento en
      la lista de componentes que nunca se usara y que se liberara al final.*/
    components=(linked_array_list*)malloc(sizeof (linked_array_list));
    control_set=(int*)malloc(vertex_num * sizeof (int));
    //initialize(control_set,vertex_num); //Pork esta se estaba haciendo??
    components->array=control_set;
    components->next=NULL;

    tail=components;
    //Mientras tenga vecinos que no he alcanzado
    while(j<n_of_neighbours){
      //Si el color del vecino coincide con uno de los pares
      if (graph[neighbours[j]].color==pair[0]||
	  graph[neighbours[j]].color==pair[1]){

	//Creo una nueva componente al final de la lista
	tail->next=(linked_array_list*)malloc(sizeof (linked_array_list));
	tail=tail->next;
	tail->color=graph[neighbours[j]].color;
	control_set=(int*)malloc(vertex_num * sizeof (int));
	initialize(control_set,vertex_num);
	tail->array=control_set;
	tail->next=NULL;

	//Calculo los nodos alcanzables desde este vecino
	dfs(neighbours[j],pair,graph,control_set);
      }
      //Calculo el proximo vecino que no he alcanzado
      j=get_nxt_neighbour(j,neighbours,n_of_neighbours,components);
    }
    tail=components;
    components=components->next;
    free(tail);

    //Prodedo si el intercambio me es util...
    if (check_subgraph(neighbours,n_of_neighbours,components)){

      //Hago intercambio para colorear con el menor color posible.
      if (pair[0]<pair[1])
	interch(pair[0],pair[1],vertex,components,graph,vertex_num,satur_degree);
      else
	interch(pair[1],pair[0],vertex,components,graph,vertex_num,satur_degree);

      del_array_list(components);
      free(pair);
      break;//Termino el ciclo ya que logre hacer intercambio.
    } 
    
    del_array_list(components);
    free(pair);

    //Calculo la proxima combinacion de colores y reinicio j
    pair=(int*)twoOnN(colors,next_swap,n_of_colors);
    j=0;
  }

  free(color_set);
  free(colors);
  free(neighbours);
  free(next_swap);
}
