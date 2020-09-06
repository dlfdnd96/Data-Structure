/*
*** Graph °Ë»ö DFS, BFS
***   0
***  /
*** 1 -- 3     7
*** |   /| \  /
*** |  / |  5
*** | /  |   \
*** 2 -- 4    \
***            6 - 8
*** =======================
*** DFS(0): 0 1 3 5 7 6 8 4 2
*** BFS(0): 0 1 2 3 4 5 6 7 8
*** DFSRecursive(0): 0 1 2 4 3 5 6 8 7
*** DFS(3): 3 5 7 6 8 4 2 1 0
*** BFS(3): 3 1 2 4 5 0 6 7 8
*** DFSRecursive(3): 3 1 0 2 4 5 6 8 7
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
        QueueNode<QT>* inputNode = new QueueNode<QT>(data);

        if (mEndQueuePointer != nullptr)
        {
            mEndQueuePointer->SetNextNode(inputNode);
        }

        mEndQueuePointer = inputNode;

        if (mFrontQueuePointer == nullptr)
        {
            mFrontQueuePointer = mEndQueuePointer;
        }
    }
    constexpr QT Remove()
    {
        if (mFrontQueuePointer == nullptr)
        {
            throw std::runtime_error("Queue is empty!!");
        }

        QueueNode<QT>* deleteQueueNode = mFrontQueuePointer;
        QT queueData = mFrontQueuePointer->GetQueueNodeData();
        mFrontQueuePointer = mFrontQueuePointer->GetNextNode();

        if (mFrontQueuePointer == nullptr)
        {
            mEndQueuePointer = nullptr;
        }

        delete deleteQueueNode;

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
        vector<GraphNode>* mAdjacent = nullptr;
        bool mMarked = NULL;
    }; // end Node class

public:
    Graph(__int32 const size)
    {
        this->nodes = new vector<GraphNode>(size);

        for (int index = 0; index < size; ++index)
        {
            this->nodes[0][index] = GraphNode(index);
        }
    }
    ~Graph()
    {
        delete nodes;
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
    vector<GraphNode>* nodes;
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
    GraphNode& node1 = nodes[0][index1];
    GraphNode& node2 = nodes[0][index2];
    bool isExistedNode = false;

    for (const GraphNode& iterNode : *(node1.GetAdjacentNode()))
    {
        if (iterNode == node2)
        {
            isExistedNode = true;
        }
    }

    if (!isExistedNode)
    {
        node1.GetAdjacentNode()->emplace_back(node2);
    }

    isExistedNode = false;
    for (const GraphNode& iterNode : *(node2.GetAdjacentNode()))
    {
        if (iterNode == node1)
        {
            isExistedNode = true;
        }
    }

    if (!isExistedNode)
    {
        node2.GetAdjacentNode()->emplace_back(node1);
    }
}

void Graph::DFS()
{
    DFSByIndex(0);
}

void Graph::DFSByIndex(__int32 const index)
{
    GraphNode& root = nodes[0][index];
    root.SetMarked(true);
    stack<GraphNode>* stackNode = new stack<GraphNode>;
    stackNode->push(root);

    while (!stackNode->empty())
    {
        GraphNode stackTopNode = stackNode->top();
        stackNode->pop();

        for (const GraphNode& iterNode : *(stackTopNode.GetAdjacentNode()))
        {
            GraphNode& adjacentNode = nodes[0][iterNode.GetGraphNodeData()];
            if (!adjacentNode.GetMarked())
            {
                adjacentNode.SetMarked(true);
                stackNode->push(adjacentNode);
            }
        }

        Visit(stackTopNode);
    }

    delete stackNode;
}

void Graph::BFS()
{
    BFSByIndex(0);
}

void Graph::BFSByIndex(__int32 index)
{
    GraphNode& root = nodes[0][index];
    root.SetMarked(true);
    Queue<GraphNode>* queueNode = new Queue<GraphNode>();
    queueNode->Add(root);

    while (!queueNode->IsEmpty())
    {
        GraphNode queueRemoveNode = queueNode->Remove();

        for (const GraphNode& iterNode : *(queueRemoveNode.GetAdjacentNode()))
        {
            GraphNode& adjacentNode = nodes[0][iterNode.GetGraphNodeData()];
            if (!adjacentNode.GetMarked())
            {
                adjacentNode.SetMarked(true);
                queueNode->Add(adjacentNode);
            }
        }

        Visit(queueRemoveNode);
    }

    delete queueNode;
}

void Graph::DFSRecursive()
{
    DFSRecursiveByIndex(0);
}

constexpr void Graph::DFSRecursiveByNode(GraphNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    node->SetMarked(true);
    Visit(*node);

    for (const GraphNode& iterNode : *(node->GetAdjacentNode()))
    {
        GraphNode& adjacentNode = nodes[0][iterNode.GetGraphNodeData()];
        if (!adjacentNode.GetMarked())
        {
            DFSRecursiveByNode(&adjacentNode);
        }
    }
}

void Graph::DFSRecursiveByIndex(__int32 const index)
{
    GraphNode& graphNode = nodes[0][index];
    DFSRecursiveByNode(&graphNode);
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

    /* DFS, BFS Å½»ö */
    uniqueGraphPointer->DFS();
    //uniqueGraphPointer->BFS();
    //uniqueGraphPointer->DFSRecursive();
    //uniqueGraphPointer->DFSByIndex(3);
    //uniqueGraphPointer->BFSByIndex(3);
    //uniqueGraphPointer->DFSRecursiveByIndex(3);

    return 0;
}
