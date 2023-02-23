#include "Header.h";

using namespace std;

/*
Generate a list of possible words from a character matrix
Given an M × N boggle board, find a list of all possible words that can be formed by a sequence of adjacent characters on the board.

We are allowed to search a word in all eight possible directions, i.e., North, West, South, East, North-East, North-West, South-East, South-West, but a word should not have multiple instances of the same cell.


Consider the following the traditional 4 × 4 boggle board. If the input dictionary is [START, NOTE, SAND, STONED], the valid words are [NOTE, SAND, STONED].

Boggle Board

Practice This Problem


We can use Depth–first search (DFS) to solve this problem. The idea is to start from each character in the matrix and explore all eight paths possible and recursively check if they lead to a solution or not. To make sure that a word doesn’t have multiple instances of the same cell, keep track of cells involved in the current path in the matrix, and before exploring any cell, ignore the cell if it is already covered in the current path.

To find all possible movements from a cell, we can use an array to store the relative position of movement from any cell. For example, if the current cell is (x, y), we can move to (x + row[k], y + col[k]) for 0 <= k <=7 using the following array:

int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 }
int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 }
So, from position (x, y), we can move to:

(x – 1, y – 1)
(x – 1, y)
(x – 1, y + 1)
(x, y – 1)
(x, y + 1)
(x + 1, y – 1)
(x + 1, y)
(x + 1, y + 1)
The algorithm can be implemented as follows in C++

The time complexity of the proposed solution is exponential. We can improve the time complexity by using a Trie data structure. The idea is to build a Trie out of the given words and then perform preorder traversal (DFS) on it, as shown below in C++, Java, and Python:
*/

//data structure to store a trie node
struct Trie
{
    //true when the node is a leaf node
    bool isLeaf;
    unordered_map<char, Trie*> character;

    //constructor
    Trie()
    {
        isLeaf = false;
    }
};

//iterative function to insert a string into a trie
void insert(Trie* const& root, string const& str)
{
    //start from the root node
    Trie* curr = root;
    for (char ch : str)
    {
        //create a new node if the path doesn't exist
        if (curr->character.find(ch) == curr->character.end())
        {
            curr->character[ch] = new Trie();
        }

        //got to the next node 
        curr = curr->character[ch];
    }
    curr->isLeaf = true;
}

// Below arrays detail all eight possible movements from a cell
// (top, right, bottom, left, and four diagonal moves)
int row[] = { -1, -1, -1, 0, 1, 0, 1, 1 };
int col[] = { -1, 1, 0, -1, -1, 1, 0, 1 };

// Function to check if it is safe to go to cell (x, y) from the current cell.
// The function returns false if (x, y) is not valid matrix coordinates
// or cell (x, y) is already processed.
bool isSafe(int x, int y, vector<vector<bool>>& processed, vector<vector<char>> const& board, char ch) {
    return (x >= 0 && x < processed.size()) && (y >= 0 && y < processed[0].size()) &&
        !processed[x][y] && (board[x][y] == ch);
}

//a recursive function to search valid words present in a boggle using trie
void searchBoggle(Trie* root, vector<vector<char>>& board, int i, int j, vector<vector<bool>>& processed, string path, unordered_set<string>& result)
{
    // if a leaf node is encountered
    if (root->isLeaf)
    {
        // update result with the current word
        result.insert(path);
    }

    // mark the current cell as processed
    processed[i][j] = true;

    // traverse all children of the current Trie node
    for (auto it : root->character)
    {
        // check for all eight possible movements from the current cell
        for (int k = 0; k < 8; k++)
        {
            // skip if a cell is invalid, or it is already processed
            // or doesn't lead to any path in the Trie
            if (isSafe(i + row[k], j + col[k], processed, board, it.first))
            {
                searchBoggle(it.second, board, i + row[k], j + col[k],
                    processed, path + it.first, result);
            }
        }
    }

    // backtrack: mark the current cell as unprocessed
    processed[i][j] = false;
}

unordered_set<string> searchInBoggle(vector<vector<char>>& board, unordered_set<string>& words)
{
    //construct a set for storing the result
    unordered_set<string> result;

    //base case
    if (board.size() == 0)
    {
        return result;
    }

    // M x M board
    int M = board.size();
    int N = board[0].size();

    //insert all words into a trie
    Trie* root = new Trie();
    for (string word : words)
    {
        insert(root, word);
    }

    //construct a boolean matrix to store whether a cell is processed or not
    vector<vector<bool>> processed(M, vector<bool>(N));

    string s;

    //consider each character in the matrix
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //current character 
            char ch = board[i][j];

            //proceed only if the current character is a child of the trie root node
            if (root->character[ch])
            {
                s = ch;
                searchBoggle(root->character[ch], board, i, j, processed, s, result);
            }
        }
    }
    //return the result set
    return result;
}

template <typename T>
void printSet(unordered_set<T> const& input)
{
    cout << "{";
    int n = input.size();
    for (auto const& i : input) {
        cout << i;
        if (--n) {
            cout << ", ";
        }
    }
    cout << "}";
}

int main()
{
    vector<vector<char>> board = {
                    {'M', 'S', 'E', 'F'},
                    {'R', 'A', 'T', 'D'},
                    {'L', 'O', 'N', 'E'},
                    {'K', 'A', 'F', 'B'}
    };

    unordered_set<string> words = { "START", "NOTE", "SAND", "STONED" };

    unordered_set<string> output = searchInBoggle(board, words);
    printSet(output);

    return 0;
}

/*
*
* We can use Depth–first search (DFS) to solve this problem. The idea is to start from each character in the matrix and explore all eight paths possible and recursively check if they lead to a solution or not. To make sure that a word doesn’t have multiple instances of the same cell, keep track of cells involved in the current path in the matrix, and before exploring any cell, ignore the cell if it is already covered in the current path.

To find all possible movements from a cell, we can use an array to store the relative position of movement from any cell. For example, if the current cell is (x, y), we can move to (x + row[k], y + col[k]) for 0 <= k <=7 using the following array:

int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 }
int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 }
So, from position (x, y), we can move to:

(x – 1, y – 1)
(x – 1, y)
(x – 1, y + 1)
(x, y – 1)
(x, y + 1)
(x + 1, y – 1)
(x + 1, y)
(x + 1, y + 1)
The algorithm can be implemented as follows in C++
// Below arrays detail all eight possible movements from a cell
// (top, right, bottom, left, and four diagonal moves)
int row[] = { -1, -1, -1, 0, 1, 0, 1, 1 };
int col[] = { -1, 1, 0, -1, -1, 1, 0, 1 };

// Function to check if it is safe to go to cell (x, y) from the current cell.
// The function returns false if (x, y) is not valid matrix coordinates
// or cell (x, y) is already processed.
bool isSafe(int x, int y, vector<vector<bool>>& processed) {
    return (x >= 0 && x < processed.size()) && (y >= 0 && y < processed[0].size()) &&
        !processed[x][y];
}

// A recursive function to generate all possible words in a boggle
void searchBoggle(vector<vector<char>> const& board, unordered_set<string> const& words, unordered_set<string>& result, vector<vector<bool>>& processed,
    int i, int j, string path)
{
    // mark the current node as processed
    processed[i][j] = true;

    // update the path with the current character and insert it into the set
    path += board[i][j];

    // check whether the path is present in the input set
    if (words.find(path) != words.end()) {
        result.insert(path);
    }

    // check for all eight possible movements from the current cell
    for (int k = 0; k < 8; k++)
    {
        // skip if a cell is invalid, or it is already processed
        if (isSafe(i + row[k], j + col[k], processed)) {
            searchBoggle(board, words, result, processed, i + row[k], j + col[k], path);
        }
    }

    // backtrack: mark the current node as unprocessed
    processed[i][j] = false;
}

unordered_set<string> searchBoggle(vector<vector<char>> const& board, unordered_set<string> const& words)
{
    // construct a set to store valid words constructed from the boggle
    unordered_set<string> result;

    // base case
    if (board.size() == 0) {
        return result;
    }

    // `M × N` board
    int M = board.size();
    int N = board[0].size();

    // construct a boolean matrix to store whether a cell is processed or not
    vector<vector<bool>> processed(M, vector<bool>(N));

    // generate all possible words in a boggle
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) {
            // consider each character as a starting point and run DFS
            searchBoggle(board, words, result, processed, i, j, "");
        }
    }

    return result;
}

template <typename T>
void printSet(unordered_set<T> const& input)
{
    cout << "{";
    int n = input.size();
    for (auto const& i : input) {
        cout << i;
        if (--n) {
            cout << ", ";
        }
    }
    cout << "}";
}

int main()
{
    vector<vector<char>> board = {
                    {'M', 'S', 'E', 'F'},
                    {'R', 'A', 'T', 'D'},
                    {'L', 'O', 'N', 'E'}
    };

    unordered_set<string> words = { "START", "NOTE", "SAND", "STONED" };

    unordered_set<string> output = searchBoggle(board, words);
    printSet(output);

    return 0;
}
*/