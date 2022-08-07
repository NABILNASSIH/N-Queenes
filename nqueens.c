#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#include <malloc.h>
#include "board.h"
#include <string.h>
#include "list.h"



list_t openList_p;
list_t closedList_p;


void showSolution( Item *goal )
{
  int i = 0, j;

  printf("\nSolution:");

  while (goal) {
    printBoard( goal );
		goal = goal->parent;
		i++;
  }

  printf("\nLength of the solution = %d\n", i-1);
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
  return;
}


void bfs( void )
{
  Item *cur_node, *child_p, *temp;
  int i;
  /* While items are on the open list */
  while ( listCount(&openList_p) ) { 
   	
		/* Get the first item on the open list */
		cur_node = popFirst(&openList_p);
		
		//printf("%d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));

		/* Add it to the "visited" list */
		  addLast( &closedList_p, cur_node );


    /* Do we have a solution? */
    if ( evaluateBoard(cur_node) == 0.0 )
 {
      showSolution(cur_node);
      return;

    } else {

      /* Enumerate adjacent states */
      for (int i = 0; i < MAX_BOARD; i++) {
        child_p = getChildBoard( cur_node, i );
   			
        if (child_p != NULL && onList(&closedList_p, child_p->board) == NULL) { // it's a valid child!AND /* Ignore this child if already visited */
					
					/* Add child node to openList */
	  			addLast( &openList_p, child_p );
        }
      }
    }
  }

  return;
}

void dfs( void )
{
    Item *cur_node, *child_p, *temp;
    int i;
    
    /* While items are on the open list */
    while ( listCount(&openList_p) ) 
    {        
        /* Get the first item on the open list */
        cur_node = popFirst(&openList_p);
        
        /* Add it to the "visited" list */
        addLast( &closedList_p, cur_node );

        /* Do we have a solution? */
        if ( evaluateBoard(cur_node) == 0.0 ) 
        {
            showSolution(cur_node);
            return;  
        } 
        else 
        {
            /* Enumerate possible movements */
            for(i = 0; i < MAX_BOARD; i++) 
            {
                child_p = getChildBoard( cur_node, i );
                
                /* Ignore this child if already visited or invalid */
                if (child_p != NULL && onList(&closedList_p, child_p->board) == NULL) 
                { 
                    /* Add child node to openList */
                    addFirst( &openList_p, child_p );  
                }
            }
        }
    }   
    return;
}



int choix(int argc, char* argv[])
{
  if(argc!=2)
  {
    printf("la ligne de commande doit être de la forme suivante :\n");
    printf("./nqueens <mode>\n");
    return 1;
  }

  else if( strcmp(argv[1],"bfs")!=0 && strcmp(argv[1],"dfs")!=0  )
  {
      printf("Invalid  mode\n");
      printf("Valid modes: bfs dfs \n");
      return 1;
  }

  
    return 0;
}   

int main(int argc, char* argv[])
{
	
  if(choix(argc,argv)!=0)
      exit(1);

  /* init lists */
  initList(&openList_p);
  initList(&closedList_p);


  printf("\nInitial:");
  Item *initial_state = initGame();
  printBoard( initial_state );

  printf("\nSearching ...\n");
  addLast( &openList_p, initial_state );

  if(strcmp(argv[1],"bfs")==0)
      bfs() ;
  else if(strcmp(argv[1],"dfs")==0)
      dfs();

	printf("Finished!\n");

	   /* clean lists */
    cleanupList( &openList_p );
    cleanupList( &closedList_p );

  return 0;
}
