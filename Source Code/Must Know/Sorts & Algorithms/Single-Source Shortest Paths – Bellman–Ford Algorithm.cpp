#include "Header.h";

using namespace std;

/*
Single-Source Shortest Paths – Bellman–Ford Algorithm
Google Translate Icon
Given a source vertex s from a set of vertices V in a weighted directed graph where its edge weights w(u, v) can be negative, find the shortest path weights d(s, v) from source s for all vertices v present in the graph. If the graph contains a negative-weight cycle, report it.

For example, consider the following graph: https://www.techiedelight.com/wp-content/uploads/2016/11/Bellman-Ford-CLRS-1.png

Bellman Ford Algorithm CLRS

Let source vertex = 0,

The distance of vertex 1 from vertex 0 is -1. Its path is [0 —> 1]
The distance of vertex 2 from vertex 0 is 2. Its path is [0 —> 1 —> 2]
The distance of vertex 3 from vertex 0 is -2. Its path is [0 —> 1 —> 4 —> 3]
The distance of vertex 4 from vertex 0 is 1. Its path is [0 —> 1 —> 4]
Practice This Problem

The idea is to use the Bellman–Ford algorithm to compute the shortest paths from a single source vertex to all the other vertices in a given weighted digraph. Bellman–Ford algorithm is slower than Dijkstra’s Algorithm, but it can handle negative weights edges in the graph, unlike Dijkstra’s.

If a graph contains a “negative cycle” (i.e., a cycle whose edges sum to a negative value) that is reachable from the source, then there is no shortest path. Any path that has a point on the negative cycle can be made cheaper by one more walk around the negative cycle. Bellman–Ford algorithm can easily detect any negative cycles in the graph.

The algorithm initializes the distance to the source to 0 and all other nodes to INFINITY. Then for all edges, if the distance to the destination can be shortened by taking the edge, the distance is updated to the new lower value. At each iteration i that the edges are scanned, the algorithm finds all shortest paths of at most length i edges. Since the longest possible path without a cycle can be V-1 edges, the edges must be scanned V-1 times to ensure that the shortest path has been found for all nodes. A final scan of all the edges is performed, and if any distance is updated, then a path of length |V| edges have been found, which can only occur if at least one negative cycle exists in the graph.


Following is the pseudocode for Bellman–Ford as per Wikipedia. The implementation takes a graph, represented as lists of vertices and edges, and fills distance[] and parent[] with the shortest path (least cost/path) information:
function BellmanFord(list vertices, list edges, vertex source, distance[], parent[])

// Step 1 – initialize the graph. In the beginning, all vertices weight of
// INFINITY and a null parent, except for the source, where the weight is 0

for each vertex v in vertices
    distance[v] = INFINITY
    parent[v] = NULL

distance[source] = 0
// Step 2 – relax edges repeatedly
    for i = 1 to V-1    // V – number of vertices
        for each edge (u, v) with weight w
            if (distance[u] + w) is less than distance[v]
                distance[v] = distance[u] + w
                parent[v] = u

// Step 3 – check for negative-weight cycles
for each edge (u, v) with weight w
    if (distance[u] + w) is less than distance[v]
        return “Graph contains a negative-weight cycle”

return distance[], parent[]
The following slideshow illustrates the working of the Bellman–Ford algorithm. The images are taken from MIT 6.046J/18.401J Introduction to Algorithms (Lecture 18 by Prof. Erik Demaine).
https://www.techiedelight.com/single-source-shortest-paths-bellman-ford-algorithm/
Bellman Ford Algorithm – Step 1

Bellman Ford Algorithm – Step 2

Bellman Ford Algorithm – Step 3

Bellman Ford Algorithm – Step 4

Bellman Ford Algorithm – Step 5

Bellman Ford Algorithm – Step 6

Bellman Ford Algorithm – Step 7

Bellman Ford Algorithm – Step 8

Bellman Ford Algorithm – Step 9

Bellman Ford Algorithm – Step 10

Bellman Ford Algorithm – Step 11

Bellman Ford Algorithm – Step 12

Bellman Ford Algorithm – Step 13

Bellman Ford Algorithm – Step 14

Bellman Ford Algorithm – Step 15

Bellman Ford Algorithm – Step 16

Bellman Ford Algorithm – Step 17

Bellman Ford Algorithm – Step 18

Bellman Ford Algorithm – Step 19

Bellman Ford Algorithm – Step 20

Bellman Ford Algorithm – Step 21

The algorithm can be implemented as follows in C++


The time complexity of the Bellman–Ford algorithm is O(V × E), where V and E are the total number of vertices and edges in the graph, respectively.


*/


//data structure to store an edge
struct Edge
{
    int src, dest, weight;
};

//recursive function to print the path of a given vertex from source to vertex
void printPath(vector<int> const& parent, int vertex, int source)
{
    if (vertex < 0)
    {
        return;
    }

    printPath(parent, parent[vertex], source);
    if (vertex != source)
    {
        cout << ", ";
    }
    cout << vertex;
}

//function to run the bellman ford algorithm from a given source
void bellmanFord(vector<Edge> const& edges, int source, int n)
{
    //distance[] and parent[] stores the shortest path (least cost/path)
    //information. initially all vertices except the source vertex
    //weight INFINITY and no parent

    vector<int> distance(n, INT_MAX);
    distance[source] = 0;

    vector<int> parent(n, -1);

    int u, v, w, k = n;

    //relaxation step (run V-1 times)
    while (--k)
    {
        for (Edge edge : edges)
        {
            //edge from u to v having weight w
            u = edge.src;
            v = edge.dest;
            w = edge.weight;

            //if the distance to destination v can be
            //shorted by taking edge (u,v)
            if (distance[u] != INT_MAX && distance[u] + w < distance[v])
            {
                //update distance to the new lower value
                distance[v] = distance[u] + w;

                //set v's parent as u
                parent[v] = u;
            }
        }
    }
    //run relaxation step once more for the n'th time to check for negative weight cycles
    for (Edge edge : edges)
    {
        //edge from u to v having weight w
        u = edge.src;
        v = edge.dest;
        w = edge.weight;

        //if distance to destination u can be shortened by taking edge (u,v)
        if (distance[u] != INT_MAX && distance[u] + w < distance[v])
        {
            cout << "Negative weight cycle is found!!";
            return;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i != source && distance[i] < INT_MAX)
        {
            cout << "The distance of vertex " << i << " from the source is " << setw(2) << distance[i] << ". Its path is [";
            printPath(parent, i, source);
            cout << "]" << endl;
        }
    }
}



int main()
{
    //vector of graph edges as per the above diagram
    vector<Edge> edges =
    {
        // (x, y, w) —> edge from `x` to `y` having weight `w`
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    //set the maximum number of nodes in the graph
    int n = 5;

    //run the bellman ford algoritm from every node
    for (int source = 0; source < n; source++)
    {
        bellmanFord(edges, source, n);
    }

    return 0;
}

