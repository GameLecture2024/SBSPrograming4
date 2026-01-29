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
#include <Windows.h>
using namespace std;

// Hash Table

// 비용. BFS -> mindistance N^2 젤작은거 찾자. - 전수 조사
// sort() -> nlogn
// PQ -> O(1) - logn

// [0] vector
// [1] map vs hash table  
// map -> logn

// table - 시간을 위해 공간을 사용했다.
// 어디까지 내줄건데?  

void Table()
{
	struct User
	{
		int id = 0;
		int value;
	};

	vector<User> users;	 
	users.resize(1000);
	
	users[999] = User{ 999, 999 * 10 };

	// Q 999번 아이디의 유저가 가지고 있는 값을 출력하세요.

	cout << "유저가 가지고 있는 값 : " << users[999].value << endl;
}

// hash	- 
// hashing?
// 너무 많다. => 1억 ( ) => 1A  + 


void Hash()
{
	struct User
	{
		int id = 0;
		string name;
	};

	vector<User> users;

	users.resize(1000);

	int userId = 123'456'789;
	int key = (userId % 1000); // 0 ~ 999 = 1000개

	users[key] = User{ userId, "AAA"};

	int user2Id = 789;
	int key2 = (user2Id % 1000);

	users[key] = User{ user2Id, "BBB" };

	// 숫자가 너무 크다. => 쪼개겠다. bucket [        ]

	// 해결하기 위한 방법들을 생각을 했어야 한다.
	// 이미 데이터가 들어 잇네? 넣지 않고 +1 그 다음에 자리가 있나? 선형 조사법 
	// hash(key) + n^2  // ->									이차 조사법		   

	// 체이닝 : 중복된 데이터가 있으면? 연속적으로 데이터를 이어가겠다.

}


// 789  {   ["AAA] -> [789, "BBB"]                          }
// 이 데이터들 중에서 아이디가 AAA인 녀석을 찾아라?
// 함수 -> 중복이 안되도록 하는 엄청나게 어썸한 코드. -> prime number..  제곱 수 ...  digit ...  

void HashChaining()
{
	struct User
	{
		int id = 0;
		string name;
	};

	vector<vector<User>> users;

	users.resize(1000);

	int userId = 123'456'789;
	int key = (userId % 1000); // 0 ~ 999 = 1000개
	int user2Id = 789;
	int key2 = (user2Id % 1000);


	users[key].push_back(User{ userId, "AAA" });
	users[key2].push_back(User{ user2Id, "BBB" });

	for (User& user : users[key])
	{
		if (user.id == user2Id)
		{
			cout << user.name << endl;
		}
	}

}

// struct User - id value - id * 100

// map -> O(n)
// Hash Table -> 탐색 시간 O(1)
// 공간을 사용해서 시간을 매우 추구한 버전이다.

// 로딩.. 데이터 초기화
// 게임 플레이 => Database 99 -> 123 -> 10 
// 99 <-  insert [10]
// n << 아이템 업데이트. 1만. << 게임 렉이 걸려요
// map< >  -  hash table< >	STL Cpp== unordered_map , C# == Dictionary


// vector, map, hash table << data table;

int main()
{
	//Table();
	//Hash();
	//HashChaining();

	unordered_map<int, string> users;

	users.insert(make_pair(123'456'789, "AAA"));
	users.insert(make_pair(789, "BBB"));

	cout << users[789] << endl;
}



