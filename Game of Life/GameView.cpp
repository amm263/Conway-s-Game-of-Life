/*
* Progetto di Programmazione Parallela: Game of Life
* AA 2011-2012 - Autore: Andrea Mazzotti - Matricola 0000418295
*/

#include "StdAfx.h"
#include "GameView.h"


GameView::GameView(int width, int xscale, int height, int yscale)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	w=width;
	h=height;
	xs=xscale;
	ys=yscale;
	screen=SDL_SetVideoMode(width*xscale,height*yscale,32,SDL_SWSURFACE);
	SDL_WM_SetCaption("Game of Life", "Game of Life");
	pixels = (Uint32*)screen->pixels;
	model=GameModel::get_instance();
	draw_screen();
}

void GameView::draw_screen()
{
	for(int x=0;x<w;x++)
	{
		for(int y=0;y<h;y++)
		{
			if(model->get_cell(x,y))
			{
				FillRect(x*xs,y*ys,xs,ys,0x000000);
			}
			else
			{
				FillRect(x*xs,y*ys,xs,ys,0xFFFFFF);
			}
		}
	}

	SDL_Flip(screen);
}


GameView::~GameView(void)
{
}
