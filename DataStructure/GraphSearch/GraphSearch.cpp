/*
*** Graph 검색 DFS, BFS
*** 영상 보면서 다시 하기
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <stack>
#include <exception>

using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::iterator;

template <typename QT>
class Queue
{
public:
    template <typename NT>
    class Node
    {
    public:
        constexpr void SetNextNode(Node* const node)
        {
            this->mNext = node;
        }
        constexpr Node* GetNextNode() const
        {
            return this->mNext;
        }
        void SetQueueNodeData(NT const data)
        {
            this->mQueueNodeData = data;
        }
        NT GetQueueNodeData() const
        {
            return this->mQueueNodeData;
        }
        Node(NT const data) : mQueueNodeData(data) {}

    private:
        NT mQueueNodeData;
        Node<NT>* mNext = nullptr;
    }; // end Node class

public:
    void Add(QT& const data)
    {
        Node<QT>* inputNode = new Node<QT>(data);

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
    constexpr QT remove()
    {
        if (mFrontQueuePointer == nullptr)
        {
            throw std::runtime_error("Queue is empty!!");
        }

        Node<QT>* deleteNode = mFrontQueuePointer;
        QT queueData = mFrontQueuePointer->GetData();
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
    Node<QT>* mFrontQueuePointer;
    Node<QT>* mEndQueuePointer;
}; // end Queue class

class Graph
{
public:
    class Node
    {
    public:
        Node() {}
        Node(__int32 data) : mGraphNodeData(data), mMarked(false)
        {
            mAdjacent = new vector<Node>();
        }
        ~Node()
        {
            delete mAdjacent;
        }
        void SetGraphNodeData(__int32 const data);
        __int32 GetGraphNodeData() const;
        vector<Node>* GetAdjacentNode() const;
        void SetMarked(bool const mark);
        bool GetMarked() const;

    private:
        __int32 mGraphNodeData;
        vector<Node>* mAdjacent;
        bool mMarked;
    }; // end Node class

public:
    Graph(__int32 const size)
    {
        this->nodes = new Node[size];

        for (int index = 0; index < size; ++index)
        {
            nodes[index] = Node(index);
        }
    }
    ~Graph()
    {
        delete[] this->nodes;
    }
    void AddEdge(__int32 const i1, __int32 const i2);
    void DFS();
    void DFS(__int32 index);
    void BFS();
    void BFS(__int32 index);

private:
    Node* nodes;
}; // end Graph class

void Graph::Node::SetGraphNodeData(__int32 const data)
{
    this->mGraphNodeData = data;
}
__int32 Graph::Node::GetGraphNodeData() const
{
    return this->mGraphNodeData;
}
vector<Graph::Node>* Graph::Node::GetAdjacentNode() const
{
    return this->mAdjacent;
}
void Graph::Node::SetMarked(bool const mark)
{
    this->mMarked = mark;
}
bool Graph::Node::GetMarked() const
{
    return this->mMarked;
}

void Graph::AddEdge(__int32 const index1, __int32 const index2)
{
    Node n1 = nodes[index1];
    Node n2 = nodes[index2];

    if (
        std::find
        (
            n1.GetAdjacentNode()->begin(),
            n1.GetAdjacentNode()->end(),
            n2
        ) == n1.GetAdjacentNode()->end()
        )
    {
        n1.GetAdjacentNode()->push_back(n2);
    }
    if (
        std::find
        (
            n2.GetAdjacentNode()->begin(),
            n2.GetAdjacentNode()->end(),
            n1
        ) == n2.GetAdjacentNode()->end()
        )
    {
        n2.GetAdjacentNode()->push_back(n1);
    }
}

void Graph::DFS()
{
    DFS(0);
}

void Graph::DFS(__int32 const index)
{
    Node root = nodes[index];
    stack<Node>* stackNode = new stack<Node>();
    stackNode->push(root);
    root.SetMarked(true);

    while (!stackNode->empty())
    {
        Node r = stackNode->top();
        stackNode->pop();

        for (const auto& n : r.GetAdjacentNode())
        {
            if (n.GetMarked() == false)
            {
                n.SetMarked(true);
                stackNode->push(n);
            }
        }

        Visit(r);
    }
}

void Graph::BFS()
{
    BFS(0);
}

void Graph::BFS(__int32 index)
{
    Node root = nodes[index];
    Queue<Node>* queueNode = new Queue<Node>();
    queueNode->Add(root);
    root.SetMarked(true);

    while (!queueNode->IsEmpty())
    {
        Node r = queueNode->remove();

        for (const auto& n : r.GetAdjacentNode())
        {
            if (n.GetMarked() == false)
            {
                n.SetMarked(true);
                stackNode->push(n);
            }
        }

        Visit(r);
    }
}

void Visit(Graph::Node& n)
{
    cout << n.GetGraphNodeData() << " ";
}

int main()
{
    return 0;
}
