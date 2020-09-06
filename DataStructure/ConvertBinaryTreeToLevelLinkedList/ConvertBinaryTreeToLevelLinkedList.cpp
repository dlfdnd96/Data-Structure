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

class LinkedList
{
public:
    class LinkedListNode
    {
    public:
        constexpr __int32 GetLinkedListData() const;
        constexpr void SetLinkedListData(const __int32 data);
        constexpr LinkedListNode* GetLinkedListNodeNext() const;
        constexpr void SetLinkedListNodeNext(LinkedListNode* const node);

    private:
        __int32 mLinkedListData;
        LinkedListNode* mLinkedListNodeNext;
    }; // end LinkedListNode Node

public:
    LinkedList()
    {
        mLinkedListHeader = new LinkedListNode();
    }
    constexpr LinkedListNode* GetLinkedListHeader() const;
    void AddLinkedListNode(__int32 data);
    constexpr void DeleteLinkedListNode(__int32 data);
    void Retrieve();
    constexpr unsigned __int32 GetLinkedListSize() const;

private:
    LinkedListNode* mLinkedListHeader;

}; // end LinkedList class

class Tree
{
public:
    class TreeNode
    {
    public:
        TreeNode(const __int32 data) : mTreeNodeData(data) {}
        constexpr __int32 GetTreeNodeData() const;
        constexpr void SetTreeNodeData(const __int32 data);
        constexpr TreeNode* GetTreeNodeLeft() const;
        constexpr void SetTreeNodeLeft(TreeNode* const node);
        constexpr TreeNode* GetTreeNodeRight() const;
        constexpr void SetTreeNodeRight(TreeNode* const node);

    private:
        __int32 mTreeNodeData;
        TreeNode* mTreeNodeLeft = nullptr;
        TreeNode* mTreeNodeRight = nullptr;
    }; // end TreeNode class

public:
    Tree(const __int32 size)
    {
        mRoot = MakeBSTRecursive(0, size - 1);
    }
    constexpr TreeNode* GetRootNode() const;
    constexpr TreeNode* MakeBSTRecursive(const __int32 start, const __int32 end);
    vector<LinkedList>* InitBST();
    void BSTRecursive(const TreeNode* root, vector<LinkedList>* nodeList, const __int32 level);
    vector<LinkedList>* BSTUsingBFS();

private:
    TreeNode* mRoot;

}; // end Tree class

/* Getter, Setter */
constexpr __int32 LinkedList::LinkedListNode::GetLinkedListData() const
{
    return this->mLinkedListData;
}
constexpr void LinkedList::LinkedListNode::SetLinkedListData(const __int32 data)
{
    this->mLinkedListData = data;
}
constexpr LinkedList::LinkedListNode* LinkedList::LinkedListNode::GetLinkedListNodeNext() const
{
    return this->mLinkedListNodeNext;
}
constexpr void LinkedList::LinkedListNode::SetLinkedListNodeNext(LinkedListNode* const node)
{
    this->mLinkedListNodeNext = node;
}
constexpr LinkedList::LinkedListNode* LinkedList::GetLinkedListHeader() const
{
    return this->mLinkedListHeader;
}
constexpr __int32 Tree::TreeNode::GetTreeNodeData() const
{
    return this->mTreeNodeData;
}
constexpr void Tree::TreeNode::SetTreeNodeData(const __int32 data)
{
    this->mTreeNodeData = data;
}
constexpr Tree::TreeNode* Tree::TreeNode::GetTreeNodeLeft() const
{
    return this->mTreeNodeLeft;
}
constexpr void Tree::TreeNode::SetTreeNodeLeft(TreeNode* const node)
{
    this->mTreeNodeLeft = node;
}
constexpr Tree::TreeNode* Tree::TreeNode::GetTreeNodeRight() const
{
    return this->mTreeNodeRight;
}
constexpr void Tree::TreeNode::SetTreeNodeRight(TreeNode* const node)
{
    this->mTreeNodeRight = node;
}
constexpr Tree::TreeNode* Tree::GetRootNode() const
{
    return this->mRoot;
}

/* LinkedList class functions */
void LinkedList::AddLinkedListNode(__int32 data)
{
    LinkedListNode* insertNode = new LinkedListNode();
    insertNode->SetLinkedListData(data);
    
    LinkedListNode* iterNode = mLinkedListHeader;
    while (iterNode->GetLinkedListNodeNext() != nullptr)
    {
        iterNode = iterNode->GetLinkedListNodeNext();
    }

    iterNode->SetLinkedListNodeNext(insertNode);
}

constexpr void LinkedList::DeleteLinkedListNode(__int32 data)
{
    LinkedListNode* iterNode = mLinkedListHeader;
    while (iterNode->GetLinkedListNodeNext() != nullptr)
    {
        if (iterNode->GetLinkedListData() == data)
        {
            LinkedListNode* deleteNode = iterNode->GetLinkedListNodeNext();
            iterNode->SetLinkedListNodeNext(iterNode->GetLinkedListNodeNext()->GetLinkedListNodeNext());

            delete deleteNode;
        }
        else
        {
            iterNode = iterNode->GetLinkedListNodeNext();
        }
    }
}

void LinkedList::Retrieve()
{
    LinkedListNode* iterNode = mLinkedListHeader->GetLinkedListNodeNext();
    while (iterNode->GetLinkedListNodeNext() != nullptr)
    {
        cout << iterNode->GetLinkedListData() << " ";
        iterNode = iterNode->GetLinkedListNodeNext();
    }

    cout << iterNode->GetLinkedListData() << endl;
}

constexpr unsigned __int32 LinkedList::GetLinkedListSize() const
{
    if (mLinkedListHeader->GetLinkedListNodeNext() == nullptr)
    {
        return 0;
    }

    LinkedListNode* nodeIter = mLinkedListHeader->GetLinkedListNodeNext();
    unsigned __int32 count = 1;
    while (nodeIter->GetLinkedListNodeNext() != nullptr)
    {
        ++count;
        nodeIter = nodeIter->GetLinkedListNodeNext();
    }

    return count;
}

/* Tree class functions */
constexpr Tree::TreeNode* Tree::MakeBSTRecursive(const __int32 start, const __int32 end)
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

vector<LinkedList>* Tree::InitBST()
{
    vector<LinkedList>* nodeLists = new vector<LinkedList>();
    BSTRecursive(mRoot, nodeLists, 0);

    return nodeLists;
}

void Tree::BSTRecursive(const TreeNode* root, vector<LinkedList>* nodeList, const __int32 level)
{
    if (root == nullptr)
    {
        return;
    }

    LinkedList* list = nullptr;
    if (nodeList->size() == level)
    {
        list = new LinkedList();
        nodeList->emplace_back(*list);
    }
    else
    {
        list = &nodeList[0][level];
    }
    list->AddLinkedListNode(root->GetTreeNodeData());
    BSTRecursive(root->GetTreeNodeLeft(), nodeList, level + 1);
    BSTRecursive(root->GetTreeNodeRight(), nodeList, level + 1);
}

vector<LinkedList>* Tree::BSTUsingBFS()
{
    vector<LinkedList>* resultNodeList = new vector<LinkedList>();
    LinkedList* currentLevelLinkedList = new LinkedList();
    if (mRoot != nullptr)
    {
        currentLevelLinkedList->AddLinkedListNode(mRoot->GetTreeNodeData());
    }

    //vector<LinkedList>::iterator iterVector = resultNodeList->begin();
    TreeNode* currentNode = mRoot;
    LinkedList::LinkedListNode* iterNode = currentLevelLinkedList->GetLinkedListHeader()->GetLinkedListNodeNext();
    while (currentLevelLinkedList->GetLinkedListSize() > 0)
    {
        resultNodeList->emplace_back(*currentLevelLinkedList);
        while (iterNode != nullptr)
        {
            TreeNode& parentNode = *currentNode;
            currentLevelLinkedList = new LinkedList();
            if (parentNode.GetTreeNodeLeft() != nullptr)
            {
                currentLevelLinkedList->AddLinkedListNode(parentNode.GetTreeNodeLeft()->GetTreeNodeData());
            }
            if (parentNode.GetTreeNodeRight() != nullptr)
            {
                currentLevelLinkedList->AddLinkedListNode(parentNode.GetTreeNodeRight()->GetTreeNodeData());
            }
            
            iterNode = iterNode->GetLinkedListNodeNext();
            currentNode = 
        }

        iterNode = currentLevelLinkedList->GetLinkedListHeader()->GetLinkedListNodeNext();
        if (currentNode->GetTreeNodeLeft() != nullptr)
        {
            currentNode = currentNode->GetTreeNodeLeft();
        }
        else if (currentNode->GetTreeNodeRight() != nullptr)
        {
            currentNode = currentNode->GetTreeNodeRight();
        }
    }

    return resultNodeList;
}

void PrintList(vector<LinkedList>& resultNodeList)
{
    for (LinkedList nodeList : resultNodeList)
    {
        nodeList.Retrieve();
    }
}

int main()
{
    std::unique_ptr<Tree> uniqueTreePointer = std::make_unique<Tree>(10);
    PrintList(*uniqueTreePointer->BSTUsingBFS());

    return 0;
}
