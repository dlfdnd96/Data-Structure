/*
*** 정수 값이 저장되어 있는 이진트리에서 연결된 노드의 합산이
*** 특정 숫자가 되는 경로의 개수를 찾으시오.
*** 경로의 시작과 끝점은 어디든 가능하지만 언제나 위에서
*** 아래로만 합산이 되어야 한다.
*/

#include <iostream>
#include <vector>
#include <map>

struct Tree
{
    struct Node
    {
        Node(int data) : mNodeData(data) {}

        int mNodeData;
        Node* mLeftNode;
        Node* mRightNode;
    }; // end Node struct

    Tree(int size) : mTreeRoot(MakeBST(0, size - 1)) {}
    Node* MakeBST(const int start, const int end);
    /* 방법 1 */
    int CountPathsWithSum(const int targetSum) const;
    int CountPathsWithSumByNodeRecursive(const Node* root, const int targetSum) const;
    int CountPathsWithSumFromNodeRecursive(const Node* node, const int targetSum, int currSum) const;
    /* 방법 2 */
    int CountPathsWithSumUsingArray(const int targetSum) const;
    int CountPathsWithSumUsingArrayByNodeRecursive(const Node* root, const int targetSum, std::vector<int>* vec) const;
    void AddValue(std::vector<int>* vec, const int value) const;
    int CountPaths(std::vector<int>* vec, const int targetSum) const;
    void RemoveLast(std::vector<int>* vec) const;
    /* 방법 3 */
    int CountPathsWithSumUsingHash(const int targetSum) const;
    int CountPathsWithSumUsingHashByNodeRecursive(const Node* node, const int targetSum, int currSum, std::map<int, int>* hashTable) const;
    void IncrementHashTable(std::map<int, int>* hashTable, const int key, const int value) const;

    Node* mTreeRoot;
}; // end Tree struct

Tree::Node* Tree::MakeBST(const int start, const int end)
{
    if (start > end)
    {
        return nullptr;
    }

    int mid = (start + end) >> 1;
    Node* node = new Node(mid);
    node->mLeftNode = MakeBST(start, mid - 1);
    node->mRightNode = MakeBST(mid + 1, end);

    return node;
}

int Tree::CountPathsWithSum(const int targetSum) const
{
    return CountPathsWithSumByNodeRecursive(mTreeRoot, targetSum);
}

int Tree::CountPathsWithSumByNodeRecursive(const Node* root, const int targetSum) const
{
    if (root == nullptr)
    {
        return 0;
    }

    int pathsFromRoot = CountPathsWithSumFromNodeRecursive(root, targetSum, 0);
    int pathsOnLeft = CountPathsWithSumByNodeRecursive(root->mLeftNode, targetSum);
    int pathsOnRight = CountPathsWithSumByNodeRecursive(root->mRightNode, targetSum);

    return pathsFromRoot + pathsOnLeft + pathsOnRight;
}

int Tree::CountPathsWithSumFromNodeRecursive(const Node* node, const int targetSum, int currSum) const
{
    if (node == nullptr)
    {
        return 0;
    }
    
    currSum += node->mNodeData;
    int totalPaths = 0;
    if (currSum == targetSum)
    {
        ++totalPaths;
    }

    totalPaths += CountPathsWithSumFromNodeRecursive(node->mLeftNode, targetSum, currSum);
    totalPaths += CountPathsWithSumFromNodeRecursive(node->mRightNode, targetSum, currSum);

    return totalPaths;
}

int Tree::CountPathsWithSumUsingArray(const int targetSum) const
{
    std::vector<int>* vec = new std::vector<int>();

    return CountPathsWithSumUsingArrayByNodeRecursive(mTreeRoot, targetSum, vec);
}

int Tree::CountPathsWithSumUsingArrayByNodeRecursive(const Node* root, const int targetSum, std::vector<int>* vec) const
{
    if (root == nullptr)
    {
        return 0;
    }
    
    int totalPaths = 0;
    AddValue(vec, root->mNodeData);
    totalPaths = CountPaths(vec, targetSum);
    totalPaths += CountPathsWithSumUsingArrayByNodeRecursive(root->mLeftNode, targetSum, vec);
    totalPaths += CountPathsWithSumUsingArrayByNodeRecursive(root->mRightNode, targetSum, vec);
    RemoveLast(vec);

    return totalPaths;
}

void Tree::AddValue(std::vector<int>* vec, const int value) const
{
    for (int index = 0; index < vec->size(); ++index)
    {
        (*vec)[index] += value;
    }

    vec->emplace_back(value);
}

int Tree::CountPaths(std::vector<int>* vec, const int targetSum) const
{
    int totalPaths = 0;
    for (int value : *vec)
    {
        if (value == targetSum)
        {
            ++totalPaths;
        }
    }

    return totalPaths;
}

void Tree::RemoveLast(std::vector<int>* vec) const
{
    int value = (*vec)[vec->size() - 1];
    vec->pop_back();
    for (int index = 0; index < vec->size(); ++index)
    {
        (*vec)[index] -= value;
    }
}

int Tree::CountPathsWithSumUsingHash(const int targetSum) const
{
    std::map<int, int>* hashTable = new std::map<int, int>();
    hashTable->insert(std::make_pair(0, 1));

    return CountPathsWithSumUsingHashByNodeRecursive(mTreeRoot, targetSum, 0, hashTable);
}

int Tree::CountPathsWithSumUsingHashByNodeRecursive(const Node* node, const int targetSum, int currSum, std::map<int, int>* hashTable) const
{
    if (node == nullptr)
    {
        return 0;
    }

    currSum += node->mNodeData;
    int sum = currSum - targetSum;
    int totalPaths = [&]() -> int
    { 
        std::map<int, int>::iterator iter = hashTable->find(sum);
        if (iter != hashTable->end())
        {
            return iter->second;
        }
        else
        {
            return 0;
        }
    }();

    IncrementHashTable(hashTable, currSum, 1);
    totalPaths += CountPathsWithSumUsingHashByNodeRecursive(node->mLeftNode, targetSum, currSum, hashTable);
    totalPaths += CountPathsWithSumUsingHashByNodeRecursive(node->mRightNode, targetSum, currSum, hashTable);
    IncrementHashTable(hashTable, currSum, -1);

    return totalPaths;
}

void Tree::IncrementHashTable(std::map<int, int>* hashTable, const int key, const int value) const
{
    int newCount = [&]() -> int
    {
        std::map<int, int>::iterator iter = hashTable->find(key);
        if (iter != hashTable->end())
        {
            return (iter->second) + value;
        }
        else
        {
            return value;
        }
    }();

    if (!newCount)
    {
        hashTable->erase(key);
    }
    else
    {
        (*hashTable)[key] = newCount;
    }
}

int main()
{
    Tree t(10);
    std::cout << "방법 1: " << t.CountPathsWithSum(5) << std::endl;
    std::cout << "방법 2: " << t.CountPathsWithSumUsingArray(5) << std::endl;
    std::cout << "방법 3: " << t.CountPathsWithSumUsingHash(5) << std::endl;

    return 0;
}
