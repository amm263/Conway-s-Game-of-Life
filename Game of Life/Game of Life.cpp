/*
* Progetto di Programmazione Parallela: Game of Life
* AA 2011-2012 - Autore: Andrea Mazzotti - Matricola 0000418295
*/

// Game of Life.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameControl.h"


int _tmain(int argc, _TCHAR* argv[])
{
	GameControl* control = new GameControl(100,100);
	control->run();
	return 0;
}

