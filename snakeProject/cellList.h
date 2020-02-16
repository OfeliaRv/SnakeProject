/*==========================================================*\
  Sunday March the 10th 2019
  Arash Habibi
  cellList.h
\*==========================================================*/

#ifndef __CELLLIST_H__
#define __CELLLIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "arena.h"
#include "ppm.h"

#define CL_MAX 1000

struct cellList{
	
	int size;
	struct cell arr[CL_MAX];
};

//----------------------------------------------------
// Returns an empty stack of cells

struct cellList CL_new();

//----------------------------------------------------
// Adds cell (row,col) on top of the stack cell

struct cellList CL_add(struct cellList cl, struct cell c);

//----------------------------------------------------
// Prints the contents of the cell list.

void CL_print(struct cellList cl, char *label);

//----------------------------------------------------
// Returns the value of cell index i.

struct cell CL_get(struct cellList cl, int i);

//----------------------------------------------------
// Returns an element at random in cl (unless cl is empty)

struct cell CL_random(struct cellList cl);

//----------------------------------------------------
// Returns a list of cells corresponding to the neighbors
// of c (Each neighbor has c neighbors)

struct cellList CL_neighbors(struct cell c, struct arena ar);

//----------------------------------------------------
// Returns a list filled with the neighbors of cell c
// Each cell has 4 neighbors except those who are on the
// border of the arena.

struct cellList CL_randomPath(struct cell start, int nb_cells, struct arena ar);

//----------------------------------------------------
// Draws one ppm image file representing the cl cell list.

int isInside(struct cell c, struct cellList cl); //for 5th

void CL_draw(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name);

//----------------------------------------------------
// Draws a series of ppm image files. In the first file
// can be seen the first cell of cl, in the second file,
// the first and the second. In the last file, all of
// the elements can be seen.

void CL_animate(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name);

//----------------------------------------------------
// Tests the behaviour of a cell list.

//void CL_test(int nb_rows, int nb_cols);

#endif // __CELLLIST_H__
