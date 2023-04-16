#include "Header.h"

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'miniMaxSum' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void miniMaxSum(vector<int> arr) {
    vector<long> MinSortArray(begin(arr), end(arr));
    vector<long> MaxSortArray(begin(arr), end(arr));



    //sort array for min
    sort(MinSortArray.begin(), MinSortArray.end());

    //     for (int i = 0; i < MinSortArray.size(); ++i) {
    //     cout <<"MINSORT: " << MinSortArray[i] << endl;
    // }

        //sort array for max
    sort(MaxSortArray.begin(), MaxSortArray.end());

    //     for (int i = 0; i < MaxSortArray.size(); ++i) {
    //     cout << "MAXSORT: " << MaxSortArray[i] << endl;
    // }


        //min sum of sorted array
    long long MinSum = accumulate(MinSortArray.begin(), MinSortArray.begin() + 4, 0LL);

    //max sum of sorted array
    long long MaxSum = accumulate(MaxSortArray.begin() + 1, MaxSortArray.end(), 0LL);

    cout << MinSum << " " << MaxSum;
}

int main()
{

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(5);

    for (int i = 0; i < 5; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    miniMaxSum(arr);

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string& str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
