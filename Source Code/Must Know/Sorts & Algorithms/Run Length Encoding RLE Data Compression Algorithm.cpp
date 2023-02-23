#include "Header.h";

using namespace std;

/*
Run Length Encoding (RLE) Data Compression Algorithm
Google Translate Icon
Run–length encoding (RLE) is a simple form of lossless data compression that runs on sequences with the same value occurring many consecutive times. It encodes the sequence to store only a single value and its count.

For example, consider a screen containing plain black text on a solid white background. There will be many long runs of white pixels in the blank space and many short runs of black pixels within the text.

WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW
With a run–length encoding (RLE) data compression algorithm applied to the above hypothetical scan line, it can be rendered as 12W1B12W3B24W1B14W. This can be interpreted as a sequence of twelve W’s, one B, twelve W’s, three B’s, etc.


Practice This Problem


The idea is to run a linear scan on the string, and for each distinct character, append the character and its consecutive occurrence in the output string.

The algorithm can be implemented as follows in C++, Java, and Python. Note that the output size will double the input size in the worst case, so the algorithm can’t run in-place. e.g. ABCD —> A1B1C1D1.

The time complexity of the above solution is O(n), where n is the length of the input string and doesn’t require any extra space.


*/

string encode(string str)
{
	//stores output string
	string encoding = "";
	int count;

	for (int i = 0; str[i]; i++)
	{
		//count occurrences of character at index i
		count = 1;

		while (str[i] == str[i + 1])
		{
			count++, i++;
		}

		//append current charater and its count to the result

		encoding += to_string(count) + str[i];
	}
	return encoding;
}

int main()
{
	string str = "ABBCCCD";

	cout << encode(str);

	return 0;
}

