/*==========================================================*\
  Sunday March the 10th 2019
  cellList.c
\*==========================================================*/
#include <time.h>
#include "cellList.h"
#include "cell.h"
#include "ppm.h"

//----------------------------------------------------
// Returns an empty stack of cells

struct cellList CL_new(){
	struct cellList cl;
	cl.size=0;

	return cl;
}

//----------------------------------------------------
// Adds cell (row,col) on top of the stack cell

struct cellList CL_add(struct cellList cl, struct cell c){
	cl.arr[cl.size]=c;
	cl.size++;

	return cl;
}


void CL_print(struct cellList cl, char *label){
	struct cell c;
	printf("%s\n", label);
	for (int i = 0; i < cl.size; i++){
		c=cl.arr[i];
		
		printf("%d : (%d,%d)\n", i, c.row,c.col);
	}
}

//----------------------------------------------------
// Returns the value of cell index ind.

struct cell CL_get(struct cellList cl, int ind){
	struct cell c;
	c=cl.arr[ind];
	
	//printf("cell of index %d is (%d,%d)\n", ind, c.row,c.col);
	return c;
}

//----------------------------------------------------
// Returns an element at random in cl (unless cl is empty)

struct cell CL_random(struct cellList cl){
	struct cell c;
    int ind = rand() % cl.size;
    c = cl.arr[ind];
    
    //printf("random number is: %d\n", ind); 
    return c;	
}


//----------------------------------------------------
// Returns a list of cells corresponding to the neighbors
// of c (Each neighbor has c neighbors)

struct cellList CL_neighbors(struct cell c, struct arena ar){
struct cell newCell=c;
	
	struct cellList neighbourList=CL_new();
	//Upper
	newCell.row=c.row-1;
	if(A_isInside(newCell,ar)==1)
	neighbourList= CL_add(neighbourList,newCell);

	//Lower
	newCell.row=c.row+1;
	if(A_isInside(newCell,ar)==1)
	neighbourList= CL_add(neighbourList,newCell);

	//Left 
	newCell.row=c.row;
	newCell.col=c.col-1;
	if(A_isInside(newCell,ar)==1)
	neighbourList= CL_add(neighbourList,newCell);

	//Right
	newCell.col=c.col+1;
	if(A_isInside(newCell,ar)==1)
	neighbourList= CL_add(neighbourList,newCell);
	                                                                                                                   

	return neighbourList;
}

//----------------------------------------------------
// Returns a cell list obtained by choosing random neighbors
// of start, then, random neighbors of this neighbor and so on,
// until there are nb_cells cells in the cell list.

struct cellList CL_randomPath(struct cell start, int nb_cells, struct arena ar){
	
// 	struct cellList cl;
// 	cl.size=nb_cells;
// 	cl.arr[0]=start;
// 	for(int i=1;i<nb_cells;i++){
// 		cl.arr[i]=CL_random(CL_neighbors(cl.arr[i-1],ar));
// 	}

// 	return cl;
// }


struct cellList snake=CL_new();
	int i=0;
	snake.arr[i]=start;
	snake.size++;
	struct cell c;

for ( i = 0; i < nb_cells; i++){
	c=CL_random(CL_neighbors(snake.arr[i],ar));
	C_print(c,"cell is");

    if(isInside(c,snake)==1){
   		i--;
   		printf("same\n");
    }
    else{
   		printf("here\n");
   		snake.arr[i+1]=c;
   		snake.size++;
   		C_print(snake.arr[i+1],"snake is at");
	}
	printf("\n");
}
    return snake;
}

//----------------------------------------------------
// Draws a series of ppm image files. In the first file
// can be seen the first cell of cl, in the second file,
// the first and the second. In the last file, all of
// the elements can be seen.

int isInside(struct cell c, struct cellList cl){
	for (int i = 0; i < cl.size; i++)
	{

		if (cl.arr[i].col==c.col && cl.arr[i].row==c.row)
		{
		  return 1;
		}
	}
	return 0;

}

void CL_draw(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name)
{
	int pixels_per_cell = 20;
	char ppm_file_name[50];
	float proportion_serpent = 0.7;
	struct ppm img = PPM_new(nb_rows, nb_cols, pixels_per_cell, proportion_serpent);
	img = PPM_drawBG(img);

	struct cell c = CL_get(cl,0);
	img = PPM_drawCell(img, c.row, c.col);

	for(int i=1; i<cl.size;i++)
	{
		struct cell c = CL_get(cl,i);
		struct cell c2 = CL_get(cl,i-1);
		img = PPM_drawLink(img, c.row, c.col, c2.row, c2.col);
		img = PPM_drawCell(img, c.row, c.col);
	}
	sprintf(ppm_file_name,"%s.ppm",ppm_name);
	PPM_save(img,ppm_file_name);
}
// ----------------------------------------------------
// Draws a series of ppm image files. In the first file
// can be seen the first cell of cl, in the second file,
// the first and the second. In the last file, all of
// the elements can be seen.

void CL_animate(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name)
{
	int pixels_per_cell = 20;
	char ppm_file_name[50];
	float proportion_serpent = 0.7;
	struct ppm img = PPM_new(nb_rows, nb_cols, pixels_per_cell, proportion_serpent);
	img = PPM_drawBG(img);

	struct cell c = CL_get(cl,0);
	img = PPM_drawCell(img, c.row, c.col);
	sprintf(ppm_file_name,"%s_%02d.ppm",ppm_name,0);
	PPM_save(img,ppm_file_name);

	for(int i=1; i<cl.size;i++)
	{
		struct cell c = CL_get(cl,i);
		struct cell c2 = CL_get(cl,i-1);
		img = PPM_drawLink(img, c.row, c.col, c2.row, c2.col);
		img = PPM_drawCell(img, c.row, c.col);

		sprintf(ppm_file_name,"%s_%02d.ppm",ppm_name,i);
		PPM_save(img,ppm_file_name);
	}
}


/////////////////////////////////////////////////////////////////////////////////
int main(){
	
	struct cellList cl = CL_new();
	struct cell c = C_new(3,5);
	struct arena ar = A_new(8,10);
	srand(time(NULL));
	//cl = CL_add(cl,c); 
	// cl = CL_add(cl,C_new(4,5)); 
	// cl = CL_add(cl,C_new(4,6));

	//c = CL_get(cl,1);  
	//c = CL_random(cl);
    
    //struct cellList cl2 = CL_new();
    //cl2 = CL_neighbors(c,ar);

	cl = CL_randomPath(c,15,ar);
	CL_print(cl,"TestList");
    // CL_draw(cl, 10, 10, "snake",0);
    // CL_animate(cl, 10, 10, "snake");

	return 0;
}