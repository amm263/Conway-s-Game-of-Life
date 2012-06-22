/*
* Progetto di Programmazione Parallela: Game of Life
* AA 2011-2012 - Autore: Andrea Mazzotti - Matricola 0000418295
*/

#pragma once
class GameModel
{
public:
	GameModel(int x, int y);
	~GameModel(void);
	bool get_cell(int x, int y)
	{
		return read_board[x][y];
	}
	// Effettua una negazione sulla cella.
	void change_cell(int x, int y)
	{
		write_board[x][y]=!write_board[x][y];
	}
	int get_rows()
	{
		return rows;
	}
	int get_columns()
	{
		return columns;
	}
	void randomize();
	// Copia la cella[x][y] per aggiornare la board di lettura.
	void copy_board(int x, int y)
	{
		read_board[x][y]=write_board[x][y];
	}
	static GameModel* get_instance()
	{
		return instance;
	}
private:
	static GameModel* instance;
	bool** read_board;
	bool** write_board;
	int rows;
	int columns;
};

