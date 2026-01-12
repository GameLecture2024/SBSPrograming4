#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size)
{
	_size = size;

}

void Board::Render()
{
	ConsoleHelper::SetCursorPos(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);
	
	for (int y = 0; y < _size; y++)
	{
		for (int x = 0; x < _size; x++)
		{
			ConsoleHelper::SetCursorColor(ConsoleColor::BLUE);
			cout << "¡Ü";
		}
		cout << endl;
	}
}
