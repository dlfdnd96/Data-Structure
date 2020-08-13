/*
*** Stack�� �����ϴ� �Լ��� ����ÿ�. ��, �ϳ��� stack�� �߰���
*** ����� �� �ְ� array �� �ٸ� data ������ ��� �Ұ���.
*/

#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;

void StackSort(stack<int>& s1)
{
    stack<int>* s2 = new stack<int>();

	while (!s1.empty())
	{
		const int tmp = s1.top();
		s1.pop();

		while (!s2->empty() && s2->top() > tmp)
		{
			const int tmp2 = s2->top();
			s2->pop();
			s1.push(tmp2);
		}

		s2->push(tmp);
	}

	while (!s2->empty())
	{
		const int descSortData = s2->top();
		s2->pop();
		s1.push(descSortData);
	}
}

int main()
{
	stack<int>* s1 = new stack<int>();
	s1->push(3);
	s1->push(5);
	s1->push(1);
	s1->push(6);
	StackSort(*s1);
	
	while (!s1->empty())
	{
		const int stackData = s1->top();
		s1->pop();
		cout << stackData << endl;
	}

    return 0;
}
