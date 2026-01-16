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

struct Player
{
	int id;
};

// iterator : ptr 내장하고 있는 클래스.	wraping	 
// STL container 안에서 포인터로 쓴다.

template <typename T>
class Iterator
{
public:
	Iterator() : _ptr(nullptr) {}
	Iterator(T* ptr) : _ptr(ptr) {}

public:
	Iterator& operator++()	// 전위 연산자
	{
		_ptr++;
		return *this; // this 클래스의 주소.	  _ptr주소의 주소
	}

	Iterator& operator++(int)  // 후위 연산자를 표현하는 방법 it++
	{
		Iterator temp = *this;	// 새로운 객체 생성. 메모리 할당 대입.
		_ptr++;
		return temp;
	}

	Iterator& operator--()
	{
		_ptr--;
		return *this;
	}
	Iterator& operator--(int)  // 후위 연산자를 표현하는 방법 it++
	{
		Iterator temp = *this;	// 새로운 객체 생성. 메모리 할당 대입.
		_ptr--;
		return temp;
	}

	bool operator==(const Iterator& other)
	{
		return _ptr == other._ptr;
	}

	bool operator!=(const Iterator& other)
	{
		return !(*this == other);
	}

	Iterator operator+(const int count)
	{
		Iterator temp = *this;
		temp._ptr += count;
		return temp;
	}

	T& operator*() { return *_ptr; }

	// int* ptr;  *ptr;

	//                 ++it;  	 it++;	 미세한 성능 차이.

public:
	T* _ptr;
};

template <typename T>
class Vector
{
public:
	Vector() : _data(nullptr), _size(0), _capacity(0) {}
	~Vector()
	{
		if (_data)
			delete[] _data;
	}
public:
	// 데이터가 없을떄 _size 0 : _capacity 0
	void push_back(const T& data)
	{
		if (_size == _capacity)
		{
			int newCapacity = _capacity * 1.5;  // 0     1 * 1.5 = 1.5 1
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}
		_data[_size] = data;

		_size++;
	}

	void reserve(int capacity)
	{
		// capacity 크기만큼 data를 new만든다.  >> 새로운 메모리 공간을 생성한다.
		_capacity = capacity;

		T* newData = new T[_capacity];
		// 기존 데이터를 새로운 공간으로 이주시켜줘.(★★★★)

		for (int i = 0; i < _size; i++)
			newData[i] = _data[i];

		if (_data)
			delete[] _data; // 기존

		_data = newData;
	}

	T& operator[](const int index) {
		return _data[index];
	}

	int size() { return _size; }
	int capacity() { return _capacity; }
public:
	typedef Iterator<T> iterator;

	iterator begin() { return iterator(&_data[0]); }
	iterator end() { return begin() + _size; }


private:
	T* _data;
	int _size;
	int _capacity;
};


int main()
{

	// 플레이어를 최대 10명까지만 저장할 수 있다.
	// 계속 층이 올라가고 있는 아파트 -> 실시간 추가할 수 있는 배열 같은 것이 있으면 좋겠다.
	// array (고정 배열)  <-> 가변 배열	 vector , list
	// 그러면 무조건 array가 vector보다 안좋나요? 

	// (맨처음) (맨끝) (중간) 삽입 삭제   Good Bad
	// 임의 접근 (Random Access)         Good Bad

	// 123469131928
	// reserve 최소한으로 하려면 어떻게 하면 좋을까? 
	// 미리 만들어서 빠르게 사용할 수 있다. 갯수를 미리 만들어 두고, 
	// 1000명.  10000명 ->(10000) 15000 -> 30000 -> 45000 -> ....   10만.

	Vector<int> v;
	v.reserve(100);
	for (int i =0; i < 25; i++)
	{
		v.push_back(i);
		cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
	}

	

	auto vStart = v.begin();
	cout << "후위 연산자, 전위 연산자" << endl;
	//cout << "전위 연산자 : " << *(++vStart) << endl;    1이 더해진 후에 값이 나왔습니다
	cout << "후위 연산자 : " << *(vStart++) << endl;		 // 0을 먼저 출력하고 ++일어났다.
	//v.clear();
	//vector<int> temp;
	//swap(v, temp);
	//cout << v.size() << " " << v.capacity() << endl;

	// [999][0][1][2] //[3][4] 
	// [999][0][1][2]    

	// [0][1] [999] [2]

	// 면접 단골 질문(★★)
	// Q) 데이터 insert, 데이터 push_front 지원X 안하는 이유
	// A) 느리다. n만큼  order of N -  O(N)

	// Random Access(★★★★★)   시작 주소 + <<  ---->  주소가 연속적으로 배치가 되어 있기 때문에
	// Id 45000         _data[45000]    O(1)  
	

	// iterator << 뭘까 ?
	// v.push_front(); vector 녀석은 push_front지원을 안해주구나 없구나.
	// v.insert()

	// iterator가 뭔가요? ptr인데, 자료구조에 귀속되어 있는 ptr
	// 결론 : STL 자료구조(컨테이너) - 반복자(iterator)를 통해서 조작할 수 있다.

	auto itBegin = v.begin(); 
	auto itEnd = v.end();
	cout << endl;
	
	
	//v.insert(v.begin() + 5, 9999);
	//v.erase(v.begin() + 5);
	
	// 99번 째 아이디를 가지고 있는 플레이어를 삭제해주세요.
	
	for (auto it = v.begin(); it != v.end();)
	{
		int data = (*it);
	
		if (data == 3)
		{
			//it = v.erase(it);     // 
		}
		else
		{
			++it;
		}		
	}
	
	for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << (*it) << " ";
	}

	// remove_if()
}