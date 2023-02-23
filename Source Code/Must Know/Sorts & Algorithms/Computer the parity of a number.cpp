#include "Header.h";

using namespace std;

/*
Compute the parity of a number using a lookup table
2. Using a Lookup Table
We can use a lookup table to find parity in constant time. An integer in C/C++ usually takes 4 bytes for storage. That means the maximum number it can store is 232-1. A lookup table for all 232-1 integers will be infeasible (Not to forget, we have negative numbers too). The trick is to create an 8–bit (1 byte) version of the table, then iterate over each byte in the integer to be checked and summing the table lookup results.

1 byte with all its bits set is 255 in decimal (11111111 in binary), and all bits unset is 0 in decimal (00000000 in binary). So, the lookup table should be of size 256 (0-255).


The following solution uses the macros to generate the lookup table. The lookup table will be generated at compile time by the preprocessor. The first and last few numbers of the sequence will be:

{ 0, 1, 1, 0, 1, 0, … , 0, 1, 0, 1, 1, 0 } as

The parity of 0 is 0
The parity of 1 is 1
The parity of 2 is 1
The parity of 3 is 0
The parity of 4 is 1
The parity of 5 is 0
……
……
The parity of 250 is 0
The parity of 251 is 1
The parity of 252 is 0
The parity of 253 is 1
The parity of 254 is 1
The parity of 255 is 0
Consider n = 1691315356 (In binary 01100100110011110110110010011100)

1. Split the 32–bit integer into 16–bit chunks:

0110010011001111 | 0110110010011100


2. Take their XOR:

0110010011001111  ^
0110110010011100
~~~~~~~~~~~~~~~~
0000100001010011


3. Split the 16–bit result into 8–bit chunks:

00001000 | 01010011


4. Take their XOR:

00001000  ^
01010011
~~~~~~~~
01011011
Now, 01011011 is 91 in decimal, and lookup[91] will return 1 (odd parity). The split and XOR operation happens in a single expression for each chunk in the following C++ solution:




*/
// Macros to generate the lookup table(at compile - time)
#define P2(n) n, n^1, n^1, n
#define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
#define FIND_PARITY P6(0), P6(1), P6(1), P6(0)
//compute parity of a number x using the lookup table

unsigned int lookup[256] = { FIND_PARITY };

//find parity of x
int findParity(int x)
{
	//print lookup table(parity of integer i)

		/*
	for (int i = 0; i < 256; i++) {
		cout << "The parity of " << i << " is " << lookup[i] << endl;
	}
	*/



	// Assuming 32–bit (4 bytes) integer, break the integer into
	// 16–bit chunks and take their XOR
	x ^= x >> 16;

	// Again split the 16–bit chunk into 8–bit chunks and take their XOR
	x ^= x >> 8;

	// Note mask used 0xff is 11111111 in binary
	return lookup[x & 0xff];
}

int main()
{
	int x = 17;

	cout << x; cout << " in binary is " << bitset<8>(x) << endl;

	if (findParity(x))
	{
		cout << x << " contains odd bits";

	}
	else
	{
		cout << x << " contains even bits";

	}
	return 0;
}

/*
Google Translate Icon
In this post, we will see how to compute the parity of a number using a lookup table. The parity is related to the total number of 1’s in the binary number.

The odd parity (encoded as 1) means an odd number of 1’s and even parity (encoded as 0) means an even number of 1’s. Parity bits are often used as a simple means of error detection as digital data is transmitted and received.

Practice This Problem


A naive solution would be to calculate parity by checking each bit of the given number one by one. The time taken is proportional to the total number of bits in the number. We can perform better by turning off the rightmost set bit of the number one by one and finding the parity. The time it takes is proportional to the total number of set bits. We have already discussed these solutions in this post. In this post, a few other interesting solutions are discussed.

1. Divide and Conquer
The idea is to calculate the parity of an integer by recursively dividing the 32–bit integer into two halves and take their XOR until only the 1 bit is left. Taking the XOR will cancel out set bits at the same position in two halves, and since parity will not be affected if we take out even set bits from it (why?), the problem is successfully reduced to half at each step.

For example, we initially split the 32–bit (4 bytes) integer into two 16–bit chunks and take their XOR. Then again, we split the 16–bit chunk into 8–bit chunks and take their XOR. Then 8–bit chunks further get divided into 4–bits chunks and so on… This process continues until only the 1 bit is left.


Following is the C++

Here’s an optimized version of the above solution that involves a smaller number of operations:

//compute parity of a number x using the lookup table
int findParity(int x)
{
	//recursively divide the 32 bit integer into two equal halves and take their xor until only 1 bit is left

	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;

	//return 1 if the last bit is set otherwise return 0
	return x & 1;
}

*/