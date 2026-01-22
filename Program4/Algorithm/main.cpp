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

// 데이터를 push할때도 시간을 발생.
// vector가장 큰 특징. push_back 매우 빠르다 O(1)
// 최소 값 찾을려면 n번도 해야 한다 -> O(n)

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


// push O(logN)
// top() O(1)
template<typename T, typename Container = vector<T>>
class Priority_queue
{
public:

	// left children : 	i x 2 + 1;
	// right children : i x 2 + 2;
	// parent : (i - 1) / 2

	void push(const T& value)
	{
		_heap.push_back(value);

		int now = static_cast<int>(_heap.size()) - 1;

		while (now > 0)
		{
			int parent = (now - 1) / 2;

			if (_heap[now] < _heap[parent])	  // 나 부모한테 졌어요.
				break;

			// 부모를 이겼다. 나랑 바꿔
			::swap(_heap[parent], _heap[now]);
			now = parent;
		}
	}
	void pop()
	{
		_heap[0] = _heap.back();  // 왼쪽 부터 채워나가기 규칙 지키기.
		_heap.pop_back();

		int now = 0;

		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			if (left >= _heap.size())
				break;

			int next = now;
			if (_heap[next] < _heap[left])
				next = left;
			
			if (right < _heap.size() && _heap[next] < _heap[right])
				next = right;

			if (next == now)
				break;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}
	T& top()
	{
		return _heap[0];
	}

	bool empty()
	{
		return _heap.empty();
	}

private:
	Container _heap = {};
};


void examPQ()
{
	Priority_queue<int, vector<int>> pq;

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



// 트리 규칙을 정한다. 정책을 정한다.
// 강제로 제한. 2명 이하로만 가질 수 있다. BST
// 힙 트리. 나만의 트리 규칙이 있겠구나.
// 부모는 항상 자식보다 우선 순위가 높은 가치를 가진다.
// 최대 자식은 2개만 가질 수 있는데, 왼쪽 부터 채워나가야 한다.
// [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13]



int main()
{
	srand(time(nullptr));
	minDistance();
	examPQ();

}

