#include "Header.h";

using namespace std;

/*
Generate numbers from 1 to 7 with equal probability using a specified function
Write an algorithm to generate numbers from 1 to 7 with equal probability using a specified function that produces random numbers between 1 and 5.

Practice This Problem

Suppose the specified function is random(), which generates random numbers from 1 to 5 with equal probability. The idea is to use the expression 5 × (random() - 1) + random() which uniformly produces random numbers in the range [1–25]. So if we exclude the possibility of the random number being one among [8–25] by repeating the procedure, we are left with numbers between 1 and 7 having equivalent probability.

How this works?

Since random() returns random numbers from 1 to 5 with equal probability, R = 5 × (random() - 1) can be any of 0, 5, 10, 15 or 20. Now for the second random() call, let’s explore all possibilities:

If R = 0, R + random() can be any of 1, 2, 3, 4, 5
If R = 5, R + random() can be any of 6, 7, 8, 9, 10
If R = 10, R + random() can be any of 11, 12, 13, 14, 15
If R = 15, R + random() can be any of 15, 16, 17, 18, 19, 20
If R = 20, R + random() can be any of 21, 22, 23, 24, 25
So, the expression uniformly distributes the numbers in the range [1–25]. Following is the C

To minimize the total number of calls to the random() function, stop the while loop at r <= 21 and use the modulo operator, as shown below:

int generate()
{
    int r;
    do {
        r = 5 * (random() - 1) + random();
    } while (r > 21);

    return (r % 7) + 1;
}

*/

//function to generate a random number from 1 to 5 with equal probability
int getRandom()
{
    return (rand() % 5) + 1;
}

//function to generate a random numbr from 1 to 7 with equal probability
//by using the specified function 
int generate()
{
    int r;
    do {
        r = 5 * (getRandom() - 1) + getRandom();
    } while (r > 21);

    return (r % 7) + 1;
}

int main()
{
    // initialize srand with a distinctive value
    srand(time(NULL));

    // count array to validate the results
    int count[8];
    memset(count, 0, sizeof count);

    // make 1000000 calls to the `generate()` function and store the results
    for (int i = 1; i <= 1000000; i++)
    {
        int val = generate();
        count[val]++;
    }

    // print the results
    for (int i = 1; i <= 7; i++) {
        printf("%d ~ %0.2f%\n", i, count[i] / 10000.0);
    }


    return 0;
}

/*

*/