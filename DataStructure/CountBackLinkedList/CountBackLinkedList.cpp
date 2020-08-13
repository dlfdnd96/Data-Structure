/*
*** 단방향 LinkedList의 끝에서 K번째 노드를
*** 찾는 알고리즘을 구현하라
*/
#include <iostream>

using std::cout;
using std::endl;

class LinkedList
{
public:
	class Node
	{
	public:
		void SetData(__int32 const data);
		__int32 GetData() const;
		void SetNode(Node* const node);
		Node* GetNextNode() const;

	private:
		__int32 mData = NULL;
		Node* mNext = nullptr;
	}; // end Node class

public:
	LinkedList()
	{ 
		this->mHeader = new Node();
	}
	Node* GetHeader() const;
	void AddNode(__int32 const data);
	void Retrieve();
	Node* KthToLastRecursive(Node* const first, __int32 const k, __int32& countPtr); // 뒤에서 부터 노드를 세는 함수
	Node* KthToLastUsingDoublePointer(Node* const first, __int32 const k); // 포인터 2개를 사용하여 뒤에서 부터 노드를 세는 함수

private:
	Node* mHeader;
}; // end LinkedList class

void LinkedList::Node::SetData(__int32 const data)
{
	this->mData = data;
}
__int32 LinkedList::Node::GetData() const
{
	return this->mData;
}
void LinkedList::Node::SetNode(Node* const node)
{
	this->mNext = node;
}
LinkedList::Node* LinkedList::Node::GetNextNode() const
{
	return this->mNext;
}
LinkedList::Node* LinkedList::GetHeader() const
{
	return this->mHeader;
}

void LinkedList::AddNode(__int32 const data)
{
	Node* const end = new Node();
	end->SetData(data);
	Node* iterNode = mHeader;

	while (iterNode->GetNextNode() != nullptr)
	{
		iterNode = iterNode->GetNextNode();
	}

	iterNode->SetNode(end);
}

void LinkedList::Retrieve()
{
	Node* iterNode = mHeader->GetNextNode();

	while (iterNode->GetNextNode() != nullptr)
	{
		cout << iterNode->GetData() << " -> ";
		iterNode = iterNode->GetNextNode();
	}

	cout << iterNode->GetData() << endl;
}

LinkedList::Node* LinkedList::KthToLastRecursive(Node* const first, __int32 const k, __int32& countPtr)
{
	if (first == nullptr)
	{
		return nullptr;
	}

	Node* found = KthToLastRecursive(first->GetNextNode(), k, countPtr);
	countPtr = countPtr + 1;

	if (countPtr == k)
	{
		return first;
	}

	return found;
}

LinkedList::Node* LinkedList::KthToLastUsingDoublePointer(Node* first, __int32 k)
{
	Node* runnerNode = mHeader;
	Node* iterNode = mHeader;

	for (int i = 0; i < k; i++)
	{
		if (runnerNode == NULL)
		{
			return NULL;
		}
		runnerNode = runnerNode->GetNextNode();
	}

	while (runnerNode != NULL)
	{
		runnerNode = runnerNode->GetNextNode();
		iterNode = iterNode->GetNextNode();
	}

	return iterNode;
}

int main()
{
	std::unique_ptr<LinkedList> linkedListUniquePointer = std::make_unique<LinkedList>();
	linkedListUniquePointer->AddNode(0);
	linkedListUniquePointer->AddNode(1);
	linkedListUniquePointer->AddNode(2);
	linkedListUniquePointer->AddNode(3);
	linkedListUniquePointer->Retrieve();

	__int32 const k = 3;
	__int32 count = 0;

	LinkedList::Node* found = linkedListUniquePointer->KthToLastRecursive(linkedListUniquePointer->GetHeader(), k, count);
	// LinkedList::Node* found = linkedListUniquePointer->KthToLastUsingDoublePointer(linkedListUniquePointer->GetHeader(), k);
	cout << found->GetData() << endl;

	return 0;
}
