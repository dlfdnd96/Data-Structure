#include <iostream>

using namespace std;

struct LinkedList
{
	struct Node
	{
		int mNodeData;
		Node* mNextNode;
	};

	LinkedList() : mNodeHeader(new Node()) {}
	void AddNode(const int data);
	void DeleteNode(const int data);
	void Retrieve();

	Node* mNodeHeader;
};


void LinkedList::AddNode(const int data)
{
	Node* iter = mNodeHeader;
	Node* newNode = new Node();
	newNode->mNodeData = data;
	while (iter->mNextNode != nullptr)
	{
		iter = iter->mNextNode;
	}

	iter->mNextNode = newNode;
}

void LinkedList::DeleteNode(const int data)
{
	Node* iter = mNodeHeader;
	while (iter->mNextNode != nullptr)
	{
		if (iter->mNextNode->mNodeData == data)
		{
			iter->mNextNode = iter->mNextNode->mNextNode;
		}
		else
		{
			iter = iter->mNextNode;
		}
	}
}

void LinkedList::Retrieve()
{
	Node* iter = mNodeHeader->mNextNode;
	while (iter->mNextNode != nullptr)
	{
		cout << iter->mNodeData << " -> ";
		iter = iter->mNextNode;
	}

	cout << iter->mNodeData << endl;
}

int main()
{
	LinkedList n;
	n.AddNode(1);
	n.AddNode(2);
	n.AddNode(3);
	n.AddNode(4);
	n.Retrieve();
	n.DeleteNode(1);
	n.Retrieve();

	return 0;
}
