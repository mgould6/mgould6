#include "Header.h";

using namespace std;

/*
Flood Fill Algorithm - BFS

*/

// Below arrays detail all eight possible movements
int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

//check if it is possible to go to pixel (x,y) from the
//current pixel. the function returns false if the pixel
//has a different color or it's not a valid pixel
bool isSafe(vector<vector<char>> const& mat, int x, int y, char target)
{
    return (x >= 0 && x < mat.size()) && (y >= 0 && y < mat[0].size()) && mat[x][y] == target;
}

//flood fill using VFS

void floodFill(vector<vector<char>>& mat, int x, int y, char replacement)
{
    //base case
    if (mat.size() == 0)
    {
        return;
    }

    //create a queue and enqueue starting pixel
    queue<pair<int, int>> q;
    q.push({ x, y });

    //get the target color
    char target = mat[x][y];

    //target color is same as replacement
    if (target == replacement)
    {
        return;
    }

    //break when the queue becomes empty
    while (!q.empty())
    {
        //dequeue front node and process it
        pair<int, int> node = q.front();
        q.pop();

        //(x,y) represents the current pixel
        int x = node.first, y = node.second;

        //replace the current pixel color with that of replacement
        mat[x][y] = replacement;

        //process all eight adjacent pixels of the current pixel and
        //enqueue each valid pixel
        for (int k = 0; k < 8; k++)
        {
            //if the adjacent pixel at position (x + row[k], y + col[k]) is valid
            //and has the same color as the current pixel
            if (isSafe(mat, x + row[k], y + col[k], target))
            {
                //enque adjacent pixel
                q.push({ x + row[k], y + col[k] });
            }
        }
    }
}

//utility function to print a matrix
void printMatrix(vector<vector<char>> const& mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            cout << setw(3) << mat[i][j];
        }
        cout << endl;
    }
}

int main()
{

    // matrix showing portion of the screen having different colors
    vector<vector<char>> mat =
    {
        { 'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G' },
        { 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X' },
        { 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X' },
        { 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'G', 'G', 'X' },
        { 'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X' },
        { 'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X' },
        { 'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X' },
        { 'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X' },
        { 'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X' },
        { 'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
    };

    // start node
    int x = 3, y = 9;    // having target color `X`

    // replacement color
    char replacement = 'C';

    // replace the target color with a replacement color
    floodFill(mat, x, y, replacement);

    // print the colors after replacement
    printMatrix(mat);
    return 0;
}

/*
Flood fill (also known as seed fill) is an algorithm that determines the area connected to a given node in a multi-dimensional array.

It is used in the “bucket” fill tool of a paint program to fill connected, similarly colored areas with a different color and in games such as Go and Minesweeper for determining which pieces are cleared. When applied on an image to fill a particular bounded area with color, it is also known as boundary fill.


The flood fill algorithm takes three parameters: a start node, a target color, and a replacement color.

Consider the following matrix to the left – if the start node is (3, 9), target color is “BLACK” and replacement color is “GREY”, the algorithm looks for all nodes in the matrix that are connected to the start node by a path of the target color and changes them to the replacement color.


Flood Fill Algorithm

Note that each cell of the matrix represents one pixel.

Practice This Problem

Approach 1: (Using BFS)
A queue-based implementation using Breadth–first search (BFS) is shown below in pseudocode.

BFS (starting-pixel, replacement-color):
Create an empty queue.
Enqueue starting pixel and mark it as processed.
Loop till queue is empty

Dequeue the front node and process it.
Replace the color of the current pixel (popped node) with that of the replacement.
Process all eight adjacent pixels of the current pixel and enqueue each valid pixel that has the same color as that of the current pixel.
The algorithm can be implemented as follows in C++

The time complexity of the proposed solution is O(M × N) and requires O(M × N) extra space, where M and N are dimensions of the matrix.


*/