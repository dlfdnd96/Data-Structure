/* header node°¡ ÀÖ´Â LinkedList */
#include <iostream>

using namespace std;

class LinkedList
{
public:
	class Node
	{
	public:
		__int16 mData;
		Node* next = nullptr;
	}; // end Node class

	Node* header;

public:
	LinkedList() { header = new Node(); }
	void addNode(__int16 d);
	void deleteNode(__int16 d);
	void retrieve();
}; // end LinkedList class

void LinkedList::addNode(__int16 d)
{
	Node* end = new Node();
	end->mData = d;
	Node* iterNode = header;

	while (iterNode->next != NULL)
	{
		iterNode = iterNode->next;
	}

	iterNode->next = end;
}

void LinkedList::deleteNode(__int16 d)
{
	Node* iterNode = header;

	while (iterNode->next != NULL)
	{
		if (iterNode->next->mData == d) iterNode->next = iterNode->next->next;
		else iterNode = iterNode->next;
	}
}

void LinkedList::retrieve()
{
	Node* iterNode = header->next;

	while (iterNode->next != NULL)
	{
		cout << iterNode->mData << " -> ";
		iterNode = iterNode->next;
	}

	cout << iterNode->mData << endl;
}

int main()
{
	LinkedList ll;
	ll.addNode(0);
	ll.addNode(1);
	ll.addNode(2);
	ll.addNode(3);
	ll.addNode(4);
	ll.retrieve();
	ll.deleteNode(0);
	ll.retrieve();
	ll.deleteNode(3);
	ll.retrieve();

	return 0;
}
