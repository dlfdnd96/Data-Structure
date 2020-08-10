#include <iostream>
#include <stdexcept>

using namespace std;

template<class ST>
class Stack
{
public:
  template<class NT>
  class Node
  {
  public:
    NT data = NULL;
    Node<NT>* next = nullptr;

  public:
    Node(NT data) { this->data = data; }
  }; // end Node class

public:
  Node<ST>* top = nullptr;

public:
  ST pop()
  {
    if (top == NULL) throw runtime_error("Top이 비어있습니다.");

    ST item = top->data;
    top = top->next;

    return item;
  }

  void push(ST data)
  {
    Node<ST>* n = new Node<ST>(data);

    n->next = top;
    top = n;
  }

  ST peek()
  {
    if (top == NULL) throw runtime_error("Top이 비어있습니다.");

    return top->data;
  }

  bool isEmpty()
  {
    return top == NULL;
  }
}; // end Stack class

int main()
{
  Stack<int>* s = new Stack<int>();
  s->push(1);
  s->push(2);
  s->push(3);
  s->push(4);

  try
  {
    cout << s->pop() << endl;
    cout << s->pop() << endl;
    cout << s->peek() << endl;
    cout << s->pop() << endl;
    cout << s->isEmpty() << endl;
    cout << s->pop() << endl;
    cout << s->isEmpty() << endl;
    cout << s->pop() << endl;
    cout << s->peek() << endl;
  }
  catch (runtime_error& e)
  {
    cout << "오류 발생: " << e.what() << endl;
  }

  return 0;
}
