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

using namespace std;

// 자료구조 Standard Template Library 클래스. 데이터를 특성에 맞게 저장하는 컨테이너. 
// --------------------- 선형    : array vector list deque stack queue
// --------------------- 비선형  : map set hash-table

int main()
{
    cout << "선형 자료구조 공부" << endl; 
    cout << "vector 살펴보자" << endl;

    cout << "라이브러리 제공되는 기능을 사용해본다." << endl;
    cout << "vector 어떻게 만들어 졌는가 원리?" << endl;

    cout << "뭐가 좋고 뭐가 나쁜대?" << endl;
    cout << "코드를 작성을 하고, 비교" << endl;
    cout << "어떻게 분석할까?" << endl;

    // 둘 중에 뭐가 더 좋은 코드일까?
    // 빨리 실행될수록 좋을 것 같다.  -> 슈퍼컴퓨터, 컴퓨터 시간이 달라요(코드가 같은대)
    // 느낌적으로 좋은 것 같다.
    // 비교를 하기 위해서 약속된 내용을 따르자 -> big O  (order of O) 빅오표기법

    // 시간적으로 얼마나 빠른가?

    // 공간적으로 효율적 인가?

    // N^3 

    cout << "빅오표기법이 무엇일까?" << endl;
    cout << "실행이 자주 될까 체크" << endl;

    int a = 10; // 1번

    for (int i = 0; i < a; i++) // n번 실행했다.   n을 아주 큰 수 늘린다 가정.
        cout << i << " ";

    int target = 100;

    while (target != a)
    {
        target /= 2;

        if (a > target)
        {

        }
    }
    // 범위를 줄이고
    for (int x = 0; x < 6; x++)
    {
        if (6 + x == a)
        {

        }
    }

    //  n = 1
    //  n = logn
    //  n = ax + b;
    //  n = n * log n;
    //  n = ax^2 + bx + c;

}