/*Funcion que calcula la cantidad de colores posibles
  para un vertice*/
/*
  Recibe un arreglo que representa un conjunto vectorial
  con los colores posibles marcados con 1 y el tamano ese
  arreglo
*/
int* number_of_FC(int* FC, int FC_size){
  int n = 0;
  int i = 0;

  while(i<FC_size){
    if (FC[i]<1)
      ++n;
    ++i;
  }
  return n;
}
