/*
*** Graph에서 두 개의 노드가 서로 찾아갈 수 있는 경로가
*** 있는지 확인하라.
*** 영상 보고 다시 공부 필요
*/
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Graph
{
public:
    class Node
    {
    public:
        Node() {}
        Node(__int32 const data) : mData(data), mMarked(false)
        {
            mAdjacent = new vector<Node>();
        }
        void SetGraphNodeData(__int32 const data);
        __int32 GetGraphNodeData() const;
        void SetMarked(bool const mark);
        bool GetMarked() const;
        void SetAdjacentNode(vector<Node>* const adjacentNode);
        vector<Node>* GetAdjacentNode() const;

    private:
        __int32 mData;
        bool mMarked;
        vector<Node>* mAdjacent;
    }; // end Node class

public:
    Graph(__int32 const size)
    {
        nodes = new Node[size];

        for (int index = 0; index < size; ++index)
        {
            nodes[index] = Node(index);
        }
    }
    void AddEdge(__int32 const i1, __int32 const i2);
    void InitMarks();

private:
    Node* nodes;
}; // end Graph class

void Graph::Node::SetGraphNodeData(__int32 const data)
{
    this->mData = data;
}
__int32 Graph::Node::GetGraphNodeData() const
{
    return this->mData;
}
void Graph::Node::SetMarked(bool const mark)
{
    this->mMarked = mark;
}
bool Graph::Node::GetMarked() const
{
    return this->mMarked;
}
void Graph::Node::SetAdjacentNode(vector<Node>* const adjacentNode)
{
    this->mAdjacent = adjacentNode;
}
vector<Graph::Node>* Graph::Node::GetAdjacentNode() const
{
    return this->mAdjacent;
}

void Graph::AddEdge(__int32 const i1, __int32 const i2)
{
    Node n1 = nodes[i1];
    Node n2 = nodes[i2];

    if (std::find
    (
        n1.GetAdjacentNode()->begin(),
        n1.GetAdjacentNode()->end(),
        n2
    ) == n1.GetAdjacentNode()->end()
        )
    {
        n1.GetAdjacentNode()->push_back(n2);
    }
    if (std::find
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

void Graph::InitMarks()
{
    for (auto const& nodes)
    {

    }
}

int main()
{
    std::cout << "Hello World!\n";
}
