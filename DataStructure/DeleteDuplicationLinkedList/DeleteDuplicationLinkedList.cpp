/*
*** 정렬되어 있지 않는 Linked List Nodd의
*** 중복 값을 삭제하라
*/
#include <iostream>
#include <unordered_set>

using std::cout;
using std::endl;
using std::unordered_set;

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
	void AddNode(__int32 const data);
	void DeleteDuplicationNodeUsingHashSet(); // HashSet을 이용하여 중복값 제거
	void DeleteDuplicationNodeUsingPointer(); // 포인터를 이용하여 중복값 제거
	void Retrieve();

private:
	Node* mHeader;
	unordered_set<__int32> mDataHashSet;
}; // end Node class

void LinkedList::Node::SetData(__int32 const data)
{
	this->mData = data;
}
__int32 LinkedList::Node::GetData() const
{
	return this->mData;
}
void LinkedList::Node::SetNode(LinkedList::Node* node)
{
	this->mNext = node;
}
LinkedList::Node* LinkedList::Node::GetNextNode() const
{
	return this->mNext;
}

void LinkedList::AddNode(__int32 const data)
{
	Node* end = new Node();
	end->SetData(data);
	Node* iterNode = mHeader;

	while (iterNode->GetNextNode() != nullptr)
	{
		iterNode = iterNode->GetNextNode();
	}

	iterNode->SetNode(end);
}

void LinkedList::DeleteDuplicationNodeUsingHashSet()
{
	Node* iterNode = mHeader;

	while (iterNode->GetNextNode() != nullptr)
	{
		// 노드 값이 HashSet과 중복여부 확인
		auto iterHashSet = mDataHashSet.find(iterNode->GetNextNode()->GetData());

		if (iterHashSet == mDataHashSet.end()) // 노드의 값이 중복 값이 아니라면
		{
			mDataHashSet.insert(iterNode->GetData());
			iterNode = iterNode->GetNextNode();
		}
		else iterNode->SetNode(iterNode->GetNextNode()->GetNextNode());
	}
}

void LinkedList::DeleteDuplicationNodeUsingPointer()
{
	Node* iterNode = mHeader;

	while (iterNode != nullptr && iterNode->GetNextNode() != nullptr)
	{
		// 중복 값을 찾을 포인터 선언
		Node* iterNodeRunner = iterNode;

		while (iterNodeRunner->GetNextNode() != nullptr)
		{
			if (iterNode->GetData() == iterNodeRunner->GetNextNode()->GetData())
			{
				iterNodeRunner->SetNode(iterNodeRunner->GetNextNode()->GetNextNode());
			}
			else
			{
				iterNodeRunner = iterNodeRunner->GetNextNode();
			}
		}

		iterNode = iterNode->GetNextNode();
	}
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

int main()
{
	std::unique_ptr<LinkedList> linkedListUniquePointer = std::make_unique<LinkedList>();
	linkedListUniquePointer->AddNode(3);
	linkedListUniquePointer->AddNode(2);
	linkedListUniquePointer->AddNode(1);
	linkedListUniquePointer->AddNode(2);
	linkedListUniquePointer->AddNode(4);
	linkedListUniquePointer->AddNode(1);
	linkedListUniquePointer->AddNode(5);
	linkedListUniquePointer->AddNode(3);
	linkedListUniquePointer->Retrieve();

	linkedListUniquePointer->DeleteDuplicationNodeUsingHashSet();
	// linkedListUniquePointer->DeleteDuplicationNodeUsingPointer();
	linkedListUniquePointer->Retrieve();

	return 0;
}
