/*
*** 주어진 트리가 이진 검색이 가능한 트리인지 확인하는 함수를 구현하라
***         (4)
***        /   \
***       /     \
***      /       \
***     (1)       (7)
***    /   \     /   \
***   /     \   /     \
*** (0)     (2)(5)    (8)
***          \   \    /  \
***          (3) (6) (11)(9)
***                      /
***                    (9)
***                    / \
***                  (9) (9)
***                  / \
***                (8) (9)   
*/

#include <iostream>
#include <vector>
#include <limits>

using std::cout;
using std::endl;

class Tree
{
public:
    class Node
    {
    public:
        Node(int data) : mNodeData(data) {}
        constexpr void SetNodeData(int const data);
        int GetNodeData() const;
        constexpr void SetLeftNode(Node* const node);
        Node* GetLeftNode() const;
        constexpr void SetRightNode(Node* const node);
        Node* GetRightNode() const;

    private:
        int mNodeData;
        Node* mLeftNode;
        Node* mRightNode;
    };

public:
    Tree(int size)
    {
        this->mTreeSize = size;
        mTreeRoot = makeBSTRecursive(0, size - 1);
        mTreeRoot->GetRightNode()->GetRightNode()->GetRightNode()->SetLeftNode(new Node(9));
        this->mTreeSize++;
        mTreeRoot->GetRightNode()->GetRightNode()->GetRightNode()->SetRightNode(new Node(9));
        this->mTreeSize++;
        mTreeRoot->GetRightNode()->GetRightNode()->GetRightNode()->GetLeftNode()->SetLeftNode(new Node(9));
        this->mTreeSize++;
        mTreeRoot->GetRightNode()->GetRightNode()->GetRightNode()->GetLeftNode()->SetRightNode(new Node(9));
        this->mTreeSize++;
        mTreeRoot->GetRightNode()->GetRightNode()->GetRightNode()->GetLeftNode()->GetLeftNode()->SetLeftNode(new Node(8));
        this->mTreeSize++;
        mTreeRoot->GetRightNode()->GetRightNode()->GetRightNode()->GetLeftNode()->GetLeftNode()->SetRightNode(new Node(9));
        this->mTreeSize++;
    }
    constexpr void SetTreeRoot(Node* const root);
    Node* GetTreeRoot() const;
    constexpr void SetTreeSize(int const size);
    int GetTreeSize() const;
    bool IsValidateBST1();
    constexpr bool IsValidateBST2();
    constexpr bool IsValidateBST2ByNodeRecursive(const Node* const node);
    constexpr bool IsValidateBST3();
    constexpr bool IsValidateBST3ByNodeRecursive(const Node* const node, const int minValue, const int maxValue);

private:
    constexpr Node* makeBSTRecursive(const int start, const int end);
    constexpr void doInorderRecursive(const Node* root, std::vector<int>& binaryArray);

private:
    Node* mTreeRoot;
    int mTreeSize;
}; // end Tree class

/* Setter, Getter */
constexpr void Tree::Node::SetNodeData(int const data)
{
    this->mNodeData = data;
}
int Tree::Node::GetNodeData() const
{
    return this->mNodeData;
}
constexpr void Tree::Node::SetLeftNode(Node* const node)
{
    this->mLeftNode = node;
}
Tree::Node* Tree::Node::GetLeftNode() const
{
    return this->mLeftNode;
}
constexpr void Tree::Node::SetRightNode(Node* const node)
{
    this->mRightNode = node;
}
Tree::Node* Tree::Node::GetRightNode() const
{
    return this->mRightNode;
}
constexpr void Tree::SetTreeRoot(Node* root)
{
    this->mTreeRoot = root;
}
Tree::Node* Tree::GetTreeRoot() const
{
    return this->mTreeRoot;
}
constexpr void Tree::SetTreeSize(int const size)
{
    this->mTreeSize = size;
}
int Tree::GetTreeSize() const
{
    return this->mTreeSize;
}

/* function */
bool Tree::IsValidateBST1()
{
    std::vector<int> binarySearchArray(this->GetTreeSize());
    doInorderRecursive(mTreeRoot, binarySearchArray);
    for (unsigned int index = 1; index < binarySearchArray.size(); ++index)
    {
        if (binarySearchArray[index] < binarySearchArray[index - 1])
        {
            return false;
        }
    }

    return true;
}

int gLastPrinted = NULL;
constexpr bool Tree::IsValidateBST2()
{
    return IsValidateBST2ByNodeRecursive(this->GetTreeRoot());
}

constexpr bool Tree::IsValidateBST2ByNodeRecursive(const Node* const node)
{
    if (node == nullptr)
    {
        return true;
    }

    if (!IsValidateBST2ByNodeRecursive(node->GetLeftNode()))
    {
        return false;
    }

    if (gLastPrinted != NULL && node->GetNodeData() < gLastPrinted)
    {
        return false;
    }

    gLastPrinted = node->GetNodeData();
    if (!IsValidateBST2ByNodeRecursive(node->GetRightNode()))
    {
        return false;
    }

    return true;
}

constexpr bool Tree::IsValidateBST3()
{
    return IsValidateBST3ByNodeRecursive(this->GetTreeRoot(), INT_MIN, INT_MAX);
}

constexpr bool Tree::IsValidateBST3ByNodeRecursive(const Tree::Node* const node, const int minValue, const int maxValue)
{
    if (node == nullptr)
    {
        return true;
    }

    if (node->GetNodeData() < minValue || node->GetNodeData() > maxValue)
    {
        return false;
    }

    if (!IsValidateBST3ByNodeRecursive(node->GetLeftNode(), minValue, node->GetNodeData()) ||
        !IsValidateBST3ByNodeRecursive(node->GetRightNode(), node->GetNodeData(), maxValue))
    {
        return false;
    }

    return true;
}

int gIndex = 0;
constexpr void Tree::doInorderRecursive(const Node* root, std::vector<int>& binaryArray)
{
    if (root != nullptr)
    {
        doInorderRecursive(root->GetLeftNode(), binaryArray);
        binaryArray[gIndex] = root->GetNodeData();
        ++gIndex;
        doInorderRecursive(root->GetRightNode(), binaryArray);
    }
}

constexpr Tree::Node* Tree::makeBSTRecursive(const int start, const int end)
{
    if (start > end)
    {
        return nullptr;
    }

    int mid = (start + end) / 2;
    Node* node = new Node(mid);
    node->SetLeftNode(makeBSTRecursive(start, mid - 1));
    node->SetRightNode(makeBSTRecursive(mid + 1, end));

    return node;
}

int main()
{
    std::unique_ptr<Tree> uniqueTreePtr = std::make_unique<Tree>(10);
    cout << "Solution 1 - using inorder: " << uniqueTreePtr->IsValidateBST1() << endl;
    cout << "Solution 2 - without array: " << uniqueTreePtr->IsValidateBST2() << endl;
    cout << "Solution 3 - min/max: " << uniqueTreePtr->IsValidateBST3() << endl;

    return 0;
}
