#include "Header.h";

using namespace std;

/*
	Undirected graph implementation
*/

//define the max number of vertices in the graph
#define N 6

//data structure to store a graph object
struct Graph
{
	//an array of pointers to Node to represent an adjacency lsit
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
	for (int i = 0; i < n; i++)
	{
		graph->head[i] = NULL;
	}

	//add edges to the directed graph one by one
	for (int i = 0; i < n; i++)
	{
		//get the source and destination vertex
		int src = edges[i].src;
		int dest = edges[i].dest;

		//1. allocate a new node of adjacency list from src to dest

		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = dest;

		//point new node to the current head
		newNode->next = graph->head[src];

		//point head pointer to the new node
		graph->head[src] = newNode;

		//2. allocate a new node of adjacency list from dest to src

		newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = src;

		//point new node to the current head
		newNode->next = graph->head[dest];

		//change head pointer to point to the new node
		graph->head[dest] = newNode;
	}

	return graph;
}

//function to print adjacency list representation of a graph
void printGraph(struct Graph* graph)
{
	for (int i = 0; i < N; i++)
	{
		//print current vertext and all its neighbors
		struct Node* ptr = graph->head[i];
		while (ptr != NULL)
		{
			printf("%d -> %d\t", i, ptr->dest);
			ptr = ptr->next;
		}
		printf("\n");
	}
}

//directed graph implementation in C


int main(void)
{
	//input array containing edges of the graph (as per the above diagram) https://www.techiedelight.com/wp-content/uploads/2016/11/Directed-Graph.png
	//(x,y) pair in the array represents an edge from x to y

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

