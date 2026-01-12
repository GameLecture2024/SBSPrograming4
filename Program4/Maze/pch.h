#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>
#include "Types.h"
using namespace std;


// operator ¿Á¡§¿« == !+ +
// ctrl + m + o

struct Pos
{
	bool operator==(Pos& other) {
		return y == other.y && x == other.x;   
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	Pos operator+(Pos& other)
	{
		Pos temp;
		temp.y = y + other.y;
		temp.x = x + other.x;

		return temp;
	}

	Pos& operator+=(Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}

	int32 x = 0;
	int32 y = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4
};
