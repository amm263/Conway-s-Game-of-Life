/*
* Progetto di Programmazione Parallela: Game of Life
* AA 2011-2012 - Autore: Andrea Mazzotti - Matricola 0000418295
*/

#pragma once

#include "GameModel.h"
#include "GameView.h"

class GameControl
{
public:
	GameControl(int x, int y);
	~GameControl(void);
	void run();
private:
	GameView* view;
	static GameModel* model;
	void update_cell(int x, int y);
};

