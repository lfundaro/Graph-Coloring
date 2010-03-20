# include "structs.h"
# include <stdlib.h>
# include <stdio.h>

void dfs(int, int*, Graph *,int*);

int get_nxt_neighbour(int,int*,int,linked_array_list*);

int check_subgraph(int*,int,linked_array_list*);

void update_saturation(int, int,int,Graph *,int*);

void del_array_list(linked_array_list*);

void interch(int,int,int,linked_array_list*,Graph *,int,int*);

Graph * interchange(Graph *,int*,int,int,int);

