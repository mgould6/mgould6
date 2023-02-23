#include "Header.h";

using namespace std;

/*
Given a sequence of length <= 8 consisting of I and D, where I denotes the increasing sequence and D denotes the decreasing sequence, decode the sequence to construct a minimum number without repeated digits.

For example,

sequence        output

IIDDIDID  ——>  125437698
IDIDII    ——>  1325467
DDDD      ——>  54321
IIII      ——>  12345
Practice This Problem

The idea is simple and effective. For each element of the given sequence, insert its position index+1 into a stack. If the current character is increasing 'I' or all characters of the input sequence are processed, pop all numbers from the stack and append them to the output string.

Following is the implementation in C++
*/

string decode(string seq)
{
	//result store the output string
	string result;

	//create an empty stack of integers
	stack<int> s;

	//run n+1 times where n is the length of the input sequence
	for (int i = 0; i <= seq.length(); i++)
	{
		//push number i+1 into the stack
		s.push(i + 1);

		//if all characters of the input sequence are processed
		//or the current character is I (increasing)
		if (i == seq.length() || seq[i] == 'I')
		{
			//run till stack is empty
			while (!s.empty())
			{
				//remove a top element from the stack and add it to the solution
				result += to_string(s.top());
				s.pop();
			}
		}
	}

	return result;
}

int main()
{
	// input sequence
	string seq = "IDIDII";

	cout << "The minimum number is " << decode(seq);


	return 0;
}

/*

*/