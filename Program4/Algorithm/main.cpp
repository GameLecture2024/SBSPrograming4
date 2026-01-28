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

// 버블 선택 삽입
// 버블
// bubble - 보글보글 - 거품 - 위로 (정렬) 

// [4][3][1][9][7]
// [3][4][1][9][7] - [3][1][4][9][7] - [3][1][4][7][9]  1회차.  
// [1][3][4][7][9] - 2회차

// ----- 10개의 숫자를 던져준다음에. 알아서 정렬하는 코드를 작성해보세요... -----

// O(n) - n^2
void BubbleSort(vector<int>& v)
{
	int n = v.size();

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (v[j] > v[j + 1])
			{
				swap(v[j], v[j + 1]);
			}
		}
	}

}

// 선택 : 작은 것을 앞으로 보내자.
// 
// [4][3][9][1][7]	 ?? 5개 중에서 제일 작은 것을 어떻게 구할래?
// [1][3][9][4][7] 1회차
// [1][3][4][9][7]
// [1][3][4][7][9]  
// n * n = n^2
// 버블 소트보다는 효율적이다. n에 크기에 비하면 보잘 것 없다.
void SelectSort(vector<int>& v)
{
	int n = v.size();

	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;

		for (int j = i + 1; j < n; j++)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}
		swap(v[i], v[bestIdx]);
	}

}

// 삽입
// [4] | [3] [9] [1] [7]  
// 정렬 | 비정렬
// [3][4] | [9][1][7]
// [3][4][9] | [1][7]
// [1][3][4][9] | [7]
// [1][3][4][7][9]

// [1][3][4][9][7]

// n * n = n^2
// 특별한 case : 데이터가 거의 정렬이 되어 있으면 효율적이다.
// [                    ] 9000   [1000]
void InsertSort(vector<int>& v)
{
	int n = v.size();

	for (int i = 1; i < n; i++)
	{
		int insertData = v[i];

		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
				v[j + 1] = v[j];
			else  // [i] j의 값이 작으면 -- 내 위치.
				break;
		}
		v[j + 1] = insertData;
	}
}
 
// 순차 컨테이너 (vector, list ,deque) - 정렬 되지 않은 데이터가 들어온다.
// 탐색! - n번 돌건가?  -> logN  - 정렬. 

// 머지, 힙, 퀵 sort  
// greater - 작은 것 위, less 큰 것 위
// 빅오표기법
void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	// N * logN
	for (int num : v)
		pq.push(num);

	v.clear();

	// N * logN 
	while (pq.empty() == false)
	{
		int count = pq.top();
		pq.pop();
		v.push_back(count);
	}
}
// NlogN + NlogN = NlogN

// 합병 (merge)

// Divide and Conquer 분할 정복
// [4][3][1][9][7]

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftidx = left;
	int rightidx = mid + 1;
	
	vector<int> temp;

	while (leftidx <= mid && rightidx <= right)
	{
		if (v[leftidx] < v[rightidx])
		{
			temp.push_back(v[leftidx]);
			leftidx++;
		}
		else
		{
			temp.push_back(v[rightidx]);
			rightidx++;
		}
	}
    ///////---------------------------------------////// [왼쪽파트] [오른쪽 파트]

	// 왼쪽 먼저 끝났을 때
	if (leftidx > mid)
	{
		while (rightidx <= right)
		{
			temp.push_back(v[rightidx]);
			rightidx++;
		}
	}
	else
	{
		while (leftidx <= mid)
		{
			temp.push_back(v[leftidx]);
			leftidx++;
		}
	}
	
	// temp -> vector 넣어준다.
	for (int i = 0; i < temp.size(); i++)
		v[left + i] = temp[i];

}

// n * log N -- 정확한 수치. <<
void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}

// quick sort. 

// 버선삽 - N^2
// 힙, Merge, quick

// 퀵소트
// quick - 빠르다?	- merge비슷하다.  - [ ] 나누기.
// merge -> middle 
// 피벗 빠르게 선택했다. 

// pivot

// [5] | [1][3][7][9][2][4][6][8]
// P	 	 	l		 h	     	     pivot 어느 위치에 있으면 가장 어울릴까?	<-[5]->
//       [1][3][4][9][2][7][6][8]
//                 l  h  
//      [2][1][3][4][5][9][7][6][8]                  
// 				   h  l
//      [2][1][3][4][5][9][7][6][8]      
// 1> low high low->   <-high  pivot값
// // v[low] <= p        v[high] >= p
// 2> low index값(2)  <  high(5)	  swap
// 3>  swap(v[left],v[h])


// Heap vs Merge vs Q [Sort]
// nlogn              n^2, nlogn
// nlogn 시간을 갖는다.
// Q-sort 시간이 쪼금 효율적이지 않다. 그렇다면 무엇이 더 좋을까?
// 

int  Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	// 횟수가 많아지겠다 [(N) - logN  *  n]	 n^2. n logn
	while (low <= high)
	{
		while (low <= right && pivot >= v[low])	 // 배열 범위  && 피벗 비교	
			low++;
		
		while (high >= left + 1 && pivot <= v[high])   // 배열 범위  && 피벗 비교	
			high--;

		if (low < high)
			swap(v[low], v[high]);
	}

	swap(v[left], v[high]);
	return high;             // pivot이 위치해야할 인덱스 값.               
}

void QuickSort1(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivot = Partition(v, left, right);
	QuickSort1(v, left, pivot-1);  // 왼쪽 파트
	QuickSort1(v, pivot+1, right); // 오른쪽 파트
}

// 탐색. N      - 전수 조사 N
// 1 ~ 30  15. - 키 정렬.
// nlogn * logn = nlog(n제곱)

int main()
{
	vector<int> v{ 4,3,1,9,7 };
	srand(time(0));
	for(int i =0; i<10; i++)
		v.push_back(rand() % 100);

	// TODO 정렬
	//BubbleSort(v);
	//SelectSort(v);
	//InsertSort(v);
	//HeapSort(v);
	//MergeSort(v, 0, v.size() - 1);

	//QuickSort1(v, 0, v.size() - 1);	   // [1]  1 0

	sort(v.begin(), v.end()); // ----
	// 더 효율적인 방법이 있다고. 
	// 연관 컨테이너 - 탐색	
	// 추가.logN <<<< 로딩. ?? 로딩하는 시간이 너무 오래걸려서 화가 너무난다. <<
	//                         실제 게임중에 렉이거려서 내 캐릭터가 죽었다.  <<
	// vector<>
	// 렉. ?.
	// 탐색 시간이 빠릅니다. logN.

	for (const auto& a : v)
	{
		cout << a << " ";
	}
}



