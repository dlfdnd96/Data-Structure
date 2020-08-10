#include <iostream>
#include <stdexcept>

using namespace std;

template <typename QT>
class Queue
{
public:
  template <typename NT>
  class Node
  {
  public:
	NT data = NULL;
	Node<NT>* next = nullptr;

  public:
	Node(NT data) { this->data = data; }
  }; // end Node class

public:
  Node<QT>* first = nullptr;
  Node<QT>* last = nullptr;

public:
  void add(QT data)
  {
	Node<QT>* t = new Node<QT>(data);

	if (last != nullptr)
	{
	  last->next = t;
	}
	last = t;

	if (first == nullptr)
	{
	  first = last;
	}
  }

  QT remove()
  {
	if (first == nullptr)
	{
	  throw runtime_error("Queue가 비어있습니다.");
	}

	QT data = first->data;
	first = first->next;

	if (first == nullptr)
	{
	  last = nullptr;
	}

	return data;
  }

  QT peek()
  {
	if (first == nullptr)
	{
	  throw runtime_error("Queue가 비어있습니다.");
	}

	return first->data;
  }

  bool isEmpty()
  {
	return first == nullptr;
  }
}; // end Queue class

int main()
{
  Queue<int>* q = new Queue<int>();
  q->add(1);
  q->add(2);
  q->add(3);
  q->add(4);

  try
  {
	cout << q->remove() << endl;
	cout << q->remove() << endl;
	cout << q->remove() << endl;
	cout << q->peek() << endl;
	cout << q->remove() << endl;
	cout << q->isEmpty() << endl;
	cout << q->remove() << endl;
	cout << q->isEmpty() << endl;
  }
  catch (const runtime_error& e)
  {
	cout << "오류 발생: " << e.what() << endl;
  }

  return 0;
}
