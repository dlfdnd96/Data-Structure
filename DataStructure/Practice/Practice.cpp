#include <iostream>

using namespace std;

int main()
{
    char a;
    char b = 'a';
    cin >> a;
    for (; b < a; ++b)
    {
        cout << b << endl;
    }

    return 0;
}
