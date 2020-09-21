/*
*** 이진트리에서 주어진 두 개의 노드의 첫 번째 공통된 부모 노드를 찾으시오.
*** (단, 다른 자료구조 사용 금지)
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
        void SetNodeData(int const data);
        Node* GetLeftNode() const;
        void SetLeftNode(Node* const node);
        Node* GetRightNode() const;
        void SetRightNode(Node* const node);
        Node* GetParentNode() const;
        void SetParentNode(Node* const node);

    private:
        int mNodeData;
        Node* mLeftNode;
        Node* mRightNode;
        Node* mParentNode;
    }; // end Node class

    class Result
    {
    public:
        Result(Node* n, bool isAnc) : mResultNode(n), mIsAncestor(isAnc) {}
        Node* GetResultNode() const;
        bool GetIsAncestor() const;
    private:
        Node* mResultNode;
        bool mIsAncestor;
    }; // end Result class

public:
    Node* GetTreeRoot() const;
    Tree(int size)
    {
        this->mTreeRootMap = new std::map<int, Node>();
        this->mTreeRoot = makeBSTRecursive(0, size - 1, nullptr);
    }
    Node* CommonAncestor(int data1, int data2) const;
    Node* CommonAncestor2(int data1, int data2) const;
    Node* CommonAncestor3(int data1, int data2) const;
    Node* InitCommonAncestor4(int data1, int data2) const;
    Node* CommonAncestor4(Node* root, Node* p, Node* q) const;
    Node* InitCommonAncestor5(int data1, int data2) const;
    Result* CommonAncestor5(Node* root, Node* p, Node* q) const;

private:
    constexpr Node* makeBSTRecursive(int start, int end, Node* parent) const;
    Node getNode(int data) const;
    constexpr Node* goUpBy(Node* node, int diff) const;
    constexpr int depth(Node* node) const;
    constexpr bool covers(Node* root, Node* node) const;
    Node* getSibling(Node* node) const;
    Node* ancestorHelper(Node* root, Node* p, Node* q) const;

private:
    Node* mTreeRoot;
    std::map<int, Node>* mTreeRootMap;
}; // end Tree Class

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
Tree::Node* Tree::Node::GetParentNode() const
{
    return this->mParentNode;
}
void Tree::Node::SetParentNode(Node* const node)
{
    this->mParentNode = node;
}
Tree::Node* Tree::GetTreeRoot() const
{
    return this->mTreeRoot;
}
Tree::Node* Tree::Result::GetResultNode() const
{
    return this->mResultNode;
}
bool Tree::Result::GetIsAncestor() const
{
    return this->mIsAncestor;
}

/* function */
Tree::Node* Tree::CommonAncestor(int data1, int data2) const
{
    Node p = getNode(data1);
    Node q = getNode(data2);
    int diff = depth(&p) - depth(&q);
    Node* first = diff > 0 ? &q : &p;
    Node* second = diff > 0 ? &p : &q;
    second = goUpBy(second, std::abs(diff));
    while (first != second && first != nullptr && second != nullptr)
    {
        first = first->GetParentNode();
        second = second->GetParentNode();
    }

    return (first == nullptr || second == nullptr) ? nullptr : first;
}

Tree::Node* Tree::CommonAncestor2(int data1, int data2) const
{
    Node p = getNode(data1);
    Node q = getNode(data2);
    if (!covers(this->GetTreeRoot(), &p) || !covers(this->GetTreeRoot(), &q))
    {
        return nullptr;
    }
    else if (covers(&p, &q))
    {
        return &p;
    }
    else if (covers(&q, &p))
    {
        return &q;
    }

    Node* sibling = getSibling(&p);
    Node* parent = (&p)->GetParentNode();
    while (!covers(sibling, &q))
    {
        sibling = getSibling(parent);
        parent = parent->GetParentNode();
    }

    return parent;
}

Tree::Node* Tree::CommonAncestor3(int data1, int data2) const
{
    Node p = getNode(data1);
    Node q = getNode(data2);

    if (!covers(this->mTreeRoot, &p) || !covers(this->mTreeRoot, &q))
    {
        return nullptr;
    }

    return ancestorHelper(this->mTreeRoot, &p, &q);
}

Tree::Node* Tree::InitCommonAncestor4(int data1, int data2) const
{
    Node p = getNode(data1);
    Node q = getNode(data2);

    return CommonAncestor4(mTreeRoot, &p, &q);
}

Tree::Node* Tree::CommonAncestor4(Node* root, Node* p, Node* q) const
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->GetNodeData() == p->GetNodeData() && root->GetNodeData() == q->GetNodeData())
    {
        return root;
    }

    Node* x = CommonAncestor4(root->GetLeftNode(), p, q);
    if (x != nullptr && x->GetNodeData() != p->GetNodeData() && x->GetNodeData() != q->GetNodeData())
    {
        return x;
    }

    Node* y = CommonAncestor4(root->GetRightNode(), p, q);
    if (y != nullptr && y->GetNodeData() != p->GetNodeData() && y->GetNodeData() != q->GetNodeData())
    {
        return y;
    }

    if (x != nullptr && y != nullptr)
    {
        return root;
    }
    else if (root->GetNodeData() == p->GetNodeData() || root->GetNodeData() == q->GetNodeData())
    {
        return root;
    }
    else
    {
        return x == nullptr ? y : x;
    }
}

Tree::Node* Tree::InitCommonAncestor5(int data1, int data2) const
{
    Node p = getNode(data1);
    Node q = getNode(data2);
    Result* r = CommonAncestor5(mTreeRoot, &p, &q);
    if (r->GetIsAncestor())
    {
        return r->GetResultNode();
    }

    return nullptr;
}

Tree::Result* Tree::CommonAncestor5(Node* root, Node* p, Node* q) const
{
    if (root == nullptr)
    {
        return new Result(nullptr, false);
    }
    
    if (root->GetNodeData() == p->GetNodeData() && root->GetNodeData() == q->GetNodeData())
    {
        return new Result(root, true);
    }
    
    Result* rx = CommonAncestor5(root->GetLeftNode(), p, q);
    if (rx->GetIsAncestor())
    {
        return rx;
    }

    Result* ry = CommonAncestor5(root->GetRightNode(), p, q);
    if (ry->GetIsAncestor())
    {
        return ry;
    }

    if (rx->GetResultNode() != nullptr && ry->GetResultNode() != nullptr)
    {
        return new Result(root, true);
    }
    else if (root->GetNodeData() == p->GetNodeData() || root->GetNodeData() == q->GetNodeData())
    {
        bool isAncestor = rx->GetResultNode() != nullptr || ry->GetResultNode() != nullptr;
        
        return new Result(root, isAncestor);
    }
    else
    {
        return new Result(rx->GetResultNode() != nullptr ? rx->GetResultNode() : ry->GetResultNode(), false);
    }
}

constexpr Tree::Node* Tree::makeBSTRecursive(int start, int end, Node* parent) const
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

Tree::Node Tree::getNode(int data) const
{
    auto mapIter = mTreeRootMap->find(data);
    if (mapIter != mTreeRootMap->end())
    {
        return mapIter->second;
    }
    else
    {
        return NULL;
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

constexpr int Tree::depth(Node* node) const
{
    int depth = 0;
    while (node != nullptr)
    {
        node = node->GetParentNode();
        ++depth;
    }

    return depth;
}

constexpr bool Tree::covers(Node* root, Node* node) const
{
    if (root == nullptr)
    {
        return false;
    }
    if (root->GetNodeData() == node->GetNodeData())
    {
        return true;
    }

    return covers(root->GetLeftNode(), node) || covers(root->GetRightNode(), node);
}

Tree::Node* Tree::getSibling(Node* node) const
{
    if (node == nullptr || node->GetParentNode() == nullptr)
    {
        return NULL;
    }

    Node* parent = node->GetParentNode();

    return parent->GetLeftNode()->GetNodeData() == node->GetNodeData() ? parent->GetRightNode(): parent->GetLeftNode();
}

Tree::Node* Tree::ancestorHelper(Node* root, Node* p, Node* q) const
{
    if (root == nullptr || root->GetNodeData() == p->GetNodeData() || root->GetNodeData() == q->GetNodeData())
    {
        return root;
    }

    bool pIsOnLeft = covers(root->GetLeftNode(), p);
    bool qIsOnLeft = covers(root->GetLeftNode(), q);
    if (pIsOnLeft != qIsOnLeft)
    {
        return root;
    }
    Node* childSide = pIsOnLeft ? root->GetLeftNode() : root->GetRightNode();

    return ancestorHelper(childSide, p, q);
}

int main()
{
    Tree t(10);
    Tree::Node* fa = t.InitCommonAncestor5(0, 3);
    cout << "The first common ancestor is " << fa->GetNodeData() << endl;

    return 0;
}
