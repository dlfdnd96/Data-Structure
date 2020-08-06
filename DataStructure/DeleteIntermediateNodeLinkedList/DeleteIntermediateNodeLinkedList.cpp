/* 
*** ������ �߰� ��带 �����Ͽ� Linked List�� �籸���϶�.
*** ��, ����� ���۰� ���� �𸥴�.
*/
#include <iostream>

using namespace std;

class LinkedList
{
public:
  class Node
  {
  public:
    __int16 data;
    Node* next = nullptr;
  }; // end Node class

  Node* header;

public:
  LinkedList() { header = new Node(); }
  void addNode(__int16 d);
  void deleteNode(__int16 d);
  bool deleteMediateNode(Node* n);
  Node* getNode(__int16 n);
  void retrieve();
}; // end LinkedList class

void LinkedList::addNode(__int16 d)
{
  Node* end = new Node();
  end->data = d;
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
    if (iterNode->next->data == d) iterNode->next = iterNode->next->next;
    else iterNode = iterNode->next;
  }
}

void LinkedList::retrieve()
{
  Node* iterNode = header->next;

  while (iterNode->next != NULL)
  {
    cout << iterNode->data << " -> ";
    iterNode = iterNode->next;
  }

  cout << iterNode->data << endl;
}

LinkedList::Node* LinkedList::getNode(__int16 n)
{
  Node* iterNode = header;

  for (int i = 0; i < n; i++)
  {
    iterNode = iterNode->next;
  }

  return iterNode;
}

/* 
*** ���̵�� ����. ��->��->��->���� ���� �� 2���� �����Ѵٰ� �����ϸ�
*** 3�� ��� ���� 2������ ���� ���� �� 3���� ����� 4������ �����Ѵ�
*/
bool LinkedList::deleteMediateNode(Node* n)
{
  if (n == NULL || n->next == NULL) return false;

  Node* next = n->next;
  n->data = next->data;
  n->next = next->next;

  return true;
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
  ll.deleteMediateNode(ll.getNode(3));
  ll.retrieve();

  return 0;
}
