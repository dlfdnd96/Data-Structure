/*
*** 배열을 이진검색트리로 만들어라.
***        (4)
***        / \
***       /   \
***      /     \
***     /       \
***   (1)       (7)
***   / \       / \
*** (0) (2)    (5) (8)
***       \      \   \
***       (3)    (6) (9)
*/

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Tree
{
public:
    class Node
    {
    public:
        Node(__int32 const data) : mData(data) {}
        Node* GetLeftNode() const;
        void SetLeftNode(Node* const node);
        Node* GetRightNode() const;
        void SetRightNode(Node* const node);
        __int32 GetNodeData() const;

    private:
        __int32 mData;
        Node* mLeftNode = nullptr;
        Node* mRightNode = nullptr;
    }; // end Node class

public:
    Node* GetTreeRoot() const;
    void MakeTree(const vector<__int32>& inputArray);
    Node* MakeTreeRecursive(const vector<__int32>& inputArray, __int32 const start, __int32 const end);
    void SearchBTree(Node* const node, __int32 const find);

private:
    Node* mRoot;
}; // end Tree class

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
__int32 Tree::Node::GetNodeData() const
{
    return this->mData;
}
Tree::Node* Tree::GetTreeRoot() const
{
    return this->mRoot;
}

void Tree::MakeTree(const vector<__int32>& inputArray)
{
    mRoot = MakeTreeRecursive(inputArray, 0, inputArray.size() - 1);
}

Tree::Node* Tree::MakeTreeRecursive(const vector<__int32>& inputArray, __int32 const start, __int32 const end)
{
    if (start > end)
    {
        return nullptr;
    }

    __int32 mid = (start + end) / 2;
    Node* node = new Node(inputArray[mid]);
    node->SetLeftNode(MakeTreeRecursive(inputArray, start, mid - 1));
    node->SetRightNode(MakeTreeRecursive(inputArray, mid + 1, end));

    return node;
}

void Tree::SearchBTree(Node* const node, __int32 const find)
{
    if (find < node->GetNodeData())
    {
        cout << "Data is smaller than " << node->GetNodeData() << endl;
        SearchBTree(node->GetLeftNode(), find);
    }
    else if (find > node->GetNodeData())
    {
        cout << "Data is bigger than " << node->GetNodeData() << endl;
        SearchBTree(node->GetRightNode(), find);
    }
    else
    {
        cout << "Data found!!: " << node->GetNodeData() << endl;
    }
}

int main()
{
    vector<__int32> testVector;

    for (int number = 0; number < 10; ++number)
    {
        testVector.push_back(number);
    }

    std::unique_ptr<Tree> treeUniquePointer = std::make_unique<Tree>();
    treeUniquePointer->MakeTree(testVector);
    treeUniquePointer->SearchBTree(treeUniquePointer->GetTreeRoot(), 2);

    return 0;
}
