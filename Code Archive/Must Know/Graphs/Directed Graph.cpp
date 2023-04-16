#include "Header.h";

using namespace std;

/*






Directed Graph Implementation
This post will cover graph data structure implementation in C using an adjacency list. The post will cover both weighted and unweighted implementation of directed and undirected graphs.

In the graph’s adjacency list representation, each vertex in the graph is associated with the collection of its neighboring vertices or edges, i.e., every vertex stores a list of adjacent vertices.


Following is the C implementation of a directed graph using an adjacency list:

*/

//define the maximum number of vertices in the graph
#define N 6

//data structure to store a graph object
struct Graph
{
	//an array of pointers to node to represent an adjacency list
	struct Node* head[N];
};

//data structure to store adjacency list nodes of the graph
struct Node
{
	int dest;
	struct Node* next;
};

//data structure to store a graph edge
struct Edge
{
	int src, dest;
};

//function to create an adjacency list from specified edges
struct Graph* createGraph(struct Edge edges[], int n)
{
	//allocate storage for the graph data structure
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

	//initialize head pointer for all vertices
	for (int i = 0; i < N; i++)
	{
		graph->head[i] = NULL;
	}

	//add edges to the directed graph one by one
	for (int i = 0; i < n; i++)
	{
		//get the source and destination vertex
		int src = edges[i].src;
		int dest = edges[i].dest;

		//allocate a new node of adjaccency list from src to dest
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = dest;

		//point new node to the current head
		newNode->next = graph->head[src];

		//point head pointer to the new node
		graph->head[src] = newNode;
	}

	return graph;
}

void printGraph(struct Graph* graph)
{
	for (int i = 0; i < N; i++)
	{
		//print current vertext and all its neighbors
		struct Node* ptr = graph->head[i];
		while (ptr != nullptr)
		{
			printf("(%d -> %d)\t", i, ptr->dest);
			ptr = ptr->next;
		}
		printf("\n");

	}
}

int main()
{
	//input array containing edges of the graph (as per the  diagram https://www.techiedelight.com/wp-content/uploads/2016/11/Directed-Graph.png)
	struct Edge edges[] =
	{
		{0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
	};

	//calculate the total number of edges
	int n = sizeof(edges) / sizeof(edges[0]);

	//construct a graph from the given edges
	struct Graph* graph = createGraph(edges, n);

	//function to print adjacency list representation of a graph
	printGraph(graph);

	return 0;
}

