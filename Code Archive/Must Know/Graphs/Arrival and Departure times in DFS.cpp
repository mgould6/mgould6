#include <iostream>
#include <vector>
using namespace std;


/*

Arrival and departure time of vertices in DFS
Google Translate Icon
Given a graph, find the arrival and departure time of its vertices in DFS. The arrival time is the time at which the vertex was explored for the first time in the DFS, and departure time is the time at which we have explored all the neighbors of the vertex, and we are ready to backtrack.

The following directed graph has two connected components. The right-hand side shows the arrival and departure time of vertices when DFS starts from vertex 0.


Arrival and Departure time of Vertices in DFS


The idea is to run Depth–first search (DFS). Before exploring any adjacent nodes of any vertex in DFS, note the vertex’s arrival time. After exploring all adjacent nodes of the vertex, note its departure time. After the DFS call is over (i.e., all the graph vertices are discovered), print the vertices’ arrival and departure time.

Please note that the arrival and departure time of vertices may vary depending upon the insertion order of edges in the graph and starting node of DFS. Following is the implementation in C++, Java, and Python based on the above idea:



*/
// Data structure to store a graph edge
struct Edge {
    int src, dest;
};

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    vector<vector<int>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const& edges, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        adjList.resize(n);

        // add edges to the directed graph
        for (auto& edge : edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};

// Function to perform DFS traversal on the graph on a graph
void DFS(Graph const& graph, int v, vector<bool>& discovered,
    vector<int>& arrival, vector<int>& departure, int& time)
{
    // set the arrival time of vertex `v`
    arrival[v] = ++time;

    // mark vertex as discovered
    discovered[v] = true;

    for (int i : graph.adjList[v])
    {
        if (!discovered[i]) {
            DFS(graph, i, discovered, arrival, departure, time);
        }
    }

    // set departure time of vertex `v`
    departure[v] = ++time;
}

int main()
{
    // vector of graph edges as per the above diagram
    vector<Edge> edges = {
        {0, 1}, {0, 2}, {2, 3}, {2, 4}, {3, 1}, {3, 5}, {4, 5}, {6, 7}
    };

    // total number of nodes in the graph (labelled from 0 to 7)
    int n = 8;

    // build a graph from the given edges
    Graph graph(edges, n);

    // vector to store the arrival time of vertex
    vector<int> arrival(n);

    // vector to store the departure time of vertex
    vector<int> departure(n);

    // mark all the vertices as not discovered
    vector<bool> discovered(n);
    int time = -1;

    // Perform DFS traversal from all undiscovered nodes to
    // cover all unconnected components of a graph
    for (int i = 0; i < n; i++)
    {
        if (!discovered[i]) {
            DFS(graph, i, discovered, arrival, departure, time);
        }
    }

    // print arrival and departure time of each vertex in DFS
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << " (" << arrival[i] << ", " << departure[i] << ")\n";
    }

    return 0;
}