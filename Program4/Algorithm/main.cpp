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


//   LastInFirstOUt : LIFO
//   []	   
//	 []
//	 [3]  << top
//	 [2]
//	 [1]
//   ctrl + z     1  2  3  4   5

// stack, queue - adopter (스스로 자료구조 성격x, 다른 자료구조(container) 이용해서 사용하는 형태)
// 개념적으로 사용하는 자료구조.
// stack 성질을 가진 코드로 구현하자 -> ctrl + Z
// vector사용하는데, push_back  pop_back
// iterator사용해서 첫번쨰 중간 원소에 접근하는 것을 정책적으로 막자.
// vector? 이터레이터로 추가 작업할 수 있는대? 실수
			
// vector, list, deque Stack 성능차이가 있겠다.
// Deque -- stack의 성능이 좋겠구나.


template <typename T, typename Container = vector<T>>
class Stack	  // LIFO
{
public:
	 void push(const T& value)
	 {
		 _container.push_back(value);
	 }

	 void pop()
	 {
		 _container.pop_back();
	 }

	 int top()
	 {
		 return _container.back();
	 }

	 int size()
	 {
		 return _container.size();
	 }

	 bool empty()
	 {
		 return _container.empty();
	 }

private:
	Container _container;

};

// FIFO - Queue

// 표,햄버거집 줄을 서야하는 것
// 햄버거가게					 ->
//            [0][1][2][3][4][5][][][][]
//           front

int main()
{
	Stack<int, vector<int>> s;
	s.push(1);
	s.push(2);
	s.push(3);

	cout << "Stack 자료 구조" << endl;
	while (s.empty() == false)
	{
		int count = s.top();
		s.pop();
		cout << count << " ";
	}
	cout << endl;
	
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	cout << "Queue 자료 구조" << endl;
	while (q.empty() == false)
	{
		int count = q.front();
		q.pop();
		cout << count << " ";
	}
	cout << endl;

}