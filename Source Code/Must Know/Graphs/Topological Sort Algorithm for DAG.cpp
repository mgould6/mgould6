#include "Header.h";

using namespace std;

/*
Topological Sort Algorithm for DAG
Google Translate Icon
Given a Directed Acyclic Graph (DAG), print it in topological order using topological sort algorithm. If the graph has more than one topological ordering, output any of them. Assume valid Directed Acyclic Graph (DAG).

A Topological sort or Topological ordering of a directed graph is a linear ordering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering. A topological ordering is possible if and only if the graph has no directed cycles, i.e. if the graph is DAG.


For example, consider the following graph:https://www.techiedelight.com/wp-content/uploads/2016/11/Topological-order-2.png

Topological Order – Step 2

The graph has many valid topological ordering of vertices like,

5   7   3   1   0   2   6   4
3   5   7   0   1   2   6   4
5   7   3   0   1   4   6   2
7   5   1   3   4   0   6   2
5   7   1   2   3   0   6   4
3   7   0   5   1   4   2   6
…
etc.
Note that for every directed edge u —> v, u comes before v in the ordering. https://www.techiedelight.com/wp-content/uploads/2016/11/Topological-order-1-768x348.png


Topological Order – Step 1

Practice This Problem

We can use Depth–first search (DFS) to implement topological sort algorithm. The idea is to order the vertices in order of their decreasing departure time of vertices in DFS, and we will get our desired topological sort.

How does it work?

We have already discussed the relationship between all four types of edges involved in the DFS in the previous post. Following is the relationship we have seen between the departure time for different types of edges involved in a DFS of the directed graph:

Tree edge (u, v): departure[u] > departure[v]
Back edge (u, v): departure[u] < departure[v]
Forward edge (u, v): departure[u] > departure[v]
Cross edge (u, v): departure[u] > departure[v]
As we can see that for a tree edge, forward edge, or cross edge (u, v), departure[u] is more than departure[v]. But only for the back edge, relationship departure[u] < departure[v] is true. So, it is guaranteed that if an edge (u, v) has departure[u] > departure[v], it’s not a back-edge.


We know that in a DAG, no back-edge is present. So if we order the vertices in order of their decreasing departure time, we will get the topological order of the graph (every edge going from left to right).

Types of edges involved in DFS and relation between them

https://www.techiedelight.com/wp-content/uploads/2016/11/Edges-Showing-Depature-Time.png

Following is the C++

The time complexity of the  implementation is O(V + E), where V and E are the total number of vertices and edges in the graph, respectively.


*/

//data structure to store an edge
struct Edge {
	int src, dest;
};

//class to store a graph
class Graph
{
public:

	//a vector of vectors to represent an adjacency
	vector<vector<int>> adjList;

	//graph constructor
	Graph(vector<Edge> const& edges, int n)
	{
		//resize the vector to hold n elements of vector<int>
		adjList.resize(n);

		//add edges to the direct graph
		for (auto& edge : edges)
		{
			adjList[edge.src].push_back(edge.dest);
		}
	}
};

//perform DFS on the graph and set the departure time of all vertices of the graph

void DFS(Graph& graph, int v, vector<bool>& discovered, vector<int>& departure, int& time)
{
	//mark the current node as discovered
	discovered[v] = true;

	//set the arrival time of vertex v
	time++;

	//do for every edge (v, u)
	for (int u : graph.adjList[v])
	{
		//if u is not yet discovered
		if (!discovered[u])
		{
			DFS(graph, u, discovered, departure, time);
		}
	}

	//ready to backtrack
	//set departure time of vertext v
	departure[time] = v;
	time++;
}

//function to perform topological sort on a given DAG
void doTopologicalSort(Graph& graph, int n)
{
	//departure[] stores the vertex number using departure time as an index
	vector<int> departure(2 * n, -1);

	/* If we had done it the other way around, i.e., fill the array
	   with departure time using vertex number as an index, we would
	   need to sort it later */

	   //to keep track of whether a vertex is discovered or not
	vector<bool> discovered(n);
	int time = 0;

	//perform DFS on all undiscovered vertices
	for (int i = 0; i < n; i++)
	{
		if (!discovered[i])
		{
			DFS(graph, i, discovered, departure, time);
		}
	}

	//print the vertices in order of their decreasing departure time in dfs i.e. topological order
	for (int i = 2 * n - 1; i >= 0; i--)
	{
		if (departure[i] != -1)
		{
			cout << departure[i] << " ";
		}
	}
}

int main()
{
	//vector of graph edges as per the above diagram
	vector<Edge> edges =
	{
		{0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}
	};

	int n = 8;

	//build a graph from the given edges
	Graph graph(edges, n);

	//perform topological sort
	doTopologicalSort(graph, n);

	return 0;
}

