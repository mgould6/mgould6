#include "Header.h";

using namespace std;

/*
Combinations of words formed by replacing given numbers with corresponding alphabets
Google Translate Icon
Given a set of single-digit positive numbers, find all possible combinations of words formed by replacing the continuous digits with corresponding character in the English alphabet, i.e., subset {1} can be replaced by A, {2} can be replaced by B, {1, 0} can be replaced by J, {2, 1} can be replaced by U, etc.

For example,

Input:  digits[] = { 1, 2, 2 }
Output: ABB, AV, LB

{1, 2, 2} = ABB
{1, 22} = AV
{12, 2} = LB


Input:  digits[] = { 1, 2, 2, 1 }
Output: ABBA, ABU, AVA, LBA, LU

{1, 2, 2, 1} = ABBA
{1, 2, 21} = ABU
{1, 22, 1} = AVA
{12, 2, 1} = LBA
{12, 21} = LU
Practice This Problem

For every i'th element of the input, there are two possibilities – either this i'th element will be combined with (i+1)'th element if the number formed by them is less than equal to 26 or i'th element itself will form a new character.

The idea is to recur with the remaining digits by considering both possibilities. The algorithm can be implemented as follows in C++,
*/

//function to find all possible combinations of words formed by replacing
//given positive numbers with the corresponding character of the english alphabet
void recur(vector<int> const& digits, int i, string str)
{
	int n = digits.size();

	//base case: all digits are processed in the current configuration

	if (i == n)
	{
		//print the string 
		cout << str << endl;
		return;
	}
	static string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int sum = 0;

	//process the next two digits (i'th and te (i + 1)'th
	for (int j = i; j <= min(i + 1, n - 1); j++)
	{
		sum = (sum * 10) + digits[j];

		//if a valid character can be formed by taking one or both digits
		//append it to the output and recur for the remaining digits
		if (sum <= 26)
		{
			recur(digits, j + 1, str + alphabet[sum - 1]);
		}
	}
}

void findCombinations(vector<int> const& digits)
{
	//base case
	if (digits.size() == 0)
	{
		return;
	}

	recur(digits, 0, "");
}


/*
We can also solve this problem by using binary tree and recursion. The basic idea remains the same, i.e., recur with the remaining digits by considering both possibilities for every i'th element of the input – either this i'th element will be combined with (i+1)'th element if the number formed by them is less than equal to 26 or i'th element itself will form a new character.

The only difference is that instead of using string to store the output, use binary tree nodes. Following is the implementation in C++, Java, and Python based on the idea. It constructs a binary tree where each leaf node contains one unique combination of words formed.

The time complexity of both above-discussed methods is exponential and requires additional space for the recursion (call stack).




*/
struct Node
{
	string key;
	Node* left, * right;

	Node(string key)
	{
		this->key = key;
		this->left = this->right = nullptr;
	}
};

//function to print all leaf nodes of the binary tree
void print(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->left == nullptr && node->right == nullptr)
	{
		cout << node->key << " ";
	}
	else {
		print(node->right);
		print(node->left);
	}
}

//function to construct a binary tree where each leaf node contains
//one unique combination of words formed
void construct(Node* root, vector<int> const& digits, int i)
{
	int n = digits.size();

	//base case empty tree
	if (root == nullptr || i == n)
	{
		return;
	}

	static string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	//check if digits[i+1] exists
	if (i + 1 < n)
	{
		//process current and next digit
		int sum = 10 * digits[i] + digits[i + 1];

		//if both digits can form a valid character, create the left child from it
		if (sum <= 26)
		{
			root->left = new Node(root->key + alphabet[sum - 1]);
		}

		//construct the left subtree by remaining digits
		construct(root->left, digits, i + 2);
	}
	//process the current digit and create the right child from it
	root->right = new Node(root->key + alphabet[digits[i] - 1]);

	//construct the right subtree by remaining digits
	construct(root->right, digits, i + 1);
}

int main()
{
	vector<int> digits = { 1, 2, 2 };

	findCombinations(digits);


	vector<int> digits2 = { 1, 2, 2, 1 };

	//create empty root
	Node* root = new Node("");

	//construct binary tree
	construct(root, digits2, 0);

	print(root);

	return 0;
}

/*

*/