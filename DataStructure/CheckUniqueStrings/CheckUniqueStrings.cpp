/*
*** 주어진 문자열의 문자들이 모두 고유한지 확인하시오.
*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

bool IsUnique(std::string str)
{
    if (str.size() > 128)
    {
        return false;
    }

    std::vector<bool> charSet(128, 0);
    for (int index = 0; index < str.size(); ++index)
    {
        if (charSet[str[index]])
        {
            return false;
        }

        charSet[str[index]] = true;
    }

    return true;
}

bool IsUniqueUsingHashTable(std::string str)
{
    std::map<int, bool> hashMap;
    for (int index = 0; index < str.size(); ++index)
    {
        std::map<int, bool>::iterator iter = hashMap.find(str[index]);
        if (iter == hashMap.end())
        {
            hashMap.insert(std::make_pair(str[index], true));
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool IsUniqueUsingBitOperator(std::string str)
{
    int checker = 0;
    for (int index = 0; index < str.size(); ++index)
    {
        int val = str[index] - 'a';
        if ((checker & (1 << val)) > 0)
        {
            return false;
        }

        checker |= (1 << val);
    }

    return true;
}

bool IsUniqueUsingPointer(std::string str)
{
    std::sort(str.begin(), str.end());
    for (int index = 1; index < str.size(); ++index)
    {
        if (str[index - 1] == str[index])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::cout << std::boolalpha << IsUnique("abcdefgghijk") << std::endl;
    std::cout << std::boolalpha << IsUnique("abcdefghijk") << std::endl;
    std::cout << std::boolalpha << IsUniqueUsingHashTable("abcdefgghijk") << std::endl;
    std::cout << std::boolalpha << IsUniqueUsingHashTable("abcdefghijk") << std::endl;
    std::cout << std::boolalpha << IsUniqueUsingBitOperator("abcdefgghijk") << std::endl;
    std::cout << std::boolalpha << IsUniqueUsingBitOperator("abcdefghijk") << std::endl;
    std::cout << std::boolalpha << IsUniqueUsingPointer("abcdefgghijk") << std::endl;
    std::cout << std::boolalpha << IsUniqueUsingPointer("abcdefghijk") << std::endl;

    return 0;
}
