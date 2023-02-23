#include "Header.h";

using namespace std;

/*
Disjoint–Set Data Structure (Union–Find Algorithm)

Explain the working of a disjoint–set data structure and efficiently implement it.

Problem: We have some number of items. We are allowed to merge any two items to consider them equal. At any point, we are allowed to ask whether two items are considered equal or not.

What is a disjoint–set?
A disjoint–set is a data structure that keeps track of a set of elements partitioned into several disjoint (non-overlapping) subsets. In other words, a disjoint set is a group of sets where no item can be in more than one set. It is also called a union–find data structure as it supports union and find operation on subsets. Let’s begin by defining them:

Find: It determines in which subset a particular element is in and returns the representative of that particular set. An item from this set typically acts as a “representative” of the set.

Union: It merges two different subsets into a single subset, and the representative of one set becomes representative of another.

The disjoint–set also supports one other important operation called MakeSet, which creates a set containing only a given element in it.

How does Union–Find work?
We can determine whether two elements are in the same subset by comparing the result of two Find operations. If the two elements are in the same set, they have the same representation; otherwise, they belong to different sets. If the union is called on two elements, merge the two subsets to which the two elements belong.

How to Implement Disjoint Sets?
Disjoint–set forests are data structures where each set is represented by a tree data in which each node holds a reference to its parent and the representative of each set is the root of that set’s tree.

Find follows parent nodes until it reaches the root.
Union combines two trees into one by attaching one tree’s root into the root of the other.
For example, consider five disjoint sets S1, S2, S3, S4, and S5 represented by a tree, as shown below diagram. Each set initially contains only one element each, so their parent pointer points to itself or NULL.

S1 = {1}, S2 ={2}, S3 = {3}, S4 ={4} and S5 = {5}

The Find operation on element i will return representative of Si, where 1 <= i <= 5, i.e., Find(i) = i.

Union–Find Algorithm

If we do Union (S3, S4), S3 and S4 will be merged into one disjoint set, S3. Now,

S1 = {1}, S2 ={2}, S3 = {3, 4} and S5 = {5}.

Find(4) will return representative of set S3, i.e., Find(4) = 3

Union–Find Algorithm – Step 1

If we do Union (S1, S2), S1 and S2 will be merged into one disjoint set, S1. Now,

S1 = {1, 2}, S3 = {3, 4} and S5 = {5}.

Find(2) or Find(1) will return the representative of set S1, i.e., Find(2) = Find(1) = 1

Union–Find Algorithm – Step 2

If we do Union (S3, S1), S3 and S1 will be merged into one disjoint set, S3. Now,

S3 = {1, 2, 3, 4} and S5 = {5}.

Union–Find Algorithm – Step 3

One way of implementing these might be:

function MakeSet(x)
    x.parent = x

function Find(x)
    if x.parent == x
        return x
    else
        return Find(x.parent)

function Union(x, y)
    xRoot = Find(x)
    yRoot = Find(y)
    xRoot.parent = yRoot
Following is the C++, Java, and Python implementation of union–find that uses a hash table to implement a disjoint set:

The above approach is no better than the linked list approach because the tree it creates can be highly unbalanced; however, we can enhance it in two ways.

1. The first way, called union by rank, is to always attach the smaller tree to the root of the larger tree. Since it is the depth of the tree that affects the running time, the tree with a smaller depth gets added under the root of the deeper tree, which only increases the depth of the depths were equal. Single element trees are defined to have a rank of zero, and whenever two trees of the same rank r are united, the result has the rank of r+1. The worst-case running-time improves to O(log(n)) for the Union or Find operation.

2. The second improvement, called path compression, is a way of flattening the tree’s structure whenever Find is used on it. The idea is that each node visited heading to a root node may as well be attached directly to the root node; they all share the same representative. To effect this, as Find recursively traverses up the tree, it changes each node’s parent reference to point to the root that is found. The resulting tree is much flatter, speeding up future operations not only on these elements but on those referencing them, directly or indirectly.


*/
//a class to represent a disjoint set
class DisjointSet
{
    unordered_map<int, int> parent;

    //stores the depth of the trees
    unordered_map<int, int> rank;

public:
    //perform makeSet operation
    void makeSet(vector<int> const& universe)
    {
        //create n disjoint sets (one for each item)
        for (int i : universe)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    //find the root of the set in which element k belongs

    int Find(int k)
    {
        //if k is not the root
        if (parent[k] != k)
        {
            //path compression
            parent[k] = Find(parent[k]);
        }
        return parent[k];
    }

    void Union(int a, int b)
    {
        //find the root of the sets in which elements x and y belong
        int x = Find(a);
        int y = Find(b);

        //if x and y are present in the same set
        if (x == y)
        {
            return;
        }

        //always attach a smaller depth tree under the root of the deeper tree
        if (rank[x] > rank[y])
        {
            parent[y] = x;
        }
        else if (rank[x] < rank[y])
        {
            parent[x] = y;
        }
        else
        {
            parent[x] = y;
            rank[y]++;
        }
    }
};

void printSets(vector<int> const& universe, DisjointSet& ds)
{
    for (int i : universe)
    {
        cout << ds.Find(i) << " ";
    }
    cout << endl;
}

//disjoint set data structure union find algorithm
int main()
{
    //universe of times 
    vector<int> universe = { 1, 2, 3, 4, 5 };

    //initialize 'DisjointSet' class
    DisjointSet ds;

    //create a singleton set for each element of the universe
    ds.makeSet(universe);
    printSets(universe, ds);

    ds.Union(4, 3); //4 and 3 are in the same set
    printSets(universe, ds);

    ds.Union(2, 1); //1 and 2 are in the same set
    printSets(universe, ds);

    ds.Union(1, 3); //1 and 2 are in the same set
    printSets(universe, ds);

    return 0;
}

/*
*
* The velow approach is no better than the linked list approach because the tree it creates can be highly unbalanced; however, we can enhance it in two ways.

1. The first way, called union by rank, is to always attach the smaller tree to the root of the larger tree. Since it is the depth of the tree that affects the running time, the tree with a smaller depth gets added under the root of the deeper tree, which only increases the depth of the depths were equal. Single element trees are defined to have a rank of zero, and whenever two trees of the same rank r are united, the result has the rank of r+1. The worst-case running-time improves to O(log(n)) for the Union or Find operation.

2. The second improvement, called path compression, is a way of flattening the tree’s structure whenever Find is used on it. The idea is that each node visited heading to a root node may as well be attached directly to the root node; they all share the same representative. To effect this, as Find recursively traverses up the tree, it changes each node’s parent reference to point to the root that is found. The resulting tree is much flatter, speeding up future operations not only on these elements but on those referencing them, directly or indirectly.



class DisjointSet
{
    unordered_map<int, int> parent;

public:
    //perform MakeSet operation
    void makeSet(vector<int> const& universe)
    {
        //create n disjoint sets one for each item
        for (int i : universe)
        {
            parent[i] = i;
        }
    }

    //find the root of the set in which element k belongs
    int Find(int k)
    {
        //if k is root
        if (parent[k] == k)
        {
            return k;
        }

        //recur for the parent until we find the root
        return Find(parent[k]);
    }

    //perform union of two subsets
    void Union(int a, int b)
    {
        //find the root of the sets in which elements x and y belong
        int x = Find(a);
        int y = Find(b);

        parent[x] = y;
    }
};

void printSets(vector<int> const& universe, DisjointSet& ds)
{
    for (int i : universe)
    {
        cout << ds.Find(i) << " ";
    }
    cout << endl;
}


*/