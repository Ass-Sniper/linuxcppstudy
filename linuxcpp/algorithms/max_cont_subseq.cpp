#include <iostream>
#include <vector>
#include <time.h>

/*
基本思路：
第一步：以输入数组为准，计算其任意的由连续元素组成的序列的和的集合
第二步：计算上述集合中的最大值
*/

/*
第一步：通过循环得到任意序列
第二步：动态调整当前最大值
*/

using namespace std;

typedef unsigned int uint;

// Cubic maximum contiguous subsequence sum algorithm.
// seqstart and seqEnd represent the actual best sequence.
// O(N*N*N)
template <class Comparable>
Comparable maxSubsequenceSum_Cubic(const vector<Comparable>& a, int & seqStart, int & seqEnd )
{
	int n = a.size();
	Comparable maxSum = 0;

	for ( int i = 0; i < n; i++ ) {

		for ( int j = i; j < n; j++) {

			Comparable thisSum = 0;

			for ( int k = i; k <= j; k++)
				thisSum += a[k];
	
			if ( thisSum > maxSum)
			{
				maxSum = thisSum;
				seqStart = i;
				seqEnd = j;
			}
		}
	}
	return maxSum;
}

// A quadratic maximum contiguous subsequence sum algorithm
// O(N*N)
// a[i] + a[i+1]  + ... + a[j-1] + a[j] = (a[i] + a[i+1] + ... + a[j-1]) + a[j]
template <class Comparable>
Comparable maxSubsequenceSum_Quadratic(const vector<Comparable>& a, int & seqStart, int & seqEnd )
{
	int n = a.size();
	Comparable maxSum = 0;

	for ( int i = 0; i < n; i++ ) {

		Comparable thisSum = 0;
		
		for ( int j = i; j < n; j++) {

			thisSum += a[j];
	
			if ( thisSum > maxSum)
			{
				maxSum = thisSum;
				seqStart = i;
				seqEnd = j;
			}
		}
	}
	return maxSum;
}

// A linear maximum contiguous subsequence sum algorithm
// O(N)
// a[i] + ... + a[j] = a[i] + a[i+1] + ... + a[p] + ... + a[j]
// if a[i] + ... + a[p] < 0; then a[i]~a[p] is skipped and a[p+1]~a[j] maybe become the result
template <class Comparable>
Comparable maxSubsequenceSum_Linear(const vector<Comparable>& a, int & seqStart, int & seqEnd )
{
	int n = a.size();
	Comparable thisSum = 0;
	Comparable maxSum = 0;

	for ( int i = 0, j = 0; j < n; j++ ) {

		thisSum += a[j];

		if ( thisSum > maxSum)
		{
			maxSum = thisSum;
			seqStart = i;
			seqEnd = j;
		} else if (thisSum < 0) {　//if current subsequence sum is negative, then a[i]~a[j] can never become the max subsequence
			i = j + 1;
			thisSum = 0;
		}
	}
	return maxSum;
}

template <class Comparable>
void printMaxContiguousSubseq(const vector<Comparable>& a, const int seqStart, const int seqEnd)
{
	cout<< "[";
	for (int i = seqStart; i <= seqEnd; ++i)
	{
		cout<< a[i];
		if(i < seqEnd)
			cout<< ",";
	}
	cout<< "]" <<endl;
}



int main(int argc, char const *argv[])
{
	int array[] = {-2, 11 , -4 , 13, -5, 2};

	int count = sizeof(array)/sizeof(array[0]);

	vector<int> sequence(array, array+count);

	int start = 0, end = 0 , maxSum = 0; 

    clock_t startTime,finishTime;
    double totaltime;

    startTime = clock();
    maxSum = maxSubsequenceSum_Cubic(sequence, start, end);
    finishTime = clock();
 	totaltime = (double)(finishTime-startTime)/CLOCKS_PER_SEC;
   	cout<< "Cubic solution execution time:"<< fixed << totaltime << "s" <<endl;
	cout<< "The Maximum Contiguous Subsequence Sum: " << maxSum <<endl;
	cout<< "startIndex: " << start << ";endIndex: " << end <<endl;
	printMaxContiguousSubseq(sequence, start, end);

	cout<< "------------------------------------------" <<endl;

    startTime = clock();
    maxSum = maxSubsequenceSum_Quadratic(sequence, start, end);
    finishTime = clock();
 	totaltime = (double)(finishTime-startTime)/CLOCKS_PER_SEC;
   	cout<< "Quadratic solution execution time:"<< fixed << totaltime << "s" <<endl;
	cout<< "The Maximum Contiguous Subsequence Sum: " << maxSum <<endl;
	cout<< "startIndex: " << start << ";endIndex: " << end <<endl;
	printMaxContiguousSubseq(sequence, start, end);

	cout<< "------------------------------------------" <<endl;

    startTime = clock();
    maxSum = maxSubsequenceSum_Linear(sequence, start, end);
    finishTime = clock();
 	totaltime = (double)(finishTime-startTime)/CLOCKS_PER_SEC;
   	cout<< "Linear solution execution time:"<< fixed << totaltime << "s" <<endl;
	cout<< "The Maximum Contiguous Subsequence Sum: " << maxSum <<endl;
	cout<< "startIndex: " << start << ";endIndex: " << end <<endl;
	printMaxContiguousSubseq(sequence, start, end);	

	return 0;
}
