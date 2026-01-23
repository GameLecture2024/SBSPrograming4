#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>
#include <queue>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Board* board)
{
    _board = board;

    //RightHand();
    //BFS();
    Astar();
}


void Player::Update(uint64 deltaTick)
{
    if (_pathIndex >= _path.size())
    {
        _pathIndex = 0;
        _board->Init(_board->GetSize(), this); // Generatemap << 새로운 맵
        Init(_board);
        return;
    }

    _sumTick += deltaTick;

    if (_sumTick >= MOVE_TICK)
    {
        _sumTick = 0;

        // 경로를 읽어와서 하나씩 움직여라
        _pos = _path[_pathIndex];       
        _pathIndex++;
        //RandomMove();
    }


}

// 우수법 : 오른쪽 벽을 짚고 길을 쭉 이동하면 언젠가는 미로를 탈출한다.
// 어떻게 움직여야 탈출할 수 있나요? vector<_path>
// X

void Player::RandomMove()
{
   // 플레이어가 상하좌우로 랜덤으로 움직인다.

    Pos moveDir[4] =
    {
        Pos{-1 , 0},  // 위
        Pos{0 , -1},  // 왼
        Pos{1 , 0},   // 아래
        Pos{0 , 1},   // 오
    };


    int randValue = rand() % 4;

    // TileType::EMPTY일때만 통과
    if(CanGo(_pos + moveDir[randValue]))
        _pos += moveDir[randValue];

}

bool Player::CanGo(Pos pos)
{
    TileType tileType = _board->GetTileType(pos);
    return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
    _pos = _board->GetStartPos();  
    Pos pos = _pos;
    Pos dest = _board->GetEndPos();

    _path.clear();
    _path.push_back(pos); // [시작 위치][다음 위치][][][도착지]

    Pos front[4] =
    {
        Pos{-1 , 0},  // 위
        Pos{0 , -1},  // 왼
        Pos{1 , 0},   // 아래
        Pos{0 , 1},   // 오
    };

    int count = 0;
    int maxCount = 200;

    while (pos != dest)
    {
        int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;

        if (count >= maxCount)
            return;

        if (CanGo(pos + front[newDir]))     // 1. 오른쪽 방향으로 갈 수 있습니까?
        {
            _dir = newDir;
            pos += front[_dir];
            _path.push_back(pos);
            count++;
        }
        else if (CanGo(pos + front[_dir]))  // 2. 정면 방향을 갈 수 있습니까?
        {
            pos += front[_dir];
            _path.push_back(pos);
            count++;
        }
        else                                // 3. 왼쪽으로 회전하세요.  
        {
            _dir = (_dir + 1) % DIR_COUNT;
        }
    }
    // 1. vector<Pos> path. index 
    // if(path[i] == path[i+1]) << 되돌아가는 경우이기 때문에 path 지워주자.
    // Stack               [a][b][c][d][d] [O]
    //                         pop          



    stack<Pos> s;
    for (int i = 0; i < _path.size() - 1; i++)
    {
        if (s.empty() == false && s.top() == _path[i + 1])
            s.pop();
        else
            s.push(_path[i]);
    }

    if (s.empty() == false)
        s.push(_path.back());

    vector<Pos> path;

    while (s.empty() == false)
    {
        path.push_back(s.top());
        s.pop();
    }
    reverse(path.begin(), path.end());
    _path = path;
}

void Player::BFS()
{
    _pos = _board->GetStartPos();
    Pos pos = _pos;
    Pos dest = _board->GetEndPos();

    _path.clear();
    _path.push_back(pos); // [시작 위치][다음 위치][][][도착지]

    Pos front[4] =
    {
        Pos{-1 , 0},  // 위
        Pos{0 , -1},  // 왼
        Pos{1 , 0},   // 아래
        Pos{0 , 1},   // 오
    };

    // discover , queue  , parent
    const int size = _board->GetSize();
    vector<vector<bool>> discovered(size, vector<bool>(size, false)); // 25정점 모두 false
    vector<vector<Pos>> parent(size, vector<Pos>(size, Pos{-1,-1})); // 부모가 정해지지 않았다.

    queue<Pos> q;
    q.push(pos);
    discovered[pos.y][pos.x] = true;  
    parent[pos.y][pos.x] = pos;        // 출발지점이 곧 부모인 녀석이 조건으로 쓰인다.

    while (q.empty() == false)
    {
        pos = q.front();
        q.pop();

        if (pos == dest)              // 의심.
            break;

        for (int i = 0; i < DIR_COUNT; i++)
        {
            Pos nextPos = pos + front[i];
            if (CanGo(nextPos) == false)
                continue;

            if (discovered[nextPos.y][nextPos.x])
                continue;

            q.push(nextPos);
            discovered[nextPos.y][nextPos.x] = true;
            parent[nextPos.y][nextPos.x] = pos;        // 출발지점이 곧 부모인 녀석이 조건으로 쓰인다.
        }
    }

    _path.clear();
    pos = dest;

    while (true)
    {
        _path.push_back(pos);
        if (pos == parent[pos.y][pos.x])
            break;
        pos = parent[pos.y][pos.x];
    }
    reverse(_path.begin(), _path.end());
}

// BFS -> 다익스트라(Best) -> Astar
// 도착지점

// CostVertex{int cost.}
// F G H 구조체

// F = G + H  최종 이동 거리. 
// G = 시작점에서 움직일 좌표로 이동하는데 드는 비용 ( 작을 수록 좋다, 어디로 움직이는지에 따라 다르다.)
// H = 휴리스틱. 추정치. 현재 위치. 최종 도착지점 까지의 거리.(작을 수록 좋다.) 고정

struct PQNode
{
    bool operator<(const PQNode& other) const { return f < other.f; }
    bool operator>(const PQNode& other) const { return f > other.f; }

    int f;
    int g;
    Pos pos;
};

void Player::Astar()
{
    _pos = _board->GetStartPos();
    Pos start = _pos;
    Pos dest = _board->GetEndPos();
    int size = _board->GetSize();

    const int NoParent = -1;

    // bool
    // parent
    vector<vector<bool>> closed(size, vector<bool>(size, false));
    vector<vector<Pos>> parent(size, vector<Pos>(size, Pos{ NoParent,NoParent }));
    vector<vector<int>> best(size, vector<int>(size, INT32_MAX));

    Pos front[8] =
    {
        Pos{-1 , 0},  // 위
        Pos{0 , -1},  // 왼
        Pos{1 , 0},   // 아래
        Pos{0 , 1},   // 오
        Pos{-1, -1},  // 위왼
        Pos{1, -1},   // 아왼
        Pos{1, 1},    // 아오
        Pos{-1, 1},   // 위오
    };

    // TODO : 왜 1이 아닌 10?  1.414
    int cost[8] =
    {
         2,
         8,
         14,
         8,
         30,
         30,
         30,
         30,
    };

    enum
    {
        DIR_COUNT = 8,
    };

    priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

    // Astar F,G,H
    // int f, int g, int h
    // 시작 지점에서 시작 지점으로 이동하는 비용을 계산하라
    // 비용 계산에서 음수가 나왔다. 수학적으로 음수를 나오지 못하게 하는 방법은? 절대값
    // TODO : 왜 1이 아닌 10?
    {
        int g = 0;
        int h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));
        pq.push(PQNode{ g + h, g, start }); // queue<q> q.push
        closed[start.y][start.x] = true;
        parent[start.y][start.x] = start;  // _path 조건
        best[start.y][start.x] = g + h;
    }

    while (pq.empty() == false)
    {
        PQNode node = pq.top();
        pq.pop();

        if (best[node.pos.y][node.pos.x] < node.f)
            continue;
        if (node.pos == dest)
            break;

        for (int i = 0; i < DIR_COUNT; i++)
        {
            Pos nextPos = node.pos + front[i];
            if (CanGo(nextPos) == false) continue;

            // 1. g는 이전 노드의 g값에 현재 이동 비용을 더해야 함
            int g = node.g + cost[i];
            // 2. h는 현재 탐색 중인 nextPos에서 목적지까지의 거리여야 함
            int h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

            // 3. 이미 찾은 경로보다 비용이 크다면 무시 (여기서 best의 역할이 발휘됨)
            if (best[nextPos.y][nextPos.x] <= g + h)
                continue;

            // 더 최적의 경로를 찾았네?

            pq.push(PQNode{ g + h, g, nextPos }); // queue<q> q.push
            closed[nextPos.y][nextPos.x] = true;
            parent[nextPos.y][nextPos.x] = node.pos;  // _path 조건
            best[nextPos.y][nextPos.x] = g + h;

        }
    }

    _path.clear();
    _pathIndex = 0;
    Pos pos = dest;


    while (true)
    {
        _path.push_back(pos);
        if (pos == parent[pos.y][pos.x])
            break;
        pos = parent[pos.y][pos.x];
    }
    reverse(_path.begin(), _path.end());
}



// 길찾기
// 문제해결 - 기존 해결 방식보다 뛰어난 문제 해결 방식을 찾는다.
// 우수법   - 순환하는 미로구조가 아니다.
// 알고리즘 이론 
// 자료구조 
// 그래프 -> 순회방식. 길찾기

// BFS
// 장점 : 미로를 이동할 때 비용이 일정할 때 사용한다.
// 단점 : 미로 이동 간에 비용이 다르다면 사용할 수 없다.

// 대각선으로 이동하는 게임. 물리법칙을 무시하는 게임.
// 해결 방법 : 비용을 추가한다. => 다익스트라 알고리즘  