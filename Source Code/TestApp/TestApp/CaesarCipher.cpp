#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'caesarCipher' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER k
 */

// This question is easy once you understand how chars are stored in a computers memory.
// http://www.asciitable.com/ -> every char is actually mapped to a decimal (integer) value, this
// means that the integer value of 65 represents 'A', 97 represents 'a', etc. 
// C++ is great because it will implicity convert char <-> integer

// Note: There is one tricky part however, which is that a char can not an integer value greater than 
// 127. This is because a standard char is only 1 byte/8 bits (with one sign bit), so the largest value 
// it can hold is 2^7 - 1 = 127. Thus when we perform our rotations, we should temporarily store
// the char in a larger data type such as an integer so that we can go higher than 127, then convert
// it back to an integer after doing the arithmetic.


string caesarCipher(string s, int k) {
    string Encrypted;
    
    k %=26; //set the limit of rotations to 26
    for (int i = 0; i< s.size(); i++)           //loops through the length of the string
    {
        if(s[i] >= 'A' && s[i] <= 'Z')
        {
            int letter = s[i];
            letter += k;
            if(letter > 'Z') {
                letter %= 'Z';
                letter += 'A';
                letter--;
            }
            s[i] = letter;
        }
        if(s[i] >= 'a' && s[i] <= 'z')
        {
            int letter = s[i];
            letter += k;
            if(letter > 'z') {
                letter %= 'z';
                letter += 'a';
                letter--;
            }
            s[i] = letter;

        }
    }
    cout << s << "\n";

    Encrypted = s;
    
    return Encrypted;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string s;
    getline(cin, s);

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    string result = caesarCipher(s, k);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
