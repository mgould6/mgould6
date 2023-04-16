#include "Header.h";

using namespace std;

/*
	Iterative Implementation of DFS
	he non-recursive implementation of DFS is similar to the non-recursive implementation of BFS but differs from it in two ways:

It uses a stack instead of a queue.
The DFS should mark discovered only after popping the vertex, not before pushing it.
It uses a reverse iterator instead of an iterator to produce the same results as recursive DFS.
*/

//data structure to store a graph edge
struct Edge
{
	int dest, src;
};

//class to represent graph
class Graph
{
public:
	//vector of vectors to represent an adjacency list
	vector<vector<int>> adjList;

	//Graph constructor 
	Graph(vector<Edge> const& edges, int n)
	{
		//resize the vector to hold n elements of type vector<int>
		adjList.resize(n);

		//add edges to the undirected graph
		for (auto& edge : edges)
		{
			adjList[edge.src].push_back(edge.dest);
			adjList[edge.dest].push_back(edge.src);
		}
	}
};

//perform iterative DFS on graph starting from vertex v
void iterativeDFS(Graph const& graph, int v, vector<bool>& discovered)
{
	//create a stack used to do iterative DFS
	stack<int> stack;

	//push the source node into the stack
	stack.push(v);

	//loop till stack is empty
	while (!stack.empty())
	{
		//pop a vertex from the stack
		v = stack.top();
		stack.pop();

		//if the vertex is alread discovered 
		//ignore
		if (discovered[v])
		{
			continue;
		}

		//we will reach here if the popped vertex v is not discovered yet;
		//print v and process its undiscovered adjacent nodes into the stack
		discovered[v] = true;
		cout << v << " ";

		//do for every edge (v,u)
		// we are using reverse iterator (Why?)
		for (auto it = graph.adjList[v].rbegin(); it != graph.adjList[v].rend(); it++)
		{
			int u = *it;
			if (!discovered[u])
			{
				stack.push(u);
			}
		}
	}
}

int main()
{
	vector<Edge> edges =
	{
		// Notice that node 0 is unconnected
		{1, 2}, {1, 7}, {1, 8}, {2, 3}, {2, 6}, {3, 4},
		{3, 5}, {8, 9}, {8, 12}, {9, 10}, {9, 11}
		// {6, 9} introduces a cycle
	};

	//total number of nodes in the graph labelled from 0 to 12
	int n = 13;

	//build a graph from the given edges
	Graph graph(edges, n);

	//to keep track of whether a vertex is discovered or not
	vector<bool> discovered(n);

	//do iterative DFS traversal from all undiscovered nodes to 
	//cover all connected components of a graph
	for (int i = 0; i < n; i++)
	{
		if (discovered[i] == false)
		{
			iterativeDFS(graph, i, discovered);
		}
	}

	return 0;
}

