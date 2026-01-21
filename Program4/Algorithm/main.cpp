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

vector<vector<int>> adjacent;

void CreateGraph()
{
	adjacent =
	{
		{-1,10,+1,-1,-1,-1,-1,+3 },
		{+8,-1,-1,-1,-1,+2,-1,+1 },
		{+7,-1,-1,+1,+3,-1,-1,-1 },
		{-1,-1,+9,-1,+4,-1,-1,-1 },
		{-1,-1,+6,+5,-1,-1,-1,-1 },
		{-1,+3,-1,-1,-1,-1,+5,-1 },
		{-1,-1,-1,-1,-1,+4,-1,-1 },
		{+8,+2,-1,-1,-1,-1,-1,-1 }
	};
}

// BFS 방식 + 가중치 추가한 버전.
int Dijkstra(int here)
{
	struct CostVertex
	{
		int vertex;
		int cost;
	};

	vector<int> parent(8, -1);
	vector<int> best(8, INT32_MAX);	    // 작은 값이 좋다.

	

	list<CostVertex> discovered;
	discovered.push_back(CostVertex{ here, 0 } );
	best[here] = 0;      // 거리
	parent[here] = here; // 부모의 정점 = 내 정점(0 의 정점의 부모는 0이다)
	
	while (discovered.empty() == false)
	{
		list<CostVertex>::iterator bestIt;
		int bestCost = INT32_MAX;
		// 가장 비용이 낮은 것을 선택해서 넣어야 한다.
	    // mindistance 구하기 위한 알고리즘.

		for (auto it = discovered.begin(); it != discovered.end(); ++it)
		{
			if (it->cost < bestCost)      // it++ it++ it++ it++ it++
			{
				bestCost = it->cost;
				bestIt = it;
			}
		}

		// 반복문이 끝나면 minDistance 데이터 구할 수 있다.
		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);    // 가장 비용이 싼 it 지워버리고 남은 것들도. 다시 정의하기 위해서

		if (best[here] < cost)       //  통과 못했다? 너는 최선이 아니야. 위로올라가
			continue;

		//  best << 최선의 코드를 바꿔치기
		
		for (int there = 0; there < adjacent.size(); there++)
		{
			if (adjacent[here][there] == -1)
				continue;

			int nextCost = best[here] + adjacent[here][there];
			if (best[there] <= nextCost)         // nextCost 최선이 아니다? 변경해줄 필요없다.
				continue;
			
			best[there] = nextCost;
			parent[there] = here;
			discovered.push_back(CostVertex{ there, nextCost });
		}
	}

	return 0;

}


int main()
{
	CreateGraph();
	Dijkstra(0);
}

// Maze 적용은 하지 않을겁니다
// BFS ->  다익스트라 모든 간선의 비용이 1인 것과 같다.  (?)
// Priority_Queue (우선 순위 큐)
// AStar ->  다익스트라 + @  // 