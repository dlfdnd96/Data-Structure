/*
*** 이진 검색트리에서 주어진 노드의 다음 노드를 찾는 함수를 구현하라.
*** 단, 다음 노드의 순서는 inorder traverse에 준한다.
***         (4)
***        /   \
***       /     \
***      /       \
***     (1)       (7)
***    /   \     /   \
***   /     \   /     \
*** (0)     (2)(5)    (8)
***          \   \       \
***          (3) (6)     (9)
*/
#include <iostream>

using std::cout;
using std::endl;

class Tree
{
public:
    class Node
    {
    public:
        Node(int const data) : mNodeData(data) {}
        int GetNodeData() const;
        constexpr void SetNodeData(int const data);
        Node* GetLeftNode() const;
        constexpr void SetLeftNode(Node* const node);
        Node* GetRightNode() const;
        constexpr void SetRightNode(Node* const node);
        Node* GetParentNode() const;
        constexpr void SetParentNode(Node* const node);

    private:
        __int32 mNodeData;
        Node* mLeftNode;
        Node* mRightNode;
        Node* mParentNode;
    }; // end Node class

public:
    Node* GetTreeRoot() const;
    Tree(int const size)
    {
        this->mTreeRoot = makeBSTRecursive(0, size - 1, nullptr);
    }
    void FindNext(const Node* node);

private:
    constexpr Node* makeBSTRecursive(const int start, const int end, Node* parent);
    constexpr const Node* findAboveRecursive(const Node* root, const Node* child);
    const Node* findBelowRecursive(const Node* root);

private:
    Node* mTreeRoot;
}; // end Tree class

/* Getter, Setter */
int Tree::Node::GetNodeData() const
{
    return this->mNodeData;
}
constexpr void Tree::Node::SetNodeData(int const data)
{
    this->mNodeData = data;
}
Tree::Node* Tree::Node::GetLeftNode() const
{
    return this->mLeftNode;
}
constexpr void Tree::Node::SetLeftNode(Node* const node)
{
    this->mLeftNode = node;
}
Tree::Node* Tree::Node::GetRightNode() const
{
    return this->mRightNode;
}
constexpr void Tree::Node::SetRightNode(Node* const node)
{
    this->mRightNode = node;
}
Tree::Node* Tree::Node::GetParentNode() const
{
    return this->mParentNode;
}
constexpr void Tree::Node::SetParentNode(Node* const node)
{
    this->mParentNode = node;
}
Tree::Node* Tree::GetTreeRoot() const
{
    return this->mTreeRoot;
}

/* function */
constexpr Tree::Node* Tree::makeBSTRecursive(const int start, const int end, Node* parent)
{
    if (start > end)
    {
        return nullptr;
    }

    int mid = (start + end) / 2;
    Node* node = new Node(mid);
    node->SetLeftNode(makeBSTRecursive(start, mid - 1, node));
    node->SetRightNode(makeBSTRecursive(mid + 1, end, node));
    node->SetParentNode(parent);

    return node;
}

constexpr const Tree::Node* Tree::findAboveRecursive(const Node* root, const Node* child)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->GetLeftNode() == child)
    {
        return root;
    }

    return findAboveRecursive(root->GetParentNode(), root);
}

const Tree::Node* Tree::findBelowRecursive(const Node* root)
{
    if (root->GetLeftNode() == nullptr)
    {
        return root;
    }

    return findBelowRecursive(root->GetLeftNode());
}

void Tree::FindNext(const Node* node)
{
    if (node->GetRightNode() == nullptr)
    {
        cout << findAboveRecursive(node->GetParentNode(), node)->GetNodeData() << " is " << node->GetNodeData() << "'s next" << endl;
    }
    else
    {
        cout << findBelowRecursive(node->GetRightNode())->GetNodeData() << " is " << node->GetNodeData() << "'s next" << endl;
    }
}

int main()
{
    std::unique_ptr<Tree> uniquePtrTree = std::make_unique<Tree>(10);
    uniquePtrTree->FindNext(uniquePtrTree->GetTreeRoot()->GetLeftNode()->GetRightNode()->GetRightNode());
    uniquePtrTree->FindNext(uniquePtrTree->GetTreeRoot()->GetLeftNode());
    uniquePtrTree->FindNext(uniquePtrTree->GetTreeRoot());
    uniquePtrTree->FindNext(uniquePtrTree->GetTreeRoot()->GetLeftNode()->GetLeftNode());
    uniquePtrTree->FindNext(uniquePtrTree->GetTreeRoot()->GetRightNode()->GetLeftNode()->GetRightNode());

    return 0;
}
