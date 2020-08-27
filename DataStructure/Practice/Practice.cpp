#include <iostream>
#include <exception>
#include <vector>

using namespace std;

int main()
{
	vector<__int32>* temp = new vector<__int32>(3);
	temp->at(0) = 1;
	temp->at(1) = 2;
	temp->at(2) = 3;
	//temp->at(3) = 4;
	temp[0][0] = 4;
	temp[0][1] = 5;
	temp[0][2] = 6;

	for (const auto& v : *temp)
	{
		cout << v << endl;
	}

	return 0;
}
