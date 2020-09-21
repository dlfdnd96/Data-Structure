/*
*** 이진트리의 노드들을 각 레벨별로 Linked List에 담는 알고리즘을 구현하시오.
*** 예를 들어, 5개의 depth를 가지는 tree라면 5개의 Linked List를 만들어야 함.
***             (4)
***             /  \
***            /    \
***           /      \
***          /        \
***       (1)         (7)
***      /   \       /   \
***    (0)    (2)  (5)   (8)
***             \    \     \
***             (3)  (6)   (9)
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
        Node(const int data) : mTreeNodeData(data) {}
        constexpr int GetTreeNodeData() const;
        void SetTreeNodeData(int const data);
        constexpr Node* GetTreeNodeLeft() const;
        void SetTreeNodeLeft(Node* const node);
        constexpr Node* GetTreeNodeRight() const;
        void SetTreeNodeRight(Node* const node);

    private:
        int mTreeNodeData;
        Node* mTreeNodeLeft;
        Node* mTreeNodeRight;
    }; // end Node class

public:
    Tree(const int size)
    {
        mTreeRoot = MakeBSTRecursive(0, size - 1);
    }
    constexpr Node* GetRootNode() const;
    constexpr Node* MakeBSTRecursive(const int start, const int end);
    vector<vector<Node>>* InitBST();
    void BSTRecursive(const Node* root, vector<vector<Node>>* nodeList, const int level);
    vector<vector<Node>>* BSTUsingBFS();
    void PrintList(vector<vector<Tree::Node>>& resultNodeList) const;

private:
    Node* mTreeRoot;

}; // end Tree class

/* Getter, Setter */
constexpr int Tree::Node::GetTreeNodeData() const
{
    return this->mTreeNodeData;
}
void Tree::Node::SetTreeNodeData(int const data)
{
    this->mTreeNodeData = data;
}
constexpr Tree::Node* Tree::Node::GetTreeNodeLeft() const
{
    return this->mTreeNodeLeft;
}
void Tree::Node::SetTreeNodeLeft(Node* const node)
{
    this->mTreeNodeLeft = node;
}
constexpr Tree::Node* Tree::Node::GetTreeNodeRight() const
{
    return this->mTreeNodeRight;
}
void Tree::Node::SetTreeNodeRight(Node* const node)
{
    this->mTreeNodeRight = node;
}
constexpr Tree::Node* Tree::GetRootNode() const
{
    return this->mTreeRoot;
}

/* Tree class functions */
constexpr Tree::Node* Tree::MakeBSTRecursive(const int start, const int end)
{
    if (start > end)
    {
        return nullptr;
    }

    unsigned __int32 mid = (start + end) / 2;
    Node* curruntNode = new Node(mid);
    curruntNode->SetTreeNodeLeft(MakeBSTRecursive(start, mid - 1));
    curruntNode->SetTreeNodeRight(MakeBSTRecursive(mid + 1, end));

    return curruntNode;
}

vector<vector<Tree::Node>>* Tree::InitBST()
{
    vector<vector<Tree::Node>>* nodeLists = new vector<vector<Tree::Node>>();
    BSTRecursive(mTreeRoot, nodeLists, 0);

    return nodeLists;
}

void Tree::BSTRecursive(const Node* root, vector<vector<Tree::Node>>* nodeList, const int level)
{
    if (root == nullptr)
    {
        return;
    }

    vector<Tree::Node>* list = nullptr;
    if (nodeList->size() == level)
    {
        list = new vector<Node>();
        nodeList->emplace_back(*list);
    }
    else
    {
        list = &(*nodeList)[level];
    }
    list->emplace_back(root);
    BSTRecursive(root->GetTreeNodeLeft(), nodeList, level + 1);
    BSTRecursive(root->GetTreeNodeRight(), nodeList, level + 1);
}

vector<vector<Tree::Node>>* Tree::BSTUsingBFS()
{
    vector<vector<Tree::Node>>* resultNodeList = new vector<vector<Tree::Node>>();
    vector<Tree::Node>* currentLevelLinkedList = new vector<Tree::Node>();
    if (mTreeRoot != nullptr)
    {
        currentLevelLinkedList->emplace_back(mTreeRoot);
    }

    while (currentLevelLinkedList->size() > 0)
    {
        resultNodeList->emplace_back(currentLevelLinkedList);
        vector<Tree::Node> parents = *currentLevelLinkedList;
        currentLevelLinkedList = new vector<Tree::Node>();
        for (Tree::Node parent : parents)
        {
            if (parent.GetTreeNodeLeft() != nullptr)
            {
                currentLevelLinkedList->emplace_back(parent.GetTreeNodeLeft());
            }
            if (parent.GetTreeNodeRight() != nullptr)
            {
                currentLevelLinkedList->emplace_back(parent.GetTreeNodeRight());
            }
        }
    }

    return resultNodeList;
}

void Tree::PrintList(vector<vector<Tree::Node>>& resultNodeList) const
{
    for (vector<Tree::Node> nodeList : resultNodeList)
    {
        for (Tree::Node node : nodeList)
        {
            cout << node.GetTreeNodeData() << " ";
        }
        cout << endl;
    }
}

int main()
{
    Tree t(10);
    t.PrintList(t.InitBST());

    return 0;
}
