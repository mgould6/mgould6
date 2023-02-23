#include "Header.h";

using namespace std;

/*
Depth First Search (DFS) – Iterative and Recursive Implementation
Depth–first search (DFS) is an algorithm for traversing or searching tree or graph data structures. One starts at the root (selecting some arbitrary node as the root for a graph) and explore as far as possible along each branch before backtracking.

The following graph shows the order in which the nodes are discovered in DFS:

DFS Tree

Depth–first search in trees
A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any acyclic connected graph is a tree. For a tree, we have the following traversal methods:

Preorder: visit each node before its children.
Postorder: visit each node after its children.
Inorder (for binary trees only): visit left subtree, node, right subtree.
These are already covered in detail in separate posts.

Depth–first search in Graph
A Depth–first search (DFS) is a way of traversing graphs closely related to the preorder traversal of a tree. Following is the recursive implementation of preorder traversal:

procedure preorder(treeNode v)
{
    visit(v);
    for each child u of v
        preorder(u);
}
To turn this into a graph traversal algorithm, replace “child” with “neighbor”. But to prevent infinite loops, keep track of the vertices that are already discovered and not revisit them.

procedure dfs(vertex v)
{
    visit(v);
    for each neighbor u of v
        if u is undiscovered
            call dfs(u);
}
The recursive algorithm can be implemented as follows in C++
*/


//data structure to store a graph edge
struct Edge {

    int src, dest;
};

//a class to represent a graph object
class Graph
{
public:
    //a vector ofvectors to represent an adjacency list
    vector<vector<int>> adjList;

    //Graph constructor
    Graph(vector<Edge> const& edges, int n)
    {
        //resize teh vector to hold n elements of type vector<int>
        adjList.resize(n);

        //add edges to the undirected graph
        for (auto& edge : edges)
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};


//function to perform dfs traversal on the graph on a graph
void DFS(Graph const& graph, int v, vector<bool>& discovered)
{
    //mark the current node as discovered
    discovered[v] = true;

    //print the current node
    cout << v << " ";

    //do for every edge
    for (int u : graph.adjList[v])
    {
        //if u is not yet discovered
        if (!discovered[u])
        {
            DFS(graph, u, discovered);
        }
    }
}

int main()
{
    //vector of graph edges as per the above diagram
    vector<Edge> edges =
    {
        // Notice that node 0 is unconnected
        {1, 2}, {1, 7}, {1, 8}, {2, 3}, {2, 6}, {3, 4},
        {3, 5}, {8, 9}, {8, 12}, {9, 10}, {9, 11}
    };

    //total number of nodes in the graph from 0-12
    int n = 13;

    //build a graph from the given edges
    Graph graph(edges, n);

    //to keep track of whether a vertex is discovered or not
    vector<bool> discovered(n);

    //perform DFS traversal from all undiscovered nodes to 
    // cover all connected components of a graph
    for (int i = 0; i < n; i++)
    {
        if (discovered[i] == false)
        {
            DFS(graph, i, discovered);
        }
    }

    return 0;
}

