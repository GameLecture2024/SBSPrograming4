#pragma once

#include "ConsoleHelper.h"

enum
{
	MAX_SIZE = 40
};

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
	INVISIBLE,
};

class Player;

class Board
{
public:
	Board();
	~Board();

	void					Init(int32 size, Player* player);
	void					Render();

	int32					GetSize() { return _size; }
	Pos						GetStartPos() { return Pos{ 1,1 }; }
	Pos						GetEndPos() { return Pos{ _size - 2, _size - 2 }; }

	void					GenerateMap();
	TileType				GetTileType(Pos pos);
	ConsoleColor			GetColorByTileType(Pos pos);
	int32				    _level;

private:
	Player*					_player;
	TileType				_tile[MAX_SIZE][MAX_SIZE];
	int32					_size;

	void					BinaryTree();
	void					BadMap();
	void					Kruskal();
	void					Prim();
};

