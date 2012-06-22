/*
* Progetto di Programmazione Parallela: Game of Life
* AA 2011-2012 - Autore: Andrea Mazzotti - Matricola 0000418295
*/

#include "StdAfx.h"
#include "GameModel.h"

GameModel* GameModel::instance=NULL;

/*
*	Inizializza le due board di gioco.
*	write_board è dove le modifiche vengono salvate ad ogni turno.
*	read_board è dove lo stato del gioco viene letto.
*/
GameModel::GameModel(int x, int y)
{
	int i;
	rows=x;
	columns=y;
	write_board=(bool**)malloc(sizeof(bool*)*x);
	read_board=(bool**)malloc(sizeof(bool*)*x);
	for(i=0;i<x;i++)
	{
		write_board[i]=(bool*)malloc(sizeof(bool)*y);
		read_board[i]=(bool*)malloc(sizeof(bool)*y);
	}
	instance=this;
}

/*
*	Randomizza la board.
*/
void GameModel::randomize()
{
	int x,y;
	srand ( time(NULL) );

	for (x=0;x<rows;x++)
	{
		for (y=0;y<columns;y++)
		{
			if ((rand() % 10 + 1)<=5)
			{
				write_board[x][y]=true;
				copy_board(x,y);
			}
			else
			{
				write_board[x][y]=false;
				copy_board(x,y);
			}
		}
	}
}


GameModel::~GameModel(void)
{
}
