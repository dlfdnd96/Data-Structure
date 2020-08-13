/*
***           (1)
***         ¢×   ¢Ù
***      (2)       (3)
***    ¢×   ¢Ù
*** (4)       (5)
***
*** Inorder (Left, Root, Right): 4 2 5 1 3
*** Preorder (Root, Left, Right): 1 2 4 5 3
*** Postorder (Left, Right, Root): 4 5 2 3 1
*/
#include <iostream>

using std::cout;
using std::endl;

class Node
{
public:
    void SetData(__int32 const data);
    __int32 GetData() const;
    void SetLeft(Node* leftNode);
    Node* GetLeft() const;
    void SetRight(Node* rightNode);
    Node* GetRight() const;

private:
    __int32 mData;
    Node* mLeft;
    Node* mRight;
}; // end Node class

class Tree
{
public:
    void SetRoot(Node* const node);
    Node* GetRoot() const;
    Node* MakeNode(Node* const left, Node* const right, __int32 const data);
    void InorderRecursive(Node* const node);
    void PreorderRecursive(Node* const node);
    void PostorderRecursive(Node* const node);

private:
    Node* mRoot;
}; // end Tree class

void Node::SetData(__int32 const data)
{
    this->mData = data;
}
__int32 Node::GetData() const
{
    return this->mData;
}
void Node::SetLeft(Node* leftNode)
{
    this->mLeft = leftNode;
}
Node* Node::GetLeft() const
{
    return this->mLeft;
}
void Node::SetRight(Node* rightNode)
{
    this->mRight = rightNode;
}
Node* Node::GetRight() const
{
    return this->mRight;
}
void Tree::SetRoot(Node* const node)
{
    this->mRoot = node;
}
Node* Tree::GetRoot() const
{
    return this->mRoot;
}

Node* Tree::MakeNode(Node* const left, Node* const right, __int32 const data)
{
    Node* const node = new Node();
    node->SetData(data);
    node->SetLeft(left);
    node->SetRight(right);

    return node;
}

void Tree::InorderRecursive(Node* const node)
{
    if (node != nullptr)
    {
        InorderRecursive(node->GetLeft());
        cout << node->GetData();
        InorderRecursive(node->GetRight());
    }
}

void Tree::PreorderRecursive(Node* const node)
{
    if (node != nullptr)
    {
        cout << node->GetData();
        PreorderRecursive(node->GetLeft());
        PreorderRecursive(node->GetRight());
    }
}

void Tree::PostorderRecursive(Node* const node)
{
    if (node != nullptr)
    {
        PostorderRecursive(node->GetLeft());
        PostorderRecursive(node->GetRight());
        cout << node->GetData();
    }
}

int main()
{
    Tree* const t = new Tree();
    Node* const n4 = t->MakeNode(nullptr, nullptr, 4);
    Node* const n5 = t->MakeNode(nullptr, nullptr, 5);
    Node* const n2 = t->MakeNode(n4, n5, 2);
    Node* const n3 = t->MakeNode(nullptr, nullptr, 3);
    Node* const n1 = t->MakeNode(n2, n3, 1);
    t->SetRoot(n1);
    t->PostorderRecursive(t->GetRoot());

    return 0;
}
