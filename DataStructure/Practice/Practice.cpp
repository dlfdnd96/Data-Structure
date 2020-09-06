#include <iostream>

using namespace std;

struct Calendar
{
	unsigned int mYear;
	unsigned int mMonth;
	unsigned int mDay;
};

istream& operator>>(istream& is, Calendar& t)
{
	cin >> t.mYear;
	is.ignore(1, '.');
	cin >> t.mMonth;
	is.ignore(1, ':');
	cin >> t.mDay;

	return is;
}
ostream& operator<<(ostream& os, Calendar& t)
{
	if (t.mDay < 10)
	{
		cout << "0" << t.mDay << "-";
	}
	else
	{
		cout << t.mDay << "-";
	}

	if (t.mMonth < 10)
	{
		cout << "0" << t.mMonth << "-";
	}
	else
	{
		cout << t.mMonth << "-";
	}

	if (t.mYear < 1000)
	{
		if (99 < t.mYear < 1000)
		{
			cout << "0" << t.mYear << endl;
		}
		else if (9 < t.mYear < 100)
		{
			cout << "00" << t.mYear << endl;
		}
		else if (0 < t.mYear < 10)
		{
			cout << "000" << t.mYear << endl;
		}
	}
	else
	{
		cout << t.mYear << endl;
	}

	return os;
}

int main()
{
	struct Calendar t;
	cin >> t;
	cout << t;

	return 0;
}
