#include "Header.h";

using namespace std;

/*
Single-Source Shortest Paths – Dijkstra’s Algorithm 

Dijkstra’s algorithm runs in O(E.log(V)) time like Prim’s algorithm. Here, E is the total number of edges, and V is the graph’s number of vertices.
*/

//data structure to store a graph edge
struct Edge
{
    int source, dest, weight;
};

//data structure to store a heap node
struct Node
{
    int vertext, weight;
};

//a class to represent a graph object
class Graph
{
public:
    // a vector of vectors of Edge to represent an adjacency list
    vector<vector<Edge>> adjList;

    //graph constructor
    Graph(vector<Edge> const& edges, int n)
    {
        // resize the vector to hold `n` elements of type vector<Edge>
        adjList.resize(n);

        // add edges to the directed graph
        for (Edge const& edge : edges)
        {
            // insert at the end
            adjList[edge.source].push_back(edge);
        }
    }
};

void printPath(vector<int> const& prev, int i, int source)
{
    if (i < 0)
    {
        return;
    }
    printPath(prev, prev[i], source);
    if (i != source)
    {
        cout << ", ";
    }
    cout << i;
}

//comparison to be used to order the heap
struct comp
{
    bool operator()(const Node& lhs, const Node& rhs) const
    {
        return lhs.weight > rhs.weight;
    }
};

//run Dijkstras algorithm on the given graph
void findShortestPaths(Graph const& graph, int source, int n)
{
    //create a min heap and push source node having distance 0
    priority_queue<Node, vector<Node>, comp> min_heap;
    min_heap.push({ source, 0 });

    //set initial distance from the source to v as infinity
    vector<int> dist(n, INT_MAX);

    //distance from the source to itself is zero
    dist[source] = 0;

    //boolean array to track vertices for which minimum
    //cost is already found
    vector<bool> done(n, false);
    done[source] = true;

    //stores predecessor of a vertext (to a print path)
    vector<int> prev(n, -1);

    //run till min heap is empty
    while (!min_heap.empty())
    {
        //remove and return the best vertex
        Node node = min_heap.top();
        min_heap.pop();

        //get the vertex number
        int u = node.vertext;

        //do for each neighbor v of u 
        for (auto i : graph.adjList[u])
        {
            int v = i.dest;
            int weight = i.weight;

            //relaxation step
            if (!done[v] && (dist[u] + weight) < dist[v])
            {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                min_heap.push({ v, dist[v] });
            }
        }

        //mark vertext u as done so it will not get picked up again
        done[u] = true;
    }
    for (int i = 0; i < n; i++)
    {
        if (i != source && dist[i] != INT_MAX)
        {
            cout << "Path (" << source << " —> " << i << "): Minimum cost = "
                << dist[i] << ", Route = [";
            printPath(prev, i, source);
            cout << "]" << endl;
        }
    }
}

int main()
{
    //initialize the edges as per the above diagram
    //(u, v, w) represent edge from vertex u to vertext v having weight w 
    vector<Edge> edges =
    {
        {0, 1, 10}, {0, 4, 3}, {1, 2, 2}, {1, 4, 4}, {2, 3, 9},
        {3, 2, 7}, {4, 1, 1}, {4, 2, 8}, {4, 3, 2}
    };

    //total number of nodes in the graph
    int n = 5;

    //construct graph 
    Graph graph(edges, n);

    //run dijkstras algorithm from every node
    for (int source = 0; source < n; source++)
    {
        findShortestPaths(graph, source, n);
    }

	return 0;
}

/*
Single-Source Shortest Paths – Dijkstra’s Algorithm
Given a source vertex s from a set of vertices V in a weighted digraph where all its edge weights w(u, v) are non-negative, find the shortest path weights d(s, v) from source s for all vertices v present in the graph.

For example,

Vertex	Minimum Cost	Route
A —> B	4	A —> E —> B
A —> C	6	A —> E —> B —> C
A —> D	5	A —> E —> D
A —> E	3	A —> E
Dijkstra’s Algorithm


Practice This Problem

We know that the Breadth–first search (BFS) can be used to find the shortest path in an unweighted graph or even in a weighted graph having the same cost of all its edges. But if edges in the graph are weighted with different costs, then BFS generalizes to uniform-cost search. Instead of expanding nodes to their depth from the root, uniform-cost search expands the nodes in order of their cost from the root. A variant of this algorithm is known as Dijkstra’s algorithm.


Dijkstra’s Algorithm is an algorithm for finding the shortest paths between nodes in a graph. For a given source node in the graph, the algorithm finds the shortest path between that node and every other node. It can also be used for finding the shortest paths from a single node to a single destination node by stopping the algorithm once the fastest route to the destination node has been determined.

Dijkstra’s Algorithm is based on the principle of relaxation, in which more accurate values gradually replace an approximation to the correct distance until the shortest distance is reached. The approximate distance to each vertex is always an overestimate of the true distance and is replaced by the minimum of its old value with the length of a newly found path. It uses a priority queue to greedily select the closest vertex that has not yet been processed and performs this relaxation process on all of its outgoing edges.


Following is pseudocode for Dijkstra’s Algorithm as per Wikipedia.

function Dijkstra(Graph, source)

    dist[source] = 0    // Initialization
    create vertex set Q

    for each vertex v in Graph
    {
        if v != source
        {
            dist[v] = INFINITY        // Unknown distance from source to v
            prev[v] = UNDEFINED       // Predecessor of v
        }
        Q.add_with_priority(v, dist[v])
    }
    while Q is not empty
    {
        u = Q.extract_min()           // Remove minimum
        for each neighbor v of u that is still in Q
        {
            alt = dist[u] + length(u, v)
            if alt < dist[v]
            {
                dist[v] = alt
                prev[v] = u
                Q.decrease_priority(v, alt)
            }
        }
    }
    return dist[], prev[]
For instance, consider the following graph. We will start with vertex A, So vertex A has a distance 0, and the remaining vertices have an undefined (infinite) distance from the source. Let S be the set of vertices whose shortest path distances from the source are already calculated.

Dijkstra’s Algorithm: Step 1

Initially, S contains the source vertex. S = {A}.

We start from source vertex A and start relaxing A's neighbors. Since vertex B can be reached from a direct edge from vertex A, update its distance to 10 (weight of edge A–B). Similarly, we can reach vertex E through a direct edge from A, so we update its distance from INFINITY to 3.

Dijkstra’s Algorithm: Step 2

After processing all outgoing edges of A, we next consider a vertex having minimum distance. B has a distance of 10, E has distance 3, and all remaining vertices have distance INFINITY. So, we choose E and push it into set S. Now our set becomes S = {A, E}. Next, we relax with E's neighbors. E has 2 neighbors B and C. We have already found one route to vertex B through vertex A having cost 10. But if we visit a vertex B through vertex E, we are getting an even cheaper route, i.e., (cost of edge A–E + cost of edge E–B) = 3 + 1 = 4 < 10 (cost of edge A–B).


Dijkstra’s Algorithm: Step 3

We repeat the process till we have processed all the vertices, i.e., Set S becomes full.

Dijkstra’s Algorithm: Step 4

Dijkstra’s Algorithm: Step 5

Dijkstra’s Algorithm: Step 6

Dijkstra’s Algorithm: Step 7

The algorithm can be implemented as follows in C++
*/