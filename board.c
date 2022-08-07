#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"




// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{
  int i;
  Item *node;

	char *initial = (char*)malloc(MAX_BOARD*sizeof(char));
	for (int i=0; i<MAX_BOARD; i++) initial[i] = 0;

    node = nodeAlloc();
	initBoard(node, initial);
    node->depth = 0;

  return node;
}
// initialize node's state from a given board
void initBoard(Item *node, char *board) {
	assert( node );
	int i;
	
	node->size = MAX_BOARD;
     node->board = calloc(MAX_BOARD, sizeof(char));
  
	/* Copy board */
	 for (i = 0; i<MAX_BOARD; i++)
	 {
        node->board[i] = board[i];
    }

}

// Return 0 if all queens are placed. Positive otherwise
// Ie: nb queens that still need to be placed.
double evaluateBoard(Item *node) {
    int nb = WH_BOARD, i;

    for (i = 0; i < MAX_BOARD; i++){
        if (node->board[i] == 1)
            nb-- ;
    }

  return nb;
}

int position(int i, int j){
    return i*WH_BOARD+j;
}
    
	

// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition( Item *node, int pos )

{
	int i,j;
	int ii= pos / WH_BOARD;
	int jj = pos % WH_BOARD;
	
  for (i=0; i<WH_BOARD; i++) 
	  
  {
     if (node->board[i*WH_BOARD+jj]>0) // tester la colonne
	        { 
				return 0;
            }
           
  	for (j=0; j<WH_BOARD; j++)
		{
		      

            if (node->board[ii*WH_BOARD+j]>0) //tester la ligne
			{ 
			    
				return 0;
            }


            if((abs(ii-i) == abs( jj-j)))// is  diagonal
			  { 
				if (node->board[i*WH_BOARD+j]>0) // tester les elem diago ixj
				{ 
						return 0;
				}
			  }
        }
}   
 //printf("position %d valide\n",pos);
  return 1; // POSITION VALIDE
}

// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Item *getChildBoard( Item *node, int pos )
{
  Item *child_p = NULL;

	if ( isValidPosition(node, pos) == 1 )
		{

        /* allocate and init child node */
        child_p = nodeAlloc() ;
        initBoard(child_p, node->board) ;

		/* Make move */
        child_p->board[pos] = 1;
        //printBoard(child_p) ;


		/* link child to parent for backtrack */
        child_p->parent = node;

        child_p->depth = node->depth +1 ;
        }

  return child_p;
}


// print a board


void printBoard( Item *node )
{
	int i, j;
	assert(node);
	printf("\n");
	
	for (j=0 ; j<WH_BOARD; j++) 
    	if (j==0) 
			printf(" ___");
		else 
			printf("____");
	printf("\n");
	
	for (i=0 ; i < MAX_BOARD ; i++) 
	{
    	if (i%WH_BOARD == 0) 
      		printf("|");
    	if (node->board[i] == 0) 
			printf("   |");
    	else 
      		printf("%2d |", node->board[i]);
    	if (((i+1)%WH_BOARD) == 0) 
    	{
			printf("\n");
			for (j=0; j<WH_BOARD; j++) 
        		if (j==0) 
        			printf(" ___"); 
        		else 
          			printf("____"); 
        	printf("\n");
		}
	}
	printf("\n");
}
/*


// TEST LIST

int main()
{ 

   Item *node;
   node=initGame();
   Item *node1;
	node1=getChildBoard( node, 2 );
    printBoard( node);
	printf( "%2f",evaluateBoard( node1 ));
	


	return 0;
}

*/