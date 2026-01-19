#pragma once

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 10,
	};

public:
	Player();
	~Player();

	void			Init(Board* board);
	void            Update(uint64 deltaTick);


	Pos				GetPos() { return _pos; }
	void			SetPos(Pos pos) { _pos = pos; }

private:

	vector<Pos>     _path;
	int32			_pathIndex = 0;
	Pos				_pos;
	Board*			_board;
	uint64			_sumTick = 0;
	int32           _dir = DIR_UP;
	void			RandomMove();
	bool			CanGo(Pos pos);

private:
	void			RightHand();
};


// RandomMove - 어떤 경우에도 탈출을 못하는 경우가 생긴다.
// RightHand -  문제가 있다. (한번이라도 간적이 있으면 체크)
// bool true false
// Pos[25][25] = false(true) << 가지마라.
// 선형 자료구조에서는 길이 막힙니다.
// 그래프. 길이 2개보다 많다.														 