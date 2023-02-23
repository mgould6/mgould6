#include "Header.h";

using namespace std;

/*
Rearrange array such that `A[A[i]]` is set to `i` for every element `A[i]`
Google Translate Icon
Given an unsorted integer array A of size n, whose elements lie in the range 0 to n-1, rearrange the array such that A[A[i]] is set to i for every array element A[i]. Do this in linear time and without using any extra constant space.



 A simple solution is to create an auxiliary array of size n, and for each element A[i] of the input array, set a value i at index A[i] in the auxiliary array. This approach is demonstrated below in C
 The time complexity of the above solution is O(n) and requires O(n) extra space, where n is the size of the input.


The above solution uses extra space that violates the problem constraints. We can solve this problem without using any extra space by taking advantage of the fact that array elements lie in range 0 to n-1. For each element A[i] present in the array, increment value present at index A[i] % n by i � n. Finally, traverse the modified array and set A[i] = A[i] / n. For example, consider array {1, 3, 4, 2, 0}. After incrementing value present at index A[i] % n for each element A[i] by i � n, the array becomes:

For example,

Input:  {1, 3, 4, 2, 0}
Output: {4, 0, 3, 1, 2}

Explanation:

A[0] = 1, A[1] becomes 0
A[1] = 3, A[3] becomes 1
A[2] = 4, A[4] becomes 2
A[3] = 2, A[2] becomes 3
A[4] = 0, A[0] becomes 4
Practice This Problem

{1 + 5 � 4, 3, 4 + 5 � 3, 2 + 5 � 1, 0 + 5 � 2} = {21, 3, 19, 7, 10}.

Now if we take A[i] / n for each index i, we get {4, 0, 3, 1, 2}. Following is the C, Java, and Python implementation based on this idea:
The time complexity of the above solution is O(n) and doesn�t require any extra space.



/////alternative solution in one pass

#include <stdio.h>

// Idx:  0  1  2  3  4
// A = { 1, 3, 4, 2, 0 }
// start: jmpIdx = 1, idxToWrite = 0
// pass 1: tmp = A[1] = 3, A[1] = 0, idxToWrite = 1, jmpIdx = 3
// Idx:  0  1  2  3  4
// A = { 1, 0, 4, 2, 0 }
// pass 2: tmp = A[3] = 2, A[3] = 1, idxToWrite = 3, jmpIdx = 2
// Idx:  0  1  2  3  4
// A = { 1, 0, 4, 1, 0 }
// pass 3: tmp = A[2] = 4, A[2] = 3, idxToWrite = 2, jmpIdx = 4
// Idx:  0  1  2  3  4
// A = { 1, 0, 3, 1, 0 }
// pass 4: tmp = A[4] = 0, A[4] = 2, idxToWrite = 4, jmpIdx = 0
// Idx:  0  1  2  3  4
// A = { 1, 0, 3, 1, 2 }
// pass 5: tmp = A[0] = 1, A[0] = 4, idxToWrite = 0, jmpIdx = 1
// Idx:  0  1  2  3  4
// A = { 4, 0, 3, 1, 2 }
void rearrange(int A[], int n) {
	for (int i = 0, jmpIdx = A[0], idxToWrite = 0; i < n; i++) {
		int tmp = A[jmpIdx];
		A[jmpIdx] = idxToWrite;
		idxToWrite = jmpIdx;
		jmpIdx = tmp;
	}
}

*/

void rearrange(int A[], int n)
{
	//for each element A[i] increment value present at index
	//(A[i] % n) by ixn
	for (int i = 0; i < n; i++)
	{
		A[A[i] % n] += i * n;
	}
	//traverse the modified array and set A[i] = A[i]/n;
	for (int i = 0; i < n; i++)
	{
		A[i] = A[i] / n;
	}
}


int main()
{
	int A[] = { 1,3,4,2,0 };
	int n = sizeof(A) / sizeof(A[0]);

	rearrange(A, n);

	for (int i = 0; i < n; i++)
	{
		printf("%d", A[i]);
	}

	return 0;
}

/*
* 
 A simple solution is to create an auxiliary array of size n, and for each element A[i] of the input array, set a value i at index A[i] in the auxiliary array. This approach is demonstrated below in C
void rearrange(int A[], int n)
{

	//create an auxiliary array of size n
	int* aux = new int[n];
	 
	//for each element A[i] of the input array, set
	//value i at index A[i] in auxiliary array
	for (int i = 0; i < n; i++)
	{
		aux[A[i]] = i;
	}

	//copy auxiliary array elements back to the given array
	for (int i = 0; i < n; i++)
	{
		A[i] = aux[i];
	}
}
*/