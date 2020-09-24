#include <iostream>

using namespace std;

template <typename T>
struct LinkedList
{
	struct Node
	{
		T mNodeData;
		Node* mNextNode;
	};

	LinkedList() : mLinkedListHeader(new Node()) {}
	void AddNode(T data)
	{
		Node* iter = mLinkedListHeader;
		Node* addNode = new Node();
		addNode->mNodeData = data;
		while (iter->mNextNode != nullptr)
		{
			iter = iter->mNextNode;
		}

		iter->mNextNode = addNode;
	}
	void DeleteNode(T data)
	{
		Node* iter = mLinkedListHeader;
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
	void Retrieve()
	{
		Node* iter = mLinkedListHeader->mNextNode;
		while (iter->mNextNode != nullptr)
		{
			cout << iter->mNodeData << " -> ";
			iter = iter->mNextNode;
		}

		cout << iter->mNodeData << endl;
	}
	void DeleteDuplicatedData()
	{
		Node* currentNode = mLinkedListHeader->mNextNode;
		Node* iterNode = currentNode;
		while (currentNode != nullptr && currentNode->mNextNode != nullptr)
		{
			while (iterNode->mNextNode != nullptr)
			{
				if (iterNode->mNextNode->mNodeData == currentNode->mNodeData)
				{
					iterNode->mNextNode = iterNode->mNextNode->mNextNode;
				}
				else
				{
					iterNode = iterNode->mNextNode;
				}
			}

			currentNode = currentNode->mNextNode;
			iterNode = currentNode;
		}
	}

	Node* mLinkedListHeader;
};

int main()
{
	LinkedList<int> ll;
	ll.AddNode(1);
	ll.AddNode(1);
	ll.AddNode(2);
	ll.AddNode(3);
	ll.AddNode(4);
	ll.AddNode(2);
	ll.AddNode(2);
	ll.AddNode(2);
	ll.AddNode(3);
	ll.AddNode(5);
	ll.AddNode(6);
	ll.AddNode(1);
	ll.Retrieve();
	ll.DeleteDuplicatedData();
	ll.Retrieve();

	return 0;
}
