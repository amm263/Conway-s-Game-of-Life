/*
* Progetto di Programmazione Parallela: Game of Life
* AA 2011-2012 - Autore: Andrea Mazzotti - Matricola 0000418295
*/

#pragma once

#include "GameModel.h"

class GameView
{
public:
	GameView(int width, int xscale, int height, int yscale);
	~GameView(void);
	void draw_screen();
private:
	int w,xs,h,ys;
	SDL_Surface* screen;
	Uint32* pixels;
	void FillRect(int x, int y, int w, int h, int color)
	{
		SDL_Rect rect = {x,y,w,h};
		SDL_FillRect(screen, &rect, color);
	}
	GameModel* model;
};

