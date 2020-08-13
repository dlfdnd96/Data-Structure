#include <iostream>
#include <exception>

using namespace std;

template<typename QT>
class Queue
{
	template<typename NT>
	class Node
	{
	public:
		Node(NT data) : mData(data) {}
		~Node() {}
		const NT GetNodeData() const
		{
			return this->mData;
		}
		Node<NT>* GetNodeNext() const
		{
			return this->mNext;
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
	void Add(QT data)
	{
		Node<QT>* newNode = new Node<QT>(data);

		if (mEndQueuePointer != nullptr)
		{
			mEndQueuePointer->SetNodeNext(newNode);
		}

		mEndQueuePointer = newNode;

		if (mFrontQueuePointer == nullptr)
		{
			mFrontQueuePointer = mEndQueuePointer;
		}
	}
	const QT Remove()
	{
		if (mFrontQueuePointer == nullptr)
		{
			throw runtime_error("Queue is empty!!");
		}

		Node<QT>* deleteStoreNode = mFrontQueuePointer;
		QT currentData = mFrontQueuePointer->GetNodeData();
		mFrontQueuePointer = mFrontQueuePointer->GetNodeNext();

		if (mFrontQueuePointer == nullptr)
		{
			mEndQueuePointer = nullptr;
		}

		delete deleteStoreNode;

		return currentData;
	}
	const QT Peek() const
	{
		if (mFrontQueuePointer == nullptr)
		{
			throw runtime_error("Queue is empty!!");
		}

		return mFrontQueuePointer->GetNodeData();
	}
	const bool IsEmpty() const
	{
		return mFrontQueuePointer == nullptr;
	}

private:
	Node<QT>* mFrontQueuePointer;
	Node<QT>* mEndQueuePointer;
};

int main()
{
	unique_ptr<Queue<int>> queueUniquePointer = make_unique<Queue<int>>();
	queueUniquePointer->Add(1);
	queueUniquePointer->Add(2);
	queueUniquePointer->Add(3);
	queueUniquePointer->Add(4);

	try
	{
		cout << "Remove: " << queueUniquePointer->Remove() << endl;
		cout << "Remove: " << queueUniquePointer->Remove() << endl;
		cout << "Remove: " << queueUniquePointer->Remove() << endl;
		cout << "Peek: " << queueUniquePointer->Peek() << endl;
		cout << "IsEmpty?: " << queueUniquePointer->IsEmpty() << endl;
		cout << "Remove: " << queueUniquePointer->Remove() << endl;
		cout << "IsEmpty?: " << queueUniquePointer->IsEmpty() << endl;
		cout << "Remove: " << queueUniquePointer->Remove() << endl;
	}
	catch (const runtime_error errorMessage)
	{
		cout << "Exception occur: " << errorMessage.what() << endl;
	}

	return 0;
}
