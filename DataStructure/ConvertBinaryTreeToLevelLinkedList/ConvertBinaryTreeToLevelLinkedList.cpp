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

template <typename T>
struct LinkedList
{
    struct LinkedListNode
    {
        LinkedListNode() : mNodeData(NULL), mNextNode(nullptr) {}

        T mNodeData;
        LinkedListNode* mNextNode;
    };

    LinkedList() : mLinkedListHeader(new LinkedListNode()) {}
    void AddNode(const T data) const
    {
        LinkedListNode* iter = mLinkedListHeader;
        LinkedListNode* addNode = new LinkedListNode();
        addNode->mNodeData = data;
        while (iter->mNextNode != nullptr)
        {
            iter = iter->mNextNode;
        }

        iter->mNextNode = addNode;
    }
    int GetNodeSize() const
    {
        int count = 0;
        LinkedListNode* iter = mLinkedListHeader;
        while (iter->mNextNode != nullptr)
        {
            iter = iter->mNextNode;
            ++count;
        }
        
        return (++count);
    }
    LinkedListNode* GetLinkedListHeader() const
    {
        return this->mLinkedListHeader;
    }

    LinkedListNode* mLinkedListHeader;
}; // end LinkedList struct

class Tree
{
public:
    class TreeNode
    {
    public:
        TreeNode(const int data) : mTreeNodeData(data) {}
        constexpr int GetTreeNodeData() const;
        void SetTreeNodeData(int const data);
        constexpr TreeNode* GetTreeNodeLeft() const;
        void SetTreeNodeLeft(TreeNode* const node);
        constexpr TreeNode* GetTreeNodeRight() const;
        void SetTreeNodeRight(TreeNode* const node);

    private:
        int mTreeNodeData;
        TreeNode* mTreeNodeLeft;
        TreeNode* mTreeNodeRight;
    }; // end Node class

public:
    Tree(const int size)
    {
        mTreeRoot = MakeBSTRecursive(0, size - 1);
    }
    constexpr TreeNode* GetRootNode() const;
    constexpr TreeNode* MakeBSTRecursive(const int start, const int end);
    std::vector<LinkedList<TreeNode>>* InitBST();
    void BSTRecursive(TreeNode* root, std::vector<LinkedList<TreeNode>>* nodeList, const int level);
    std::vector<LinkedList<TreeNode>>* BSTUsingBFS();
    void PrintList(std::vector<LinkedList<TreeNode>>& resultNodeList) const;

private:
    TreeNode* mTreeRoot;

}; // end Tree class

/* Getter, Setter */
constexpr int Tree::TreeNode::GetTreeNodeData() const
{
    return this->mTreeNodeData;
}
void Tree::TreeNode::SetTreeNodeData(int const data)
{
    this->mTreeNodeData = data;
}
constexpr Tree::TreeNode* Tree::TreeNode::GetTreeNodeLeft() const
{
    return this->mTreeNodeLeft;
}
void Tree::TreeNode::SetTreeNodeLeft(TreeNode* const node)
{
    this->mTreeNodeLeft = node;
}
constexpr Tree::TreeNode* Tree::TreeNode::GetTreeNodeRight() const
{
    return this->mTreeNodeRight;
}
void Tree::TreeNode::SetTreeNodeRight(TreeNode* const node)
{
    this->mTreeNodeRight = node;
}
constexpr Tree::TreeNode* Tree::GetRootNode() const
{
    return this->mTreeRoot;
}

/* Tree class functions */
constexpr Tree::TreeNode* Tree::MakeBSTRecursive(const int start, const int end)
{
    if (start > end)
    {
        return nullptr;
    }

    unsigned __int32 mid = (start + end) / 2;
    TreeNode* curruntNode = new TreeNode(mid);
    curruntNode->SetTreeNodeLeft(MakeBSTRecursive(start, mid - 1));
    curruntNode->SetTreeNodeRight(MakeBSTRecursive(mid + 1, end));

    return curruntNode;
}

std::vector<LinkedList<Tree::TreeNode>>* Tree::InitBST()
{
    std::vector<LinkedList<Tree::TreeNode>>* nodeLists = new std::vector<LinkedList<Tree::TreeNode>>();
    BSTRecursive(mTreeRoot, nodeLists, 0);

    return nodeLists;
}

void Tree::BSTRecursive(TreeNode* root, std::vector<LinkedList<Tree::TreeNode>>* nodeList, const int level)
{
    if (root == nullptr)
    {
        return;
    }

    LinkedList<Tree::TreeNode>* list = nullptr;
    if (nodeList->size() == level)
    {
        list = new LinkedList<TreeNode>();
        nodeList->emplace_back(*list);
    }
    else
    {
        list = &((*nodeList)[level]);
    }
    list->AddNode(*root);
    BSTRecursive(root->GetTreeNodeLeft(), nodeList, level + 1);
    BSTRecursive(root->GetTreeNodeRight(), nodeList, level + 1);
}

std::vector<LinkedList<Tree::TreeNode>>* Tree::BSTUsingBFS()
{
    std::vector<LinkedList<Tree::TreeNode>>* resultNodeList = new std::vector<LinkedList<Tree::TreeNode>>();
    LinkedList<Tree::TreeNode>* currentLevelLinkedList = new LinkedList<Tree::TreeNode>();
    if (mTreeRoot != nullptr)
    {
        currentLevelLinkedList->AddNode(*mTreeRoot);
    }

    while (currentLevelLinkedList->GetNodeSize() > 0)
    {
        resultNodeList->emplace_back(*currentLevelLinkedList);
        LinkedList<Tree::TreeNode> parents = *currentLevelLinkedList;
        currentLevelLinkedList = new LinkedList<Tree::TreeNode>();
        LinkedList<Tree::TreeNode>::LinkedListNode* iter = parents.GetLinkedListHeader();
        while (iter->mNextNode != nullptr)
        {
            TreeNode parent = iter->mNodeData;
            if (parent.GetTreeNodeLeft() != nullptr)
            {
                currentLevelLinkedList->AddNode(*(parent.GetTreeNodeLeft()));
            }
            if (parent.GetTreeNodeRight() != nullptr)
            {
                currentLevelLinkedList->AddNode(*(parent.GetTreeNodeRight()));
            }
        }
    }

    return resultNodeList;
}

void Tree::PrintList(std::vector<LinkedList<Tree::TreeNode>>& resultNodeList) const
{
    for (LinkedList<Tree::TreeNode> nodeList : resultNodeList)
    {
        LinkedList<Tree::TreeNode>::LinkedListNode* iter = nodeList.GetLinkedListHeader()->mNextNode;
        while (iter->mNextNode != nullptr)
        {
            cout << iter->mNodeData.GetTreeNodeData() << " ";
            iter = iter->mNextNode;
        }
        cout << iter->mNodeData.GetTreeNodeData() << " " << endl;
    }
}

int main()
{
    Tree t(10);
    t.PrintList(*(t.InitBST()));

    return 0;
}
