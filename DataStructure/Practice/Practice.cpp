#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());
    string answer = "";
    for (int index = 0; index < participant.size(); ++index)
    {
        if (index == participant.size() - 1 || participant[index] != completion[index])
        {
            answer = participant[index];

            break;
        }
    }

    return answer;
}

int main()
{
    vector<string> participant = { "leo", "kiki", "eden", "eden" };
    vector<string> completion = { "eden", "kiki", "leo" };
    string answer = solution(participant, completion);

    cout << answer << endl;

    return 0;
}