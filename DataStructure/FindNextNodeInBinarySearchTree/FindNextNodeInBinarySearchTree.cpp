/*
*** 이진 검색트리에서 주어진 노드의 다음 노드를 찾는 함수를 구현하라.
*** 단, 다음 노드의 순서는 inorder traverse에 준한다.
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
        Node(__int32 const data) : mData(data) {}
        __int32 GetNodeData() const;
        Node* GetLeftNode() const;
        void SetLeftNode(Node* const node);
        Node* GetRightNode() const;
        void SetRightNode(Node* const node);
        Node* GetParentNode() const;
        void SetParentNode(Node* const node);

    private:
        __int32 mData;
        Node* mLeftNode = nullptr;
        Node* mRightNode = nullptr;
        Node* mParentNode = nullptr;
    }; // end Node class

public:
    Node* GetTreeRoot() const;

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
    return this->mRoot;
}

int main()
{
    return 0;
}
