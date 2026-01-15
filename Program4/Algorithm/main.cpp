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

// 면접에서 직접 구현 <<-
// 만들기 위한 이론적인 원리

int main()
{
	// 플레이어를 최대 10명까지만 저장할 수 있다.
	// 계속 층이 올라가고 있는 아파트 -> 실시간 추가할 수 있는 배열 같은 것이 있으면 좋겠다.
	// array (고정 배열)  <-> 가변 배열	 vector , list
	// 그러면 무조건 array가 vector보다 안좋나요? 

	// (맨처음) (맨끝) (중간) 삽입 삭제   Good Bad
	// 임의 접근 (Random Access)         Good Bad

	vector<int> v;

	for (int i =0; i < 25; i++)
	{
		v.push_back(i);
		cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
	}
	  
	// iterator << 뭘까 ?
	// v.push_front(); vector 녀석은 push_front지원을 안해주구나 없구나.
	// v.insert()

	// iterator가 뭔가요? ptr인데, 자료구조에 귀속되어 있는 ptr
	// 결론 : STL 자료구조(컨테이너) - 반복자(iterator)를 통해서 조작할 수 있다.

	vector<int>::iterator itBegin = v.begin(); 
	vector<int>::iterator itEnd = v.end();
	cout << endl;
	

	v.insert(v.begin() + 5, 9999);
	v.erase(v.begin() + 5);

	// 99번 째 아이디를 가지고 있는 플레이어를 삭제해주세요.

	for (vector<int>::iterator it = v.begin(); it != v.end();)
	{
		int data = (*it);

		if (data == 3)
		{
			it = v.erase(it);     // 
		}
		else
		{
			++it;
		}		
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << (*it) << " ";
	}

	// remove_if()
}