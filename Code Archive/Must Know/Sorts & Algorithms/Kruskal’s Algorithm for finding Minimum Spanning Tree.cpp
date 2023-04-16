#include "Header.h";

using namespace std;

///Kruskal’s Algorithm for finding Minimum Spanning Tree
/*
The time complexity of the above solution is O(n2), where n is the total number of vertices in the graph. The time complexity can be improved to O(n.log(n)) by using the optimized implementation of Union and Find operations.
*/

//data structure to store a graph edge
struct Edge
{
    int src, dest, weight;
};

//comparison object to be used to order the edges
struct compare
{
    bool operator()
        (Edge const& a, Edge const& b) const
    {
        return a.weight > b.weight;
    }
};

//a class to represet a disjoint set
class DisjointSet
{
    unordered_map<int, int> parent;

public:
    //perform makeset operation

    void makeSet(int n)
    {
        //create n disjoint sets (one for each vertex)
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    //find the root of the set in which element k belongs 
    int  Find(int k)
    {
        //if k is root
        if (parent[k] == k)
        {
            return k;
        }
        return Find(parent[k]);
    }


    //perform union of two subsets
    void Union(int a, int b)
    {
        //find that root of the sets in which elements 
        //x and y belongs
        int x = Find(a);
        int y = Find(b);

        parent[x] = y;
    }
};

//function to construct MST using kruskals algorith
vector<Edge> runKruskalAlgorithm(vector<Edge> edges, int n) //no ref no const
{
    //store the edges present in MST
    vector<Edge> MST;

    //initialize DisjointSet class
    DisjointSet ds;

    //create a singleton set for each element of the universe
    ds.makeSet(n);

    //sort edges by incresaing weight
    sort(edges.begin(), edges.end(), compare());

    //MST contains v-1 edges
    while (MST.size() != n - 1)
    {
        //consider the next edge with minimum weight from the graph
        Edge next_edge = edges.back();
        edges.pop_back();

        //find the root of the sets to which two endpoints
        //vertices of the next edge belongs
        int x = ds.Find(next_edge.src);
        int y = ds.Find(next_edge.dest);

        //if both endpoints have different parents they belong to 
        //different connected components and can be included in MST
        if (x != y)
        {
            MST.push_back(next_edge);
            ds.Union(x, y);
        }
    }
    return MST;
}

int main()
{
    //vector of graph edges as per the above diagram
    vector<Edge> edges =
    {
        // (u, v, w) triplet represent undirected edge from
        // vertex `u` to vertex `v` having weight `w`
{       0, 1, 7}, {1, 2, 8}, {0, 3, 5}, {1, 3, 9}, {1, 4, 7}, {2, 4, 5},
        {3, 4, 15}, {3, 5, 6}, {4, 5, 8}, {4, 6, 9}, {5, 6, 11}
    };

    //total number of nodes in te graph
    int n = 7;

    //construct graph
    vector<Edge> e = runKruskalAlgorithm(edges, n);

    for (Edge& edge : e)
    {
        cout << "(" << edge.src << ", " << edge.dest << ", "
            << edge.weight << ")" << endl;
    }

    return 0;
}

/*
Kruskal’s Algorithm for finding Minimum Spanning Tree
Given a connected and weighted undirected graph, construct a minimum spanning tree out of it using Kruskal’s Algorithm.

A Minimum Spanning Tree is a spanning tree of a connected, undirected graph. It connects all the vertices with minimal total weighting for its edges.

Kruskal’s Algorithm – Step 1

For example, consider the above graph. Its minimum spanning tree will be the following tree with exactly n-1 edges where n is the total number of vertices in the graph, and the sum of weights of edges is as minimum as possible:

Kruskal’s Algorithm

Practice This Problem


Prerequisite:

Union–Find Algorithm for cycle detection in a graph


We can use Kruskal’s Minimum Spanning Tree algorithm, a greedy algorithm to find a minimum spanning tree for a connected weighted graph. Kruskal’s Algorithm works by finding a subset of the edges from the given graph covering every vertex present in the graph such that they form a tree (called MST), and the sum of weights of edges is as minimum as possible.

Let G = (V, E) be the given graph. Initially, our MST contains only vertices of the given graph with no edges. In other words, initially, MST has V connected components, with each vertex acting as one connected component. The goal is to add minimum weight edges to our MST such that we are left with a single connected component that comprises all the graph’s vertices. Following is the complete algorithm:

sort all edges in graph G in order of their increasing weights;
repeat V-1 times    // as MST contains V-1 edges
{
    select the next edge with minimum weight from graph G;

    if (no cycle is formed by adding the edge in MST, i.e., the edge connects two
            different connected components in MST)
        add the edge to MST;
}
Let’s illustrate this by taking the example of the above graph. Initially, our MST consists of only the vertices of the given graph with no edges. We start by considering the smallest weighted edge 0–3 having weight 5. As no cycle is formed, include it in our MST.

Kruskal’s Algorithm – Step 2

We next consider the smallest weighted edge 2–4 also having weight 5. As no cycle is formed, include it in our MST.

Kruskal’s Algorithm – Step 3

We next consider the smallest weighted edge 3–5 having weight 6. As no cycle is formed, include it in our MST.

Kruskal’s Algorithm – Step 4

We next consider the smallest weighted edge 0–1 having weight 7. As no cycle is formed, include it in our MST.

Kruskal’s Algorithm – Step 5

We next consider the smallest weighted edge 1–4 also having weight 7. As no cycle is formed, include it in our MST.

Kruskal’s Algorithm – Step 6

We next consider the smallest weighted edge 5–4 having weight 8. But including this edge in MST will result in a cycle 0—1—4—5—3—0, so we discard it.

Kruskal’s Algorithm – Step 7

We next consider the smallest weighted edge 1–2 also having weight 8. But including this edge in MST will result in a cycle 1—2—4—1, so we discard it.

Kruskal’s Algorithm – Step 8

We next consider the smallest weighted edge 3–1 also having weight 9. But including this edge in MST will result in a cycle 0—1—3—0, so we discard it.

Kruskal’s Algorithm – Step 9

Finally, consider the next smallest weighted edge, 4–6, also weighting 9. As no cycle is formed, include it in our MST.
Kruskal’s Algorithm – Step 10

MST is now connected (containing V-1 edges). So, we discard all remaining edges.

Kruskal’s Algorithm – Step 11

Following is the pseudocode of Kruskal’s Algorithm as per Wikipedia. It uses a disjoint–set data structure.

KRUSKAL(graph G)

MST = {}

for each vertex v belonging G.V:
    MAKE-SET(v)

for each (u, v) in G.E ordered by weight(u, v), increasing:
    if FIND-SET(u) != FIND-SET(v):
        add {(u, v)} to set MST
        UNION(u, v)

return MST
Please note that if the graph is not connected, Kruskal’s Algorithm finds a Minimum Spanning Forest, a minimum spanning tree for each connected component of the graph.

The algorithm can be implemented as follows in C++
*/