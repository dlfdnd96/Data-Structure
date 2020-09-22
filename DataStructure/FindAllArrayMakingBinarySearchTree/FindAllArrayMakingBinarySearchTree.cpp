/*
*** 배열의 값을 왼쪽부터 하나씩 넣으면서 이진검색트리를 만들었다.
*** 주어진 이진검색트리를 만들 수 있는 모든 배열을 찾는
*** 알고리즘을 구현하시오. (단, 트리에 중복값 없음)
*/

#include <iostream>
#include <vector>

class Tree
{
public:
    class Node
    {
    public:
        Node(int data) : mNodeData(data) {}
        void SetNodeData(int const data);
        int GetNodeData() const;
        void SetLeftNode(Node* const node);
        Node* GetLeftNode() const;
        void SetRightNode(Node* const node);
        Node* GetRightNode() const;

    private:
        int mNodeData;
        Node* mLeftNode;
        Node* mRightNode;
    }; // end Node class

public:
    Tree(int size)
    {
        mTreeRoot = makeBST(0, size - 1);
    }
    Node* GetTreeRoot() const;
    std::vector<std::vector<int>>* AllSequences(Tree::Node* node);

private:
    Node* mTreeRoot;
    Node* makeBST(int start, int end);
    void weaveLists(std::vector<int>& first, std::vector<int>& second, std::vector<std::vector<int>>* results, std::vector<int>& prefix);
}; // end Tree class

/* Getter, Setter */
int Tree::Node::GetNodeData() const
{
    return this->mNodeData;
}
void Tree::Node::SetNodeData(int const data)
{
    this->mNodeData = data;
}
Tree::Node* Tree::Node::GetLeftNode() const
{
    return this->mLeftNode;
}
void Tree::Node::SetLeftNode(Node* const node)
{
    this->mLeftNode = node;
}
Tree::Node* Tree::Node::GetRightNode() const
{
    return this->mRightNode;
}
void Tree::Node::SetRightNode(Node* const node)
{
    this->mRightNode = node;
}
Tree::Node* Tree::GetTreeRoot() const
{
    return this->mTreeRoot;
}

/* function */
std::vector<std::vector<int>>* Tree::AllSequences(Tree::Node* node)
{
    std::vector<std::vector<int>>* result = new std::vector<std::vector<int>>();
    if (node == nullptr)
    {
        std::vector<int> emptyVector;
        result->emplace_back(emptyVector);

        return result;
    }

    std::vector<int>* prefix = new std::vector<int>();
    prefix->emplace_back(node->GetNodeData());

    std::vector<std::vector<int>>* leftSeq = AllSequences(node->GetLeftNode());
    std::vector<std::vector<int>>* rightSeq = AllSequences(node->GetRightNode());
    for (std::vector<int> left : *leftSeq)
    {
        for (std::vector<int> right : *rightSeq)
        {
            std::vector<std::vector<int>>* weaved = new std::vector<std::vector<int>>;
            weaveLists(left, right, weaved, *prefix);
            for (std::vector<int> iter : *weaved)
            {
                result->emplace_back(iter);
            }
        }
    }

    return result;
}

Tree::Node* Tree::makeBST(int start, int end)
{
    if (start > end)
    {
        return nullptr;
    }

    int mid = (start + end) >> 1;
    Node* node = new Node(mid);
    node->SetLeftNode(makeBST(start, mid - 1));
    node->SetRightNode(makeBST(mid + 1, end));

    return node;
}

void Tree::weaveLists(std::vector<int>& first, std::vector<int>& second, std::vector<std::vector<int>>* results, std::vector<int>& prefix)
{
    if (first.size() == 0 || second.size() == 0)
    {
        std::vector<int>* result = new std::vector<int>();
        for (int data : prefix)
        {
            result->emplace_back(data);
        }

        for (int firstData : first)
        {
            result->emplace_back(firstData);
        }

        for (int secondData : second)
        {
            result->emplace_back(secondData);
        }

        return;
    }

    int headFirst = first[0];
    first.erase(first.begin());
    prefix.emplace_back(headFirst);
    weaveLists(first, second, results, prefix);
    prefix.pop_back();
    first.insert(first.begin(), headFirst);

    int headSecond = second[0];
    second.erase(second.begin());
    prefix.emplace_back(headSecond);
    weaveLists(first, second, results, prefix);
    prefix.pop_back();
    second.insert(second.begin(), headSecond);
}

int main()
{
    Tree t(5);
    std::vector<std::vector<int>>* result = t.AllSequences(t.GetTreeRoot());
    for (std::vector<int> l : *result)
    {
        for (int data : l)
        {
            std::cout << data;
        }

        std::cout << std::endl;
    }
    
    return 0;
}
