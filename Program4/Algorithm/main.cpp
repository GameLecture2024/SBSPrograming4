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

// 자료구조 Standard Template Library 클래스. 데이터를 특성에 맞게 저장하는 컨테이너. 
// --------------------- 선형    : array vector list deque stack queue
// --------------------- 비선형  : map set hash-table

// sequential  절차적 컨테이너 << array 배열
// relational  관계형 컨테이너

// iterator : ptr 내장하고 있는 클래스.	wraping	 
// STL container 안에서 포인터로 쓴다.

// class   (T == int 4) + Node 8 + 8 = 20
// Node 크기 측정. 4 + 나자신(4 + 나자신 + 나자신) + 나자신	  << 못쓴다
// Node*  (void*) 주소를 저장하겠다. class Type이 Node인 녀석.


// [꼬리] -> [머리]
// [꼬리] <- [머리]

// 단방향
// 양방향 
// 순환구조
template <typename T>
class Node
{
public:
	Node() : _prev(nullptr), _next(nullptr), _data(T()) {}
	Node(const T& val) : _prev(nullptr), _next(nullptr), _data(val) {}
public:
	T _data;
	Node* _prev;
	Node* _next;
};

template <typename T>
class Iterator
{
public:
	Iterator() : _node(nullptr) {}
	Iterator(Node<T>* node) : _node(node) {}

public:
	Iterator& operator++()	// 전위 연산자
	{
		_node = _node->_next;
		return *this; // this 클래스의 주소.	  _ptr주소의 주소
	}

	Iterator operator++(int)  // 후위 연산자를 표현하는 방법 it++
	{
		Iterator temp = *this;	// 새로운 객체 생성. 메모리 할당 대입.
		_node = _node->_next;
		return temp;
	}

	Iterator& operator--()
	{
		_node = _node->prev;
		return *this;
	}
	Iterator operator--(int)  // 후위 연산자를 표현하는 방법 it++
	{
		Iterator temp = *this;	// 새로운 객체 생성. 메모리 할당 대입.
		_node = _node->prev;
		return temp;
	}

	bool operator==(const Iterator& other)
	{
		return _node == other._node;
	}

	bool operator!=(const Iterator& other)
	{
		return !(*this == other);
	}

public:
	Node<T>* _node;
};


// 	[tail] <->   [head]	    

template <typename T>
class List
{
public:
	List() : _size(0)
	{
		_head = new Node<T>();
		_tail = new Node<T>();
		_head->_next = _tail;
		_tail->_prev = _head;
	}
	~List()
	{
		while (_size > 0)
			pop_back();

		delete _head;
		delete _tail;
	}
public:

	// [ tail ]	- Node			   [head]
	void push_back(const T& val)  // add
	{
		AddNode(_tail, val);
	}

	void pop_back()				  // remove
	{
		RemoveNode(_tail->_prev);
	}
	// [ tail ]	- [_prevNode]	 -[ Node] -	[before]	   [head]
	Node<T>* AddNode(Node<T>* before, const T& val)
	{
		Node<T>* newNode = new Node<T>(val);
		Node<T>* prevNode = before->_prev;

		newNode->_next = before;
		before->_prev = newNode;

		newNode->_prev = prevNode;
		prevNode->_next = newNode;	  // 

		_size++;

		return 	newNode;
	}

	// [ tail ]	- [_prevNode] -[ Node] -	[_nextNode]	   [head]
	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* nextNode = node->_next;
		Node<T>* prevNode = node->_prev;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;
	
		delete node;
		_size--;

		return 	nextNode;
	}


	int size() { return _size; }

public:
	typedef Iterator<T> iterator;

	iterator begin() { return iterator(_head->_next); }
	iterator end() { return iterator(_tail); }

	iterator insert(iterator it, const T& value)
	{
		Node<T>* node = AddNode(it._node, value);
		return iterator(node);
	}

	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}


private:
	Node<T>* _tail;
	Node<T>* _head;
	int _size;
};

// 배열 -> vector -> list 

//                                          Vector                        List									      
//  뒤에 삽입/삭제 속도						  o(1)						   o(1)
//  중간 삽입/삭제 (첫번째, 아무 위치)	   		  o(n)						   o(1)
//  임의 접근								  o(1)                         o(n)

// list 노드 기반으로 데이터를 연결. class node

// list::iterator 함께 사용해야지만 중간 삽입 삭제 빠르다.
// 장점 : 중간 삽입 삭제 빠르다
// 단점 : 임의 접근이 느리다.

// 중간을 삭제하려면 중간에 접근을 해야하는데 단점이 장점을 가리니깐 장점이 아니지 않나요?
// 데이터를 찾아서 삭제를 하려고하면 느립니다. << list 자체가 사용에 불편한 이유입니다.
// iterator 도구 사용하기 때문에. iterator미리 찾아 뒀더라면?  매우 빠르다.

int main()
{
	List<int> li;

	//   [999] [1] [2] [3] [444]  [4] [5]

	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);
	li.push_back(5);

	//li.push_front(999);
	//
	auto insertIt = li.begin();
	
	for (int i = 0; i < 4; i++)	  // <<<< 주의 깊게 생각(★★★★)
	{
		insertIt++;
	}
	
	li.insert(insertIt, 444);		    // 문제

	for (auto it = li.begin(); it != li.end(); ++it)
	{
		cout << it._node->_data << " ";
	}

}