#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<int> numbers)
{
    vector<int> answer;
    set<int> plusTwoNumberSet;
    unsigned int index = 0;
    unsigned int iter = 1;
    unsigned int plusResult = 0;
    for (;;)
    {
        if (index == numbers.size() - 1)
        {
            break;
        }

        plusResult = numbers[index] + numbers[index + iter];
        plusTwoNumberSet.insert(plusResult);
        if (index + iter == numbers.size() - 1)
        {
            ++index;
            iter = 0;
        }

        ++iter;
    }

    index = 0;
    set<int>::iterator setIter = plusTwoNumberSet.begin();
    for (; setIter != plusTwoNumberSet.end(); ++setIter)
    {
        answer.emplace_back(*setIter);
    }

    return answer;
}

int main()
{
    vector<int> inputVector;
    inputVector.emplace_back(5);
    inputVector.emplace_back(0);
    inputVector.emplace_back(2);
    inputVector.emplace_back(7);
    //inputVector.emplace_back(1);

    vector<int> result = solution(inputVector);
    for (unsigned int index = 0; index < result.size(); ++index)
    {
        cout << result[index] << " ";
    }

    return 0;
}
