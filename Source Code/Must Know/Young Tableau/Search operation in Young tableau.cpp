#include "Header.h";

using namespace std;

/*
Young Tableau | Insert, Search, Extract-Min, Delete, Replace
Google Translate Icon
An M × N Young tableau is an M × N matrix such that the entries of each row are sorted from left to right and the entries of each column are sorted from top to bottom. Some entries of a Young tableau may be infinity, which indicates an empty entry. Thus, a Young tableau can be used to hold n <= M*N finite numbers.

For example, the following matrix is a Young tableau:

Young tableau


In this post, we will see how to

Search an element in an M × N Young tableau in O(M + N) time.
Search operation in Young tableau
A naive solution would be to traverse the complete tableau to search for a given value. The problem with this approach is that it would require O(M × N) time for searching in an M × N Young tableau.

Can we do better?
The idea is to take advantage of the fact that a Young tableau is a row-wise and column-wise sorted matrix. We start from the tableau’s top-rightmost corner and compare the current element with the one we are looking for and accordingly move left or down:

If the current element is less than the key, increment the row index (move to the next row)
If the current element is more than the key, decrement the column index (move to the previous column)
If the current element is equal to the key, return true as we have found the element. If we end up in a row or column beyond the tableau boundary, terminate the search and return false.
The algorithm can be implemented as follows in C++

*/

// Utility function to search an element in a young tableau
bool search(vector<vector<int>>& tableau, int key)
{
    //base case 
    if (tableau.size() == 0)
    {
        return false;
    }

    // MxN young tableau
    int M = tableau.size();
    int N = tableau[0].size();

    // Start from the top rightmost cell of the tableau (0, N-1) cell
    int i = 0, j = N - 1;

    // Run till tableau boundary is reached
    while (i < M && j >= 0)
    {
        // If the current element is less than the key increment row index
        if (tableau[i][j] < key)
        {
            i++;
        }
        // If the current element is more than the key decrement the column index
        if (tableau[i][j] > key)
        {
            j--;
        }
        //if the current element is equal to the key
        else
        {
            return true;
        }
    }
    return false;

}

int main()
{
    vector<vector<int>> tableau =
    {
        { 10, 12, 15, 16 },
        { 11, 18, 20, 25 },
        { 23, 27, 30, 35 },
        { 34, 40, 44, 45 }
    };

    vector<int> keys = { 20, 23, 25, 29 };

    // do for each key
    for (int key : keys)
    {
        if (search(tableau, key)) {
            cout << "Key " << key << " found in tableau" << endl;
        }
    }

    return 0;

    return 0;
}

/*

*/