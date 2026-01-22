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
#include <string>
using namespace std;

// minDistance 구하는 방법.
// n번 순회해서 제일 작은 값을 고른다.

int minDistance()
{
	vector<int> v;

	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	v.push_back(40);

	int bestValue = INT32_MAX; // 값이 쌀 수 록 싸다.

	for (int i = 0; i < v.size(); i++)
	{
		if (bestValue < v[i])
			continue;

		// 아래쪽 내려왔다? 더 작은 값을 찾았구나
		bestValue = v[i];

	}

	cout << bestValue << endl;

	return bestValue;
}

// 우선 순위 큐.
// 우선 순위가 높은 값부터 출력해주는 특별한 컨테이너.
// 값이 가장 큰 것을 위로, 값이 가장 작은 것을 위로
// 가장 작거나(큰) 값을 O(1) 출력할 수 있다.

// 힙 트리
// 트리 <<


void examPQ()
{
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 0; i < 20; i++)
	{
		int rValue = rand() % 100;
		pq.push(rValue);
	}

	while (pq.empty() == false)
	{
		int count = pq.top();
		pq.pop();

		cout << count << " ";
	}

}

// "계층구조를 가지는" + 정점과 간선으로 구성된 데이터 표현 방식
// 트리는 그래프의 특수한 하나의 형태이다.

// 트리 용어
/*
*  루트
   부모
   자식
   형제
   선조
   자손
   잎(leaf)
   깊이(depth)   :  선택한 노드에서 루트까지의 간선의 수 
   높이(height)  :  Max(depth)
   서브트리
*/

using NodePtr = shared_ptr<struct Node>;

struct Node
{
	Node() {}
	Node(const string& data) : _data(data) {}

public:
	string _data;
	vector<NodePtr> children;
};

NodePtr CreateTree()
{
	NodePtr root = make_shared<Node>("S사의 게임 조직도");
	// 아트팀, 기획팀, 프로그래밍팀
	{
		NodePtr node = make_shared<Node>("아트팀");
		root->children.push_back(node);
		{
			NodePtr leaf = make_shared<Node>("A");
			node->children.push_back(leaf);
		}
		{
			NodePtr leaf = make_shared<Node>("B");
			node->children.push_back(leaf);
		}
	}
	{
		NodePtr node = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodePtr leaf = make_shared<Node>("A");
			node->children.push_back(leaf);
		}
		{
			NodePtr leaf = make_shared<Node>("B");
			node->children.push_back(leaf);
		}
	}

	return root;
}

// 트리 -> 재귀함수

void Print(NodePtr root, int depth)
{
	for (int i = 0; i < depth; i++)
		cout << "-";

	cout << root->_data << endl;

	for (auto& child : root->children)
		Print(child, depth + 1);

}

// 트리 규칙을 정한다. 정책을 정한다.
// 강제로 제한. 2명 이하로만 가질 수 있다. BST
// 힙 트리. 나만의 트리 규칙이 있겠구나.
// 부모는 항상 자식보다 우선 순위가 높은 가치를 가진다.
// 최대 자식은 2개만 가질 수 있는데, 왼쪽 부터 채워나가야 한다.
// [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13]

// left children : 	i x 2 + 1;
// right children : i x 2 + 2;
// parent : (i - 1) / 2

int main()
{
	//srand(time(nullptr));
	//minDistance();
	//examPQ();
	NodePtr root =  CreateTree();
	Print(root, 0);
}

