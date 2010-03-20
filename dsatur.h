# include "structs.h"
# include "utilities.h"
# include <stdlib.h>
# include <stdio.h>


/****************************************************************/
/* Algoritmo de DSATUR. Encuentra una cota superior de la       */
/* coloración de un grafo. Elige el próximo vértice a colorear  */
/* basandose en el criterio de grado de saturación. Encuentra   */
/* también una cota inferior del problema si este es ejecutado  */
/* N veces.                                                     */
/****************************************************************/
pair dsatur(Graph *, tuple *, int, int);

/************************************************************/
/* Determina repeticiones en dsatur_degree                  */
/* Cuando se elige un vértice con mayor grado de saturación */
/* se quiere saber si existe otro que tiene el mismo grado  */
/* para así descartar la posibilidad de buscar el de grado  */
/* mayor de incidencias.                                    */
/************************************************************/
int repeated(int, int *, int, int);

/************************************************************/
/* Actualiza los grados de saturación de colores adyacentes */
/************************************************************/
void update_satur(Graph *, int *, int, int);

/***********************************************************/
/* Devuelve el próximo vértice de grado mayor e incrementa */
/* el apuntador base al próximo elemento.                  */
/***********************************************************/
int get_max_degree(tuple *, Graph *, int);

/****************************************************************/
/* Función que retorna el color más pequeño                     */
/* Revisa en el arreglo color_around del vértice v_i que se     */
/* quiere colorear cuál es la primera casilla que aparece en 0  */
/* para así utiliza dicho color.                                */
/* Cuando la casilla está en 0 indica ausencia de color.        */
/* Cuando está en 1 indica presencia de color.                  */
/****************************************************************/
int leastp_color(Graph *,int, int);

/****************************************************/
/* Función que descolorea un vértice para detectar  */
/* más fácilmente una clique máxima                 */
/****************************************************/
void uncolor(Graph *, int, int);

/*********************************************************/
/* Función que chequea si dado un vértice v_i éste forma */
/* una clique con los vértices de members que ya se sabe */
/* forman una clique                                     */
/*********************************************************/
int makes_clique(Graph *, int, int *, int);



/***************************************************/
/* Esta función trata de hacer un intercambio de   */
/* colores en el grafo. Si el intercambio se da,   */
/* entonces se llama la función leastp_color la    */
/* cual devuelve el color más pequeño que se puede */
/* utilizar.                                       */
/***************************************************/
void check_interchange(int *, int *, int *, Graph *, int, int *, int, int);


