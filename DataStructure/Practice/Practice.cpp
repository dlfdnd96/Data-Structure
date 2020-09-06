#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    double x;
    cin >> x;
    cout << static_cast<int>(x) << endl;

    //cout << fixed;
    //cout.precision(6);
    //ostringstream ss;
    //ss << x;
    //string s(ss.str());
    //string decimal = s.substr(2);
    string temp = to_string(x);
    string temp2 = temp.substr(2);
    cout << temp2 << endl;

    return 0;
}