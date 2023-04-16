#include "Header.h"

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string timeConversion(string s) {
    stringstream istream;
    stringstream ostream;
    uint16_t hour = 0;
    istream << s.substr(0, 2);
    istream >> hour;

    if (s.substr(8, 2) == "PM")
    {
        (hour != 12) ? hour += 12 : hour;
    }
    else // AM
    {
        (hour == 12) ? hour = 0 : hour;
    }

    ostream << setfill('0') << setw(2) << hour << s.substr(2, s.size() - 4);

    return ostream.str();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
