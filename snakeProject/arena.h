#ifndef __ARENA_H__
#define __ARENA_H__

#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

struct arena{
	int nb_rows;
	int nb_cols;	
};

struct arena A_new(int nb_rows, int nb_cols);

int A_isInside(struct cell c, struct arena ar);

//struct cellList CL_neighbors(struct cell c, struct arena ar);

//struct cellList CL_randomPath(struct cell start, int nb_cells, struct arena ar);






#endif