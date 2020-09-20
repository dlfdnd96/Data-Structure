/*
*** 이진트리에서 주어진 두 개의 노드의 첫 번째 공통된 부모 노드를 찾으시오.
*** (단, 다른 자료구조 사용 금지)
*/
#include <iostream>
#include <map>

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
        int mNodeData;
        Node* mLeftNode;
        Node* mRightNode;
        Node* mParentNode;
    }; // end Node class

public:
    Node* GetTreeRoot() const;
    Tree(int const size)
    {
        this->mTreeRootMap = new std::map<int, Node>();
        this->mTreeRoot = makeBSTRecursive(0, size - 1, nullptr);
    }
    Node* CommonAncestor(const int data1, const int data2) const;
    Node* CommonAncestor2(const int data1, const int data2) const;

private:
    constexpr Node* makeBSTRecursive(const int start, const int end, Node* parent) const;
    Node* getNode(const int data) const;
    constexpr Node* goUpBy(Node* node, int diff) const;
    constexpr int depth(const Node* node) const;
    constexpr bool covers(const Node* root, const Node* node) const;
    Node getSibling(const Node* node) const;

private:
    Node* mTreeRoot;
    std::map<int, Node>* mTreeRootMap;
}; // end Tree Class

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
Tree::Node* Tree::CommonAncestor(const int data1, const int data2) const
{
    Node* p = getNode(data1);
    Node* q = getNode(data2);
    int diff = depth(p) - depth(q);
    Node* first = diff > 0 ? q : p;
    Node* second = diff > 0 ? p : q;
    second = goUpBy(second, std::abs(diff));
    while (first != second && first != nullptr && second != nullptr)
    {
        first = first->GetParentNode();
        second = second->GetParentNode();
    }

    return (first == nullptr || second == nullptr) ? nullptr : first;
}

Tree::Node* Tree::CommonAncestor2(const int data1, const int data2) const
{
    Node* p = getNode(data1);
    Node* q = getNode(data2);
    if (!covers(this->GetTreeRoot(), p) || !covers(this->GetTreeRoot(), q))
    {
        return NULL;
    }
    else if (covers(p, q))
    {
        return p;
    }
    else if (covers(q, p))
    {
        return q;
    }

    Node* sibling = &getSibling(p);
    Node* parent = p->GetParentNode();
    while (!covers(sibling, q))
    {
        sibling = &getSibling(parent);
        parent = parent->GetParentNode();
    }

    return parent;
}

constexpr Tree::Node* Tree::makeBSTRecursive(const int start, const int end, Node* parent) const
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
    this->mTreeRootMap->insert(std::make_pair(mid, *node));

    return node;
}

Tree::Node* Tree::getNode(const int data) const
{
    auto mapIter = mTreeRootMap->find(data);
    if (mapIter != mTreeRootMap->end())
    {
        return &(mapIter->second);
    }
    else
    {
        return nullptr;
    }
}

constexpr Tree::Node* Tree::goUpBy(Node* node, int diff) const
{
    while (diff > 0 && node != nullptr)
    {
        node = node->GetParentNode();
        --diff;
    }

    return node;
}

constexpr int Tree::depth(const Node* node) const
{
    int depth = 0;
    while (node != nullptr)
    {
        node = node->GetParentNode();
        ++depth;
    }

    return depth;
}

constexpr bool Tree::covers(const Node* root, const Node* node) const
{
    if (root == nullptr)
    {
        return false;
    }
    if (root == node)
    {
        return true;
    }

    return covers(root->GetLeftNode(), node) || covers(root->GetRightNode(), node);
}

Tree::Node Tree::getSibling(const Node* node) const
{
    if (node == nullptr || node->GetParentNode() == nullptr)
    {
        return NULL;
    }

    Node* parent = node->GetParentNode();

    return parent->GetLeftNode() == node ? *(parent->GetRightNode()) : *(parent->GetLeftNode());
}

int main()
{
    Tree t(10);
    Tree::Node* fa = t.CommonAncestor2(6, 7);
    cout << fa->GetNodeData() << endl;

    return 0;
}
