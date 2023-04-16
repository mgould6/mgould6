#include "Header.h";

using namespace std;

/*
Find all possible combinations of words formed from the mobile keypad Recursive
Google Translate Icon
Given a sequence of numbers between 2 and 9, print all possible combinations of words formed from the mobile keypad which has english alphabets associated with each key.

Keypad



Input: [2, 3, 4]

Output:

ADG BDG CDG AEG BEG CEG AFG BFG CFG ADH BDH CDH AEH BEH CEH AFH BFH CFH ADI BDI CDI AEI BEI CEI AFI BFI CFI
Practice This Problem

Recursive Implementation
We can use recursion to solve this problem. The idea is to consider every input digit one by one, replace the digit with each character in the mobile keypad, and recur for the next digit. When all the digits are processed, print the result.

Following is the C++
*/

// top down recursive function to find all possible combinations by
// replacing keys digits with characters of the corresponding list
void findCombinations(vector<vector<char>>& keypad, vector<int> const& keys, unordered_set<string>& combinations, string result, int index)
{
	// if we have processed every digit of the key, print the result
	if (index == -1)
	{
		combinations.insert(result);
		return;
	}

	// stores the current digit
	int digit = keys[index];

	// get the list corresponding to the current digit and
	// one by one, replace the digit with each character in the
	// corresponding list and recur for the next digit
	for (char c : keypad[digit]) {
		findCombinations(keypad, keys, combinations, c + result, index - 1);
	}
}


unordered_set<string>findAllCombinations(vector<vector<char>>& keypad, vector<int> const keys)
{
	// create a set to store all combinations
	unordered_set<string> combinations;

	// invalid input - return empty set
	if (keypad.size() == 0 || keys.size() == 0) {
		return combinations;
	}

	// find and return all combinations
	int n = keys.size();
	findCombinations(keypad, keys, combinations, "", n - 1);
	return combinations;
}
int main()
{
	// mobile keypad
	vector<vector<char>> keypad =
	{
		{}, {},        // 0 and 1 digit doesn't have any characters associated
		{ 'A', 'B', 'C' },
		{ 'D', 'E', 'F' },
		{ 'G', 'H', 'I' },
		{ 'J', 'K', 'L' },
		{ 'M', 'N', 'O' },
		{ 'P', 'Q', 'R', 'S'},
		{ 'T', 'U', 'V' },
		{ 'W', 'X', 'Y', 'Z'}
	};

	// input number in the form of an array (number cannot start from 0 or 1)
	vector<int> keys = { 2, 3, 4 };

	// find all combinations
	unordered_set<string> combinations = findAllCombinations(keypad, keys);
	for (string s : combinations) {
		cout << s << ' ';
	}

	return 0;
}

/*

*/