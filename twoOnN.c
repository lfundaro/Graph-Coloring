/*Descripcion
  Algoritmo para calcular las combinaciones de 2
  elementos en un arreglo de N. Funciona a traves
  de efectos de borde.
*/
# include "twoOnN.h"

/*array: Arreglo al cual se le estan calculando
         las combinaciones de 2
  next_swap: estructura de control para poder dar
             la proxima permutacion a traves de
             varias llamadas a la funcion.
	     Debe comenzar en [0,2]. 
  N: tamano del arreglo (por eficiencia)
*/         
int* twoOnN(int array[],int next_swap[],int N){
  int head = next_swap[0];
  int tail = next_swap[1];
  int* pair;
  int aux;

  //Esta guarda es para cuando
  //genero la ultima combinacion
  if (head == N-1){
    pair = NULL;
    return pair;
  }

  pair = (int*)malloc(2 * sizeof (int));
  pair[0]=array[head];
  pair[1]=array[head+1];

  if (tail<N){
    aux = array[head+1];
    array[head+1] = array[tail];
    array[tail] = aux;
    
    next_swap[1] = next_swap[1]+1;
  }
  else{
    next_swap[0]=head+1;
    next_swap[1]=head+3;
  }

  return pair;
}

