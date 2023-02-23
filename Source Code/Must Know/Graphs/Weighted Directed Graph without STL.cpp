#include "Header.h";

using namespace std;

/*
Weighted Directed Graph implementation in C++ without STL

We know that in a weighted graph, every edge will have a weight or cost associated with it, as shown below:

Weighted Directed Graph
https://www.techiedelight.com/wp-content/uploads/2016/11/Weighted-Directed-Graph.png


Following is the C++ implementation of a directed weighted graph. The implementation is similar to the above implementation of unweighted graphs, except we will also store every edge’s weight in the adjacency list.


*/



//data structure for node
struct Node
{
	int val, cost;
	Node* next;
};

//data structure for edges
struct Edge {
	int src, dest, weight;
};

//class for graph
class Graph
{
	//function to allocate a new node for the adjacency list
	Node* getAdjListNode(int value, int weight, Node* head)
	{
		Node* newNode = new Node;
		newNode->val = value;
		newNode->cost = weight;

		//point new node to the current head
		newNode->next = head;

		return newNode;
	}

	int N; //total number of nodes in the graph

public:

	//array of pointers to Node to represent the adjacency list
	Node** head;

	//graph constructor
	Graph(Edge edges[], int n, int N)
	{
		//allocate memory
		head = new Node * [N]();
		this->N = N;

		//initialize head pointer for all vertices
		for (int i = 0; i < N; i++)
		{
			int src = edges[i].src;
			int dest = edges[i].dest;
			int weight = edges[i].weight;

			//insert at the beginning
			Node* newNode = getAdjListNode(dest, weight, head[src]);

			//point head pointer to the new node
			head[src] = newNode;

			//uncomment the following code for undirected graph


			/*
			newNode = getAdjListNode(src, weight, head[dest]);

			//change head pointer to point to the new node

			head[dest] = newNode;

			*/


		}
	}

	//destructor 
	~Graph()
	{
		for (int i = 0; i < N; i++)
		{
			delete[] head[i];
		}

		delete[] head;
	}
};

//function to print all neighboring vertices of a given vertex
void printList(Node* ptr, int i)
{
	while (ptr != nullptr)
	{
		cout << "(" << i << ", " << ptr->val << ", " << ptr->cost << ") ";
		ptr = ptr->next;
	}
	cout << endl;
}


//graph implementation in c++ without using STL
int main()
{

	//an array of graph edges as per the above diagram

	Edge edges[] =
	{
		// (x, y, w) —> edge from `x` to `y` having weight `w`
		{0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {4, 5, 1}, {5, 4, 3}
	};

	int N = 6;

	//calculate the total number of edges
	int n = sizeof(edges) / sizeof(edges[0]);

	//construct graph
	Graph graph(edges, n, N);

	//print adjacency list representation of a graph
	for (int i = 0; i < N; i++)
	{
		//print all neighboring vertices of a vertex i
		printList(graph.head[i], i);
	}
	return 0;
}

