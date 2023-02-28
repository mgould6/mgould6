#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'fizzBuzz' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

void fizzBuzz(int n) {
    int i;
    for (i=1; i<=n; i++)
    {
        // number divisible by 3 and 5 will
        // always be divisible by 15, print
        // 'FizzBuzz' in place of the number
        if (i%15 == 0)       
            printf ("FizzBuzz\n");   
         
        // number divisible by 3? print 'Fizz'
        // in place of the number
        else if ((i%3) == 0)   
            printf("Fizz\n");                
         
        // number divisible by 5, print 'Buzz' 
        // in place of the number
        else if ((i%5) == 0)                      
            printf("Buzz\n");                
     
        else // print the number           
            printf("%d\n", i);                
 
    }
}
int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    fizzBuzz(n);

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
