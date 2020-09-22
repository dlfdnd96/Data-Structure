#include <iostream>

using namespace std;


class Node
{
public:
    Node(int data) : mNodeData(data) {}
    void Append(int data)
    {
        Node* currentNode = this;
        Node* newNode = new Node(data);
        while (currentNode->mNextNode != nullptr)
        {
            currentNode = currentNode->mNextNode;
        }

        currentNode->mNextNode = newNode;
    };
    void Delete(int data)
    {
        Node* currentNode = this;
        while (currentNode->mNextNode != nullptr)
        {
            if (currentNode->mNextNode->mNodeData == data)
            {
                currentNode->mNextNode = currentNode->mNextNode->mNextNode;
            }
            else
            {
                currentNode = currentNode->mNextNode;
            }
        }
    }
    void Retrieve()
    {
        Node* currentNode = this;
        while (currentNode->mNextNode != nullptr)
        {
            cout << currentNode->mNodeData << " -> ";
            currentNode = currentNode->mNextNode;
        }

        cout << currentNode->mNodeData << endl;
    }

public:
    int mNodeData;
    Node* mNextNode;
};

int main()
{
    Node* head = new Node(1);
    head->Append(2);
    head->Append(3);
    head->Append(4);
    head->Retrieve();
    head->Delete(2);
    head->Retrieve();
    head->Delete(3);
    head->Retrieve();

    return 0;
}
