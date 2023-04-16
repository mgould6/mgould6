#include "Header.h";

using namespace std;

/*
Shortest path in a maze – Lee Algorithm

Given a maze in the form of the binary rectangular matrix, find the shortest path’s length in a maze from a given source to a given destination.

The path can only be constructed out of cells having value 1, and at any given moment, we can only move one step in one of the four directions. The valid moves are:

Go Top: (x, y) ——> (x – 1, y)
Go Left: (x, y) ——> (x, y – 1)
Go Down: (x, y) ——> (x + 1, y)
Go Right: (x, y) ——> (x, y + 1)
For example, consider the following binary matrix. If source = (0, 0) and destination = (7, 5), the shortest path from source to destination has length 12.

 [ 1  1  1  1  1  0  0  1  1  1 ]
 [ 0  1  1  1  1  1  0  1  0  1 ]
 [ 0  0  1  0  1  1  1  0  0  1 ]
 [ 1  0  1  1  1  0  1  1  0  1 ]
 [ 0  0  0  1  0  0  0  1  0  1 ]
 [ 1  0  1  1  1  0  0  1  1  0 ]
 [ 0  0  0  0  1  0  0  1  0  1 ]
 [ 0  1  1  1  1  1  1  1  0  0 ]
 [ 1  1  1  1  1  0  0  1  1  1 ]
 [ 0  0  1  0  0  1  1  0  0  1 ]
Practice This Problem

We have already discussed a backtracking solution in the previous post. The time complexity of the backtracking solution will be higher since all paths need to be traveled. However, since it is the shortest path problem, Breadth–first search (BFS) would be an ideal choice.


The Lee algorithm is one possible solution for maze routing problems based on Breadth–first search. It always gives an optimal solution, if one exists, but is slow and requires considerable memory. Following is the complete algorithm:

Create an empty queue and enqueue the source cell having a distance 0 from the source (itself) and mark it as visited.
Loop till queue is empty.
Dequeue the front node.
If the popped node is the destination node, then return its distance.
Otherwise, for each of four adjacent cells of the current cell, enqueue each valid cell with +1 distance and mark them as visited.
If all the queue nodes are processed, and the destination is not reached, then return false.
Note that in BFS, all cells having the shortest path as 1 are visited first, followed by their adjacent cells having the shortest path as 1 + 1 = 2 and so on… So if we reach any node in BFS, its shortest path is one more than the shortest path of the parent. So, the destination cell’s first occurrence gives us the result, and we can stop our search there. It is impossible that the shortest path exists from some other cell for which we haven’t reached the given node yet. If any such path were possible, we would have already explored it.

Following is the C+++


The time complexity of the proposed solution is O(M × N) and requires O(M × N) extra space, where M and N are dimensions of the matrix.


*/

//a queue node
struct Node
{
	//(x,y) represents matrix cell coordinates and
	//dist represents their minimum distance from the source
	int x, y, dist;
};

//below arrays detail all four possible movements from a cell
int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };

//function to check if it is possible to go to position (row, col)
//from the current position. the function returns false if (row, col)
//is not a valid position or has a value 0 or already visited 
bool isValid(vector<vector<int>> const& mat, vector<vector<bool>>& visited, int row, int col)
{
	return (row >= 0 && row < mat.size()) && (col >= 0 && col < mat[0].size()) && mat[row][col] && !visited[row][col];
}

//find the shortest possible route in a matrix mat from source 
//cell (i, j) to destination cell (x, y)
int findShortestPathLength(vector<vector<int>> const& mat, pair<int, int>& src, pair<int, int>& dest)
{
	//base case: invalid input
	if (mat.size() == 0 || mat[src.first][src.second] == 0 || mat[dest.first][dest.second] == 0)
	{
		return -1;
	}

	// m x n matrix
	int M = mat.size();
	int N = mat[0].size();

	//construct a m x n matrix to keep track of visited cells
	vector<vector<bool>> visited;
	visited.resize(M, vector<bool>(N));

	//create an empty queue
	queue<Node> q;

	//get source cell (i, j)
	int i = src.first;
	int j = src.second;

	//mark the source cell as visited and enqueue the source node
	visited[i][j] = true;
	q.push({ i, j, 0 });

	//stores length of the longest path from source to destination
	int min_dist = INT_MAX;

	//loop till queue is empty
	while (!q.empty())
	{
		//dequeue front node and process it
		Node node = q.front();
		q.pop();

		//(i,j) represents a current cell and dist stores its
		//minimum distance from the source
		int i = node.x, j = node.y, dist = node.dist;

		//if the destination is found update min_dist and stop
		if (i == dest.first && j == dest.second)
		{
			min_dist = dist;
			break;
		}

		//check for all four possible movements from the current cell and enqueue each valid movement
		for (int k = 0; k < 4; k++)
		{
			//check if it is possible to go to position
			//(i + row[k, j + col[k) from current position
			if (isValid(mat, visited, i + row[k], j + col[k]))
			{
				//mark next cell as visited and enqueue it
				visited[i + row[k]][j + col[k]] = true;
				q.push({ i + row[k], j + col[k], dist + 1 });
			}
		}
	}

	if (min_dist != INT_MAX) {
		return min_dist;
	}
	return -1;
}


int main()
{
	vector<vector<int>> mat =
	{
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
	};

	pair<int, int> src = make_pair(0, 0);
	pair<int, int> dest = make_pair(7, 5);

	int min_dist = findShortestPathLength(mat, src, dest);
	if (min_dist != -1)
	{
		cout << "the shortest path from source to destination has length " << min_dist;
	}
	else
	{
		cout << "destination cannot be reached from a given source";
	}

	return 0;
}

/*

*/