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
#include <memory.h>    
using namespace std;

// DP 대표 문제 풀기
// 조합 (combination)
// 피보나치 수열 (fibo)  = ( 0) (1) (2) (3)

// 게임 코드 구현 x
// AI 데이터 분석.
// 코딩 테스트. 좋아합니다.

vector<int> dp;

int Fibo(int n)
{
	// 기저 사항
	// 탈출할 수 있는 조건.

	dp.resize(n + 1);

	dp[0] = 0;
	dp[1] = 1;
	
	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2];	 // 점화식 F(n) = F(n-1) + F(n-2)
	}

	return dp[n];
}


int cache[100];



int LIS(int pos, vector<int>& nums)
{
	int& ret = cache[pos];
	if (ret != 0)
		return ret;
	ret = 1;

	for (int i = pos + 1; i < nums.size(); i++)
	{
		if (nums[pos] < nums[i])
			ret = max(ret, 1 + LIS(i, nums));
	}

	return ret;
}


int main()
{
	memset(cache, 0, sizeof(cache));
	//[10,9,2,5,3,7,101,18]
	vector<int> nums{ 10,9,2,5,3,7,101,18 };

	int ret = 0;

	for (int pos = 0; pos < nums.size(); pos++)
		ret = max(ret, LIS(pos, nums));


	cout << ret;
	// 길이를 반환해야한다.

}


// leetcode 알고리즘 공부.
// 백준
// 프로그래머스
// 오래했다. 1년 - 1년( )//  - 4~5 
// 쿼드 트리. 최적화. 게임의 데이터. 



