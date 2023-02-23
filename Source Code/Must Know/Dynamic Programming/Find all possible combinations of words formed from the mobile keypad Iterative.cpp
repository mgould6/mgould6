#include "Header.h";

using namespace std;

/*
Find all possible combinations of words formed from the mobile keypad Iterative
Google Translate Icon
Given a sequence of numbers between 2 and 9, print all possible combinations of words formed from the mobile keypad which has english alphabets associated with each key.

Keypad



Input: [2, 3, 4]

Output:

ADG BDG CDG AEG BEG CEG AFG BFG CFG ADH BDH CDH AEH BEH CEH AFH BFH CFH ADI BDI CDI AEI BEI CEI AFI BFI CFI
Practice This Problem

Iterative Implementation
We can also solve this problem iteratively using a list. The idea remains the same, but instead of recursing, we push the partial-word into a list. For each character associated with a current digit in the keypad, we append each word’s character in the output list and push the result into a list. So at the end of each iteration, the list contains all possible combinations of words until the current digit. We repeat this process until all digits are processed.

Following is the C++


*/

void findCombinations(vector<vector<char>>& keypad, vector<int> const& keys)
{
    // list to store combinations of all possiblel words
    vector<string> list;

    // push all characters associated with the first digit into the output list
    for (char c : keypad[keys[0]])
    {
        list.push_back(string(1, c));
    }

    // start from the second digit
    for (int i = 1; i < keys.size(); i++)
    {
        // create a temporary vector
        vector<string> vec;

        // for each character associated  with the current digit in te keypad
        for (char c : keypad[keys[i]])
        {
            // append each words current character in the output list
            // and push into a temporary vector
            for (string str : list)
            {
                vec.push_back(str + c);
            }
        }

        //vector vec now contains all possible combinations of words
        // until the current digit

        // replace contents of output list with that of the temporary vector
        list = vec;
    }

    // print output list containing all combinations of words possible
    for (string str : list)
    {
        cout << str << " ";
    }
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
    findCombinations(keypad, keys);

    return 0;
}

/*

*/