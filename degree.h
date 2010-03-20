# ifndef DEGREE
# define DEGREE
# include <stdlib.h>
# include <stdlib.h>
# include "structs.h"


/*********************************************************/
/* Funcion que dado un arreglo de lista de adyacencias   */
/* y el número de vértices del grafo, retorna un arreglo */
/* de tuplas vértice-grado                               */
/*********************************************************/
void degree(struct Graph *, int, struct tuple *);

/*****************************************************/
/* Funcion que compara dos elementos tuple segun los */
/* grados de los vértices.                           */
/*****************************************************/
int compare(const void *, const void *);

#endif