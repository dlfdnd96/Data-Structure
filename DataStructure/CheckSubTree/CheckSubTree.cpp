/*
*** 크기가 매우 큰 두개의 이진트리 T1, T2가 있다.
*** T1 > T2이고 T2가 T1의 서브트리인지 확인하는
*** 알고리즘을 구현하시오. T2의 루트노드의 값이 T1에 존재하고,
*** 그 노드를 기준으로 줄기를 잘라 냈을 때, T2의 값과 구조가 같으면
*** 서브트리이다.
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
*/

#include <iostream>

struct Tree
{
    struct Node
    {
        /* Funciton */
        Node(int data) : mNodeData(data) {}

        /* Variable */
        int mNodeData;
        Node* mLeftNode;
        Node* mRightNode;
    };

    /* Function */
    Tree() {}
    Tree(int size)
    {
        mTreeRoot = MakeBST(0, size);
    }
    Node* MakeBST(int start, int end);
    bool ContainsTree(Node* t1, Node* t2);
    bool SubTree(Node* t1, Node* t2);
    bool MatchTree(Node* t1, Node* t2);

    /* Variable */
    Node* mTreeRoot;
};

Tree::Node* Tree::MakeBST(int start, int end)
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

bool Tree::ContainsTree(Node* t1, Node* t2)
{
    if (t2 == nullptr)
    {
        return false;
    }

    return SubTree(t1, t2);
}

bool Tree::SubTree(Node* t1, Node* t2)
{
    if (t1 == nullptr)
    {
        return false;
    }
    else if (t1->mNodeData == t2->mNodeData && MatchTree(t1, t2))
    {
        return true;
    }
    
    return SubTree(t1->mLeftNode, t2) || SubTree(t1->mRightNode, t2);
}

bool Tree::MatchTree(Node* t1, Node* t2)
{
    if (t1 == nullptr && t2 == nullptr)
    {
        return true;
    }
    else if (t1 == nullptr || t2 == nullptr)
    {
        return false;
    }
    else if (t1->mNodeData != t2->mNodeData)
    {
        return false;
    }
    else
    {
        return MatchTree(t1->mLeftNode, t2->mLeftNode) && MatchTree(t1->mRightNode, t2->mRightNode);
    }
}

int main()
{
    Tree t1;
    Tree t2;
    bool result;
    t1.mTreeRoot = t1.MakeBST(0, 9);
    t2.mTreeRoot = t2.MakeBST(5, 9);
    result = t1.ContainsTree(t1.mTreeRoot, t2.mTreeRoot);
    std::cout << std::boolalpha << result << std::endl;

    t2.mTreeRoot = t2.MakeBST(7, 9);
    result = t1.ContainsTree(t1.mTreeRoot, t2.mTreeRoot);
    std::cout << std::boolalpha << result << std::endl;

    return 0;
}
