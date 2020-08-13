#include <iostream>
#include <exception>

using namespace std;

template <typename ST>
class Stack
{
	template <typename NT>
	class Node
	{
	public:
		Node(NT data) : mData(data) {}
		~Node() {}
		const NT GetNodeData() const
		{
			return mData;
		}
		Node<NT>* GetNodeNext() const
		{
			return mNext;
		}
		void SetNodeNext(Node<NT>* inputNode)
		{
			this->mNext = inputNode;
		}

	private:
		const NT mData;
		Node<NT>* mNext = nullptr;
	};

public:
	void Push(ST data)
	{
		Node<ST>* addNode = new Node<ST>(data);

		if (mTop == nullptr)
		{
			mTop = addNode;

			return;
		}

		addNode->SetNodeNext(mTop);
		mTop = addNode;
	}
	const ST Pop()
	{
		if (mTop == nullptr)
		{
			throw runtime_error("Stack is empty!!");
		}

		Node<ST>* tempStoreDeleteNode = mTop;
		ST currentData = mTop->GetNodeData();
		mTop = mTop->GetNodeNext();

		delete tempStoreDeleteNode;

		return currentData;
	}
	const ST Peek() const
	{
		if (mTop == nullptr)
		{
			throw runtime_error("Stack is empty!!");
		}

		return mTop->GetNodeData();
	}
	const bool IsEmpty() const
	{
		return mTop == nullptr;
	}

private:
	Node<ST>* mTop;
};

int main()
{
	unique_ptr<Stack<int>> stackUniquePointer = make_unique<Stack<int>>();
	stackUniquePointer->Push(1);
	stackUniquePointer->Push(2);
	stackUniquePointer->Push(3);
	stackUniquePointer->Push(4);

	try
	{
		cout << "Pop: " << stackUniquePointer->Pop() << endl;
		cout << "Pop: " << stackUniquePointer->Pop() << endl;
		cout << "Pop: " << stackUniquePointer->Pop() << endl;
		cout << "Peek: " << stackUniquePointer->Peek() << endl;
		cout << "IsEmpty?: " << stackUniquePointer->IsEmpty() << endl;
		cout << "Pop: " << stackUniquePointer->Pop() << endl;
		cout << "IsEmpty?: " << stackUniquePointer->IsEmpty() << endl;
		cout << "Pop: " << stackUniquePointer->Pop() << endl;
	}
	catch (const runtime_error errorMessage)
	{
		cout << "Exception occur: " << errorMessage.what() << endl;
	}

	return 0;
}