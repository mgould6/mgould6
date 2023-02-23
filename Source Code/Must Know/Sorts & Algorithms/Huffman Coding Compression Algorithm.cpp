#include "Header.h";

using namespace std;

/*
Huffman Coding Compression Algorithm


Note that the input string’s storage is 47×8 = 376 bits, but our encoded string only takes 194 bits, i.e., about 48% of data compression. To make the program readable, we have used string class to store the above program’s encoded string.

Since efficient priority queue data structures require O(log(n)) time per insertion, and a complete binary tree with n leaves has 2n-1 nodes, and Huffman coding tree is a complete binary tree, this algorithm operates in O(n.log(n)) time, where n is the total number of characters.


*/

#define EMPTY_STRING ""

struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

//function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

//comparison object to be used to order the heap

struct comp
{

	bool operator()(const Node* l, const Node* r) const
	{
		//the highest priority item has the lowest frequency
		return l->freq > r->freq;
	}
};

//utitilty function to check if huffman tree contains only a single node
bool isLeaf(Node* root)
{
	return root->left == nullptr && root->right == nullptr;
}

//traverse the huffman tree and store huffman codes in a map
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
	{
		return;
	}

	//found a leaf
	if (isLeaf(root))
	{
		huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

//traverse the huffman tree and decode the encoded string
void decode(Node* root, int& index, string str)
{
	if (root == nullptr)
	{
		return;
	}

	//found a leaf node
	if (isLeaf(root))
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
	{
		decode(root->left, index, str);
	}
	else
	{
		decode(root->right, index, str);
	}
}

//builds huffman tree and decodes the given input text
void buildHuffmanTree(string text)
{
	//base case: empty string
	if (text == EMPTY_STRING)
	{
		return;
	}

	//count the frequency of appearance of each character 
	//and store it in a map
	unordered_map<char, int> freq;
	for (char ch : text)
	{
		freq[ch]++;
	}

	//create a priority queue to store live nodes of the huffman tree
	priority_queue<Node*, vector<Node*>, comp> pq;

	//create a leaf node for each character and add it to the priority queueu
	for (auto pair : freq)
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	//do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		//remove the two nodes of the highest priority
		//(the lowest frequency) from the queue

		Node* left = pq.top(); pq.pop();
		Node* right = pq.top(); pq.pop();

		//create a new internal node with these two nodes as children 
		//and with a frequency equal to the sum of the two nodes frequencies
		//add the new node to the priority queue

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));

	}

	//root stores pointer to the root of huffman tree
	Node* root = pq.top();

	//traverse the huffman tree and store huffman codes
	//in a map. alse, print them
	unordered_map<char, string> huffmanCode;
	encode(root, EMPTY_STRING, huffmanCode);

	cout << "huffman codes are: \n" << endl;
	for (auto pair : huffmanCode)
	{
		cout << pair.first << " " << pair.second << endl;
	}

	cout << "\nThe original string is: \n" << text << endl;

	//print encoded string
	string str;
	for (char ch : text)
	{
		str += huffmanCode[ch];
	}

	cout << "\nThe encode string is: \n" << str << endl;
	cout << "\nThe decoded string is: \n";

	if (isLeaf(root))
	{
		//special case for input like a, aa, aaa, etc.
		while (root->freq)
		{
			cout << root->ch;
		}
	}
	else
	{
		//traverse the huffman tree again and this time
		//decode the encoded string
		int index = -1;
		while (index < (int)str.size() - 1)
		{
			decode(root, index, str);
		}
	}
}

//huffman coding algorith implementation in C++
int main()
{
	string text = "Huffman coding is a data compression algorithm.";
	buildHuffmanTree(text);

	return 0;
}

/*

*/