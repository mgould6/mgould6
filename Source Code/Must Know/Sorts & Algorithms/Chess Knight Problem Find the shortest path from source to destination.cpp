#include "Header.h";

using namespace std;

/*
Chess Knight Problem | Find the shortest path from source to destination
Given a chessboard, find the shortest distance (minimum number of steps) taken by a knight to reach a given destination from a given source.

For example,

Input:

N = 8 (8 × 8 board)
Source = (7, 0)
Destination = (0, 7)

Output: Minimum number of steps required is 6
The knight’s movement is illustrated in the following figure:

Chess Knight Problem


Practice This Problem


The idea is to use Breadth–first search (BFS) as it is the shortest path problem. Following is the complete algorithm:

Create an empty queue and enqueue the source cell having a distance of 0 from the source (itself).
Loop till queue is empty:
Dequeue next unvisited node.
If the popped node is the destination node, return its distance.
Otherwise, we mark the current node as visited. For each of eight possible movements for a knight, enqueue each valid movement with +1 distance (minimum distance of a given node from the source is one more than the minimum distance of parent from source).

A knight can move in eight possible directions from a given cell, as illustrated in the following figure:


Knight Movements


We can find all the possible locations the knight can move to from the given location by using the array that stores the relative position of knight movement from any location. For example, if the current location is (x, y), we can move to (x + row[k], y + col[k]) for 0 <= k <= 7 using the following array:

row[] = [ 2, 2, -2, -2, 1, 1, -1, -1 ]
col[] = [ -1, 1, 1, -1, 2, -2, 2, -2 ]
So, from position (x, y) knight’s can move to:

(x + 2, y – 1)
(x + 2, y + 1)
(x – 2, y + 1)
(x – 2, y – 1)
(x + 1, y + 2)
(x + 1, y – 2)
(x – 1, y + 2)
(x – 1, y – 2)
Note that in BFS, all cells having the shortest path as 1 are visited first, followed by their adjacent cells having the shortest path as 1 + 1 = 2 and so on… so if we reach any node in BFS, its shortest path = shortest path of parent + 1. So, the destination cell’s first occurrence gives us the result, and we can stop our search there. The shortest path cannot exist from some other cell for which we haven’t reached the given node yet. If any such path were possible, we would have already explored it.

The algorithm can be implemented as follows in C++

The time complexity of the proposed solution is O(M × N) and requires O(M × N) extra space, where M and N are dimensions of the matrix.


Exercise: Extend the solution to print the paths as well.


*/

//below arrays detail all eight possible movements for a knight
int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

//check if (x,y) is valid chessboard coordinates
//note that a knight cannot go out of the chess board

bool isValid(int x, int y, int N)
{
    return (x >= 0 && x < N) && (y >= 0 && y < N);
}

// A queue node used in BFS
struct Node
{
    //(x,y) represents chessboard coordinates
    //dist represents its minimum distance from the source
    int x, y, dist;

    //node constructor
    Node(int x, int y, int dist = 0) : x(x), y(y), dist(dist) {}

    //as we are using struct as a key in a std:;set
    //we need to overload < operator 
    //alternatively we can use std::pair<int, int> as a key
    //to store the matrix coordinates in the set 
    bool operator<(const Node& o) const
    {
        return x < o.x || (x == o.x && y < o.y);
    }
};

//find the minimum number of steps taken by the knight
//from the source to reach the destination using BFS
int findShortestDistance(int N, Node src, Node dest)
{
    //set to check if the atrix cell is visited before or not
    set<Node> visited;

    //create a queue and enqueue the first node
    queue<Node> q;
    q.push(src);

    //loop till queue is empty
    while (!q.empty())
    {
        //dequeuefront node and process it
        Node node = q.front();
        q.pop();

        int x = node.x;
        int y = node.y;
        int dist = node.dist;

        //if the destination is reached return distance
        if (x == dest.x && y == dest.y)
        {
            return dist;
        }

        //skip if the location is visited before
        if (!visited.count(node))
        {
            //mark the current node as visited
            visited.insert(node);

            //check for all eight possible movements for a knight 
            // and enqueue each valid movement
            for (int i = 0; i < 8; i++)
            {
                //get the knights valid position from the current position on
                //the chessboard and enqueue it with +1 distance
                int x1 = x + row[i];
                int y1 = y + col[i];

                if (isValid(x1, y1, N))
                {
                    q.push({ x1, y1, dist + 1 });
                }
            }
        }
    }
    return INT_MAX;
}


int main()
{
    // N x N matrix
    int N = 8;

    // source coordinates
    Node src = { 0, 7 };

    // destination coordinates
    Node dest = { 7, 0 };

    cout << "The minimum number of steps required is " <<
        findShortestDistance(N, src, dest);

    return 0;
}



/*

*/