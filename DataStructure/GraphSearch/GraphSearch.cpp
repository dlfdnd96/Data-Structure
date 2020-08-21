/*
*** Graph 검색 DFS, BFS
*** 영상 보면서 다시 하기
*/
#include <iostream>
#include <vector>
#include <stack>
#include <exception>

using std::cout;
using std::endl;
using std::vector;
using std::stack;

template <typename QT>
class Queue
{
public:
    template <typename NT>
    class QueueNode
    {
    public:
        constexpr void SetNextNode(QueueNode* const node)
        {
            this->mNext = node;
        }
        constexpr QueueNode* GetNextNode() const
        {
            return this->mNext;
        }
        constexpr void SetQueueNodeData(NT const data)
        {
            this->mQueueNodeData = data;
        }
        constexpr NT GetQueueNodeData() const
        {
            return this->mQueueNodeData;
        }
        QueueNode(NT const data) : mQueueNodeData(data) {}

    private:
        NT mQueueNodeData;
        QueueNode<NT>* mNext = nullptr;
    }; // end Node class

public:
    constexpr void Add(const QT& data)
    {
        QueueNode<QT> inputNode(data);

        if (mEndQueuePointer != nullptr)
        {
            mEndQueuePointer->SetNextNode(&inputNode);
        }

        mEndQueuePointer = &inputNode;

        if (mFrontQueuePointer == nullptr)
        {
            mFrontQueuePointer = mEndQueuePointer;
        }
    }
    constexpr QT remove()
    {
        if (mFrontQueuePointer == nullptr)
        {
            throw std::runtime_error("Queue is empty!!");
        }

        QueueNode<QT>* deleteNode = mFrontQueuePointer;
        QT queueData = mFrontQueuePointer->GetQueueNodeData();
        mFrontQueuePointer = mFrontQueuePointer->GetNextNode();

        if (mFrontQueuePointer == nullptr)
        {
            mEndQueuePointer = nullptr;
        }

        delete deleteNode;

        return queueData;
    }
    constexpr QT Peek() const
    {
        if (mFrontQueuePointer == nullptr)
        {
            throw std::runtime_error("Queue is empty!!");
        }

        return mFrontQueuePointer->GetData();
    }
    constexpr bool IsEmpty() const
    {
        return mFrontQueuePointer == nullptr;
    }

private:
    QueueNode<QT>* mFrontQueuePointer = nullptr;
    QueueNode<QT>* mEndQueuePointer = nullptr;
}; // end Queue class

class Graph
{
public:
    class GraphNode
    {
    public:
        GraphNode() {}
        GraphNode(__int32 data) : mGraphNodeData(data), mMarked(false)
        {
            this->mAdjacent = new vector<GraphNode>();
        }
        constexpr void SetGraphNodeData(__int32 const data);
        constexpr __int32 GetGraphNodeData() const;
        vector<GraphNode>* GetAdjacentNode() const;
        constexpr void SetMarked(bool const mark);
        constexpr bool GetMarked() const;
        bool operator==(const GraphNode& node) const;

    private:
        __int32 mGraphNodeData = NULL;
        vector<GraphNode>* mAdjacent;
        bool mMarked = NULL;
    }; // end Node class

public:
    Graph(__int32 const size)
    {
        this->nodes = vector<GraphNode>(size);

        for (int index = 0; index < size; ++index)
        {
            nodes[index] = GraphNode(index);
        }
    }
    void AddEdge(__int32 const index1, __int32 const index2);
    void DFS();
    void DFSByIndex(__int32 index);
    void BFS();
    void BFSByIndex(__int32 index);
    void DFSRecursive();
    constexpr void DFSRecursiveByNode(GraphNode* node);
    void DFSRecursiveByIndex(__int32 const index);

private:
    vector<GraphNode> nodes;
}; // end Graph class

/* Getter, Setter */
constexpr void Graph::GraphNode::SetGraphNodeData(__int32 const data)
{
    this->mGraphNodeData = data;
}
constexpr __int32 Graph::GraphNode::GetGraphNodeData() const
{
    return this->mGraphNodeData;
}
vector<Graph::GraphNode>* Graph::GraphNode::GetAdjacentNode() const
{
    return this->mAdjacent;
}
constexpr void Graph::GraphNode::SetMarked(bool const mark)
{
    this->mMarked = mark;
}
constexpr bool Graph::GraphNode::GetMarked() const
{
    return this->mMarked;
}

/* Functions */
void Visit(const Graph::GraphNode& n)
{
    cout << n.GetGraphNodeData() << " ";
}

bool Graph::GraphNode::operator==(const GraphNode& node) const
{
    return this->GetGraphNodeData() == node.GetGraphNodeData();
}

void Graph::AddEdge(__int32 const index1, __int32 const index2)
{
    GraphNode node1 = nodes[index1];
    GraphNode node2 = nodes[index2];
    bool temp = false;

    //vectorIter = std::find(node1.GetAdjacentNode()->begin(), node1.GetAdjacentNode()->end(), node2);
    //if (vectorIter == node1.GetAdjacentNode()->end())
    //{
    //    node2.GetAdjacentNode()->push_back(node1);
    //}

    for (vector<GraphNode>::iterator nodeIterator = node1.GetAdjacentNode()->begin(); nodeIterator < node1.GetAdjacentNode()->end(); ++nodeIterator)
    {
        if (*nodeIterator == node2)
        {
            temp = true;
        }
    }

    if (!temp)
    {
        node1.GetAdjacentNode()->push_back(node2);
    }

    temp = false;
    for (vector<GraphNode>::iterator nodeIterator = node2.GetAdjacentNode()->begin(); nodeIterator < node2.GetAdjacentNode()->end(); ++nodeIterator)
    {
        if (*nodeIterator == node1)
        {
            temp = true;
        }
    }

    if (!temp)
    {
        node2.GetAdjacentNode()->push_back(node1);
    }
}

void Graph::DFS()
{
    DFSByIndex(0);
}

void Graph::DFSByIndex(__int32 const index)
{
    GraphNode& root = nodes[index];
    stack<GraphNode> stackNode;
    stackNode.push(root);
    root.SetMarked(true);

    while (!stackNode.empty())
    {
        GraphNode r = stackNode.top();
        stackNode.pop();

        for (vector<GraphNode>::iterator nodeIterator = r.GetAdjacentNode()->begin(); nodeIterator < r.GetAdjacentNode()->end(); ++nodeIterator)
        {
            GraphNode& temp = nodes[nodeIterator->GetGraphNodeData()];
            if (temp.GetMarked() == false)
            {
                temp.SetMarked(true);
                stackNode.push(temp);
            }
        }

        Visit(r);
    }
}

void Graph::BFS()
{
    BFSByIndex(0);
}

void Graph::BFSByIndex(__int32 index)
{
    GraphNode& root = nodes[index];
    Queue<GraphNode> queueNode;
    queueNode.Add(root);
    root.SetMarked(true);

    while (!queueNode.IsEmpty())
    {
        GraphNode r = queueNode.remove();

        for (GraphNode n : *(r.GetAdjacentNode()))
        {
            if (n.GetMarked() == false)
            {
                n.SetMarked(true);
                queueNode.Add(n);
            }
        }

        Visit(r);
    }
}

void Graph::DFSRecursive()
{
    DFSRecursiveByIndex(0);
}

constexpr void Graph::DFSRecursiveByNode(GraphNode* node)
{
    //if (node == nullptr)
    //{
    //    return;
    //}

    //node->SetMarked(true);
    //Visit(*node);

    //for (GraphNode n : node->GetAdjacentNode())
    //{
    //    if (node->GetMarked() == false)
    //    {
    //        DFSRecursiveByNode(node);
    //    }
    //}
}

void Graph::DFSRecursiveByIndex(__int32 const index)
{
    GraphNode node = nodes[index];
    DFSRecursiveByNode(&node);
}

int main()
{
    std::unique_ptr<Graph> uniqueGraphPointer = std::make_unique<Graph>(9);
    uniqueGraphPointer->AddEdge(0, 1);
    uniqueGraphPointer->AddEdge(1, 2);
    uniqueGraphPointer->AddEdge(1, 3);
    uniqueGraphPointer->AddEdge(2, 4);
    uniqueGraphPointer->AddEdge(2, 3);
    uniqueGraphPointer->AddEdge(3, 4);
    uniqueGraphPointer->AddEdge(3, 5);
    uniqueGraphPointer->AddEdge(5, 6);
    uniqueGraphPointer->AddEdge(5, 7);
    uniqueGraphPointer->AddEdge(6, 8);
    //uniqueGraphPointer->DFS();
    uniqueGraphPointer->BFS();
    //uniqueGraphPointer->DFSRecursive();
    //uniqueGraphPointer->DFSByIndex(3);
    //uniqueGraphPointer->BFSByIndex(3);
    //uniqueGraphPointer->DFSRecursiveByIndex(3);

    return 0;
}
