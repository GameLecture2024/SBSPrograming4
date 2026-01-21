#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 자료구조 (선형) 

// [1][2,3,8] - [n] - [] -  [8] -  []	 -----
//  - 2,3, 8
// 사이클을 표현할 수 있는 어떤 자료 표현법? - Graph
// 정점(Vertex) 간선(Edges) 데이터 표현 방식을 Graph라고 부르자.

// 1정점 2정점 서로를 가리키고 있다. 무방향 그래프
//                                   방향 그래프
// 간선 가중치 있는가 없는가?  
// cycle이 있는가 없는가? 

// 추상적인 개념을 컴퓨터에게 알아들을 수 있도록 정의 - class

// 1. Graph Create!

// 2. Graph Traverse(순회) 
// -BFS, DFS

// 응용 미로 적용

struct Vertex
{
	vector<Vertex> edges;
};

// adjacent vector 인접한 백터
// adjacnet Matrix 인접한 행렬

vector<vector<int>> adjacent;

void CreateGraph_vector()
{
	adjacent = vector<vector<int>>(8);

	adjacent[0] = { 1, 2, 7 };
	adjacent[1] = { 0, 5, 7 };
	adjacent[2] = { 0, 3, 4 };
	adjacent[3] = { 2, 4 };
	adjacent[4] = { 2, 3 };
	adjacent[5] = { 1, 6 };
	adjacent[6] = { 5 };
	adjacent[7] = { 0, 1 };

    // Q? A정점 B정점이랑 실제로 연결되어 있나요?
	vector<int>& adj = adjacent[0]; // 1번 정점 6이랑 연결되어있나요?
	bool connect = (find(adj.begin(), adj.end(), 7) != adj.end());
}

vector<vector<bool>> adjacent2;

void CreateGraph_vector2()
{
	// 연결이 안되어 있을 때 숫자를 무엇으로 표현할래? 0 -1 INT_MAX	        true 0
	// 연결이 되어있을 때 어떤 숫자로 표현할래?							    false 1
	// bool
	adjacent2 = vector<vector<bool>>(8, vector<bool>(8, false));
	// [from][to]
	adjacent2[0][1] = true;
	adjacent2[0][2] = true;
	adjacent2[0][7] = true;
	adjacent2[1][0] = true;
	adjacent2[1][5] = true;
	adjacent2[1][7] = true;
	adjacent2[2][0] = true;
	adjacent2[2][3] = true;
	adjacent2[2][4] = true;
	adjacent2[3][2] = true;
	adjacent2[3][4] = true;
	adjacent2[4][2] = true;
	adjacent2[4][3] = true;
	adjacent2[5][1] = true;
	adjacent2[5][6] = true;
	adjacent2[6][5] = true;
	adjacent2[7][0] = true; 
	adjacent2[7][1] = true;

	bool connect = adjacent2[0][6];

}

vector<vector<int>> adjacent3;

void CreateGraph_Matrix()
{
	// 연결이 되어있으면 1
	// 안되어 있으면 -1

	adjacent3 =
	{		 
		{-1,+1,+1,-1,-1,-1,-1,+1 },  // 0정점
		{+1,-1,-1,-1,-1,+1,-1,+1 },
		{+1,-1,-1,+1,+1,-1,-1,-1 },
		{-1,-1,+1,-1,+1,-1,-1,-1 },
		{-1,-1,+1,+1,-1,-1,-1,-1 },
		{-1,+1,-1,-1,-1,-1,+1,-1 },
		{-1,-1,-1,-1,-1,+1,-1,-1 },
		{+1,+1,-1,-1,-1,-1,-1,-1 }
	};
}

// 그래프 생성
// 그래프 순회

// 
// DFS : Depth  First  Search (깊이 우선 탐색)
// BFS : Beneath First Search (너비 우선 탐색)

// DFS - 재귀 함수 : 자기 자신을 호출하는 함수
// BFS - Queue 사용 : FIFO

vector<bool> visited(8, false);

// 1

// [2]
   // [6]
      // [7]
   // [8]
      // [1] (방문? skip)x
	  // [2]			 x
// [3]
    // [4]
	   // [5]
	// [5] x
// [8]


//
// 모든 선이 연결되어 있는지 확인할 때 유용 - 
void DFS(int here)
{
	visited[here] = true; 
	cout << "방문한 정점 : " << here + 1 << endl;

	for (int i = 0; i < adjacent[here].size(); i++)
	{
		int there = adjacent[here][i];
		if (visited[there] == false)
			DFS(there);
	}

}

void DFSmatrix(int here)
{
	visited[here] = true;
	cout << "방문한 정점 : " << here + 1 << endl;

	for (int there = 0; there < adjacent3[here].size(); there++)
	{
		if (adjacent3[here][there] == -1)
			continue;

		if (visited[there] == false)
			DFSmatrix(there);
	}
}

// queue   [1] [2] [3] [8] [6] []
//         [2][3][8][6]
// 	       [3][8][6]
// discover 발견했다.
// here = 3 

// Queue
// bool 
// parent   - 시작지점 도착지점
// distance	- 1
// [] {1,2,3}
void BFS(int here)
{
	vector<bool> discovered(8, false);
	vector<int> parent(8, -1);
	vector<int> distance(8, -1);
	queue<int> q;
	q.push(here);
	discovered[here] = true;
	parent[here] = here;     // 시작 지점은 부모가 나 자신이다.
	distance[here] = 0;

	while (q.empty() == false)
	{
		int here = q.front();
		q.pop();
		
		for (int there : adjacent[here])
		{
			if (discovered[there])
				continue;
			q.push(there);
			discovered[there] = true;
			parent[there] = here;     // 시작 지점은 부모가 나 자신이다.
			distance[there] = distance[here] + 1;
		}
	}

	int dest = 6;
	vector<int> _path;
	while (true)
	{
		_path.push_back(dest);
		if (dest == parent[dest])
			break;
		dest = parent[dest];
	}

}



int main()
{
	CreateGraph_vector();
	CreateGraph_vector2();
	CreateGraph_Matrix();
	//DFS(0);
	//DFSmatrix(0);
	BFS(0);
}