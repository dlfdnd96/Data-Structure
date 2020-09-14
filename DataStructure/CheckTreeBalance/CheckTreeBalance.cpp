/*
*** 주어진 이진트리의 balance가 맞는지 확인하는 함수를 구현하라.
*** Balance란 어떤 node의 양쪽 서브트리의 길이가 1이상 차이가 나지 않는 것을 뜻함.
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
***                        \
***                        (10)
*/

#include <iostream>
#include <limits>

using std::cout;
using std::endl;

class Tree
{
public: 
    class Node
    {
    public:
        Node(int data) : mData(data) {}
        constexpr void SetNodeData(int const data);
        int GetNodeData() const;
        constexpr void SetLeftNode(Node* const n);
        Node* GetLeftNode() const;
        constexpr void SetRightNode(Node* const n);
        Node* GetRightNode() const;

    private:
        int mData;
        Node* mLeftNode;
        Node* mRightNode;
    }; // end Node class

    class Level
    {
    public:
        constexpr void SetMinLevel(int const level);
        int GetMinLevel() const;
        constexpr void SetMaxLevel(int const level);
        int GetMaxLevel() const;

    private:
        int mMinLevel = INT_MAX;
        int mMaxLevel = INT_MIN;
    }; // end Level class

public:
    Tree(int size)
    {
        mTreeRoot = makeBST(0, size - 1);
        mTreeRoot->GetRightNode()->GetRightNode()->GetRightNode()->SetRightNode(new Node(10));
        mTreeRoot->GetRightNode()->GetRightNode()->SetLeftNode(new Node(11));
    }
    constexpr Node* GetTreeRoot() const;
    constexpr bool IsBalanced(const Node* root);
    constexpr bool IsBalanced2(const Node* root);
    bool IsBalanced3(const Node* root);

private:
    Node* makeBST(const int start, const int end);
    constexpr int getHeight(const Node* root);
    constexpr int checkHeight(const Node* root);
    constexpr void checkBalanced(const Node* node, Level* obj, int level);
    Node* mTreeRoot;
}; // end Tree class

/* Getter, Setter */
constexpr void Tree::Node::SetNodeData(int const data)
{
    this->mData = data;
}
int Tree::Node::GetNodeData() const
{
    return this->mData;
}
constexpr void Tree::Node::SetLeftNode(Node* const n)
{
    this->mLeftNode = n;
}
Tree::Node* Tree::Node::GetLeftNode() const
{
    return this->mLeftNode;
}
constexpr void Tree::Node::SetRightNode(Node* const n)
{
    this->mRightNode = n;
}
Tree::Node* Tree::Node::GetRightNode() const
{
    return this->mRightNode;
}
constexpr Tree::Node* Tree::GetTreeRoot() const
{
    return this->mTreeRoot;
}
constexpr void Tree::Level::SetMinLevel(const int level)
{
    this->mMinLevel = level;
}
int Tree::Level::GetMinLevel() const
{
    return this->mMinLevel;
}
constexpr void Tree::Level::SetMaxLevel(const int level)
{
    this->mMaxLevel = level;
}
int Tree::Level::GetMaxLevel() const
{
    return this->mMaxLevel;
}

/* function */
Tree::Node* Tree::makeBST(const int start, const int end)
{
    if (start > end)
    {
        return nullptr;
    }

    unsigned int mid = (start + end) / 2;
    Node* node = new Node(mid);
    node->SetLeftNode(makeBST(start, mid - 1));
    node->SetRightNode(makeBST(mid + 1, end));

    return node;
}

constexpr bool Tree::IsBalanced(const Tree::Node* root)
{
    if (root == nullptr)
    {
        return true;
    }

    int heightDiff = getHeight(root->GetLeftNode()) - getHeight(root->GetRightNode());
    if (abs(heightDiff) > 1)
    {
        return false;
    }
    else
    {
        return IsBalanced(root->GetLeftNode()) && IsBalanced(root->GetRightNode());
    }
}

constexpr bool Tree::IsBalanced2(const Tree::Node* root)
{
    return checkHeight(root) != INT_MIN;
}

bool Tree::IsBalanced3(const Tree::Node* root)
{
    Level* obj = new Level();
    checkBalanced(root, obj, 0);
    if (std::abs(obj->GetMinLevel() - obj->GetMaxLevel()) > 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

constexpr int Tree::getHeight(const Tree::Node* root)
{
    if (root == nullptr)
    {
        return -1;
    }

    return std::max(getHeight(root->GetLeftNode()), getHeight(root->GetRightNode())) + 1;
}

constexpr int Tree::checkHeight(const Tree::Node* root)
{
    if (root == nullptr)
    {
        return -1;
    }

    int leftHeight = checkHeight(root->GetLeftNode());
    if (leftHeight == INT_MIN)
    {
        return INT_MIN;
    }

    int rightHeight = checkHeight(root->GetRightNode());
    if (rightHeight == INT_MIN)
    {
        return INT_MIN;
    }

    int heightDiff = leftHeight - rightHeight;
    if (std::abs(heightDiff) > 1)
    {
        return INT_MIN;
    }
    else
    {
        return std::max(leftHeight, rightHeight) + 1;
    }
}

constexpr void Tree::checkBalanced(const Node* node, Level* obj, int level)
{
    if (node == nullptr)
    {
        if (level < obj->GetMinLevel())
        {
            obj->SetMinLevel(level);
        }
        else if (level > obj->GetMaxLevel())
        {
            obj->SetMaxLevel(level);
        }

        return;
    }

    checkBalanced(node->GetLeftNode(), obj, level + 1);
    checkBalanced(node->GetRightNode(), obj, level + 1);
}

int main()
{
    std::unique_ptr<Tree> uniqueTreePtr = std::make_unique<Tree>(10);
    cout << uniqueTreePtr->IsBalanced(uniqueTreePtr->GetTreeRoot()) << endl;
    cout << uniqueTreePtr->IsBalanced2(uniqueTreePtr->GetTreeRoot()) << endl;
    cout << uniqueTreePtr->IsBalanced3(uniqueTreePtr->GetTreeRoot()) << endl;

    return 0;
}
