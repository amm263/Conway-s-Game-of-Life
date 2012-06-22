/*
* Progetto di Programmazione Parallela: Game of Life
* AA 2011-2012 - Autore: Andrea Mazzotti - Matricola 0000418295
*/

#include "StdAfx.h"
#include "GameControl.h"


GameModel* GameControl::model=NULL;

/*
*	Il costruttore crea un nuovo modello di gioco,
*	lo randomizza ed infine crea la finestra dell'applicazione.
*/
GameControl::GameControl(int x, int y)
{
	model= new GameModel(x,y);
	model->randomize();
	view= new GameView(x,8,y,8);
}

void GameControl::run()
{
	int start, finish, id, y;
	int nthreads=omp_get_num_procs(); //Inizializzo i threads a seconda del numero di processori.
	omp_set_num_threads(nthreads);
	SDL_Event event;
	
	/*
	*	Parte parallela:
	*	
	*	Variabili shared:
	*		model --> puntatore al modello
	*		nthreads --> numero di threads
	*
	*	Variabili private:
	*		start --> Offset di inizio della sezione da calcolare e contatore.
	*		finish --> Offset di fine della sezione.
	*		id --> Id del thread.
	*		y --> Contatore.
	*/
	#pragma omp parallel shared(model, nthreads) private(start,finish,id,y) num_threads(nthreads)
	{
		id= omp_get_thread_num();

		start= id * (model->get_rows()/nthreads); 
		finish= start + (model->get_rows()/nthreads);

		while(true)
		{

			for (start= id * (model->get_rows()/nthreads);start<finish;start++)
			{
				for (y=0;y<model->get_columns();y++)
				{
					update_cell(start,y);
				}
			}
			// Aspetto che la write_board sia stata aggiornata da tutti i thread.
			#pragma omp barrier
			for (start= id * (model->get_rows()/nthreads);start<finish;start++)
			{
				for (y=0;y<model->get_columns();y++)
				{
					model->copy_board(start,y);
				}
			}
			// Aspetto che la read board sia stata aggiornata da tutti i thread.
			#pragma omp barrier

			if (id==0)
			{
				//Sleep(10);
   				view->draw_screen();
				if(SDL_PollEvent(&event))
				{
					// Se è stato premuto il tasto Spazio, viene randomizzata la board.
					if(event.type==SDL_KEYDOWN)
					{
						switch(event.key.keysym.sym)
						{
							case SDLK_SPACE:
								model->randomize();;
							break;
						}
					}
					else if(event.type==SDL_QUIT)
					{
						SDL_Quit();
						exit(0);
					}
				}
			}
			// Aspetto che il primo thread aggiorni l'interfaccia.
			#pragma omp barrier
		}
	}

}


/*
*	Controllo principale del gioco.
*	Qui sono definite le regole.
*/
void GameControl::update_cell(int x, int y)
{
	int living_cells=0;
	int sec_x, sec_y, i, j;
	for(sec_x=x-1;sec_x<=x+1;sec_x++)
	{
		for(sec_y=y-1;sec_y<=y+1;sec_y++)
		{
			i=sec_x;
			j=sec_y;
			
			if(sec_x==-1)
				i=model->get_rows()-1;
			else if(sec_x==model->get_rows())
				i=0;

			if(sec_y==-1)
				j=model->get_columns()-1;
			else if(sec_y==model->get_columns())
				j=0;

			if ((x==i)&&(y==j))
			{
			}
			else
			{
				if (model->get_cell(i,j))
					living_cells++;
			}
		}
	}
	if( model->get_cell(x,y) )
	{
		if ((living_cells<2)||(living_cells>3))
			model->change_cell(x,y);
	}
	else
	{
		if (living_cells==3)
			model->change_cell(x,y);
	}
}

GameControl::~GameControl(void)
{
}
