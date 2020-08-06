/*
*** Linked List 안에 loop가 있는지 확인하고
*** 루프가 시작되는 노드를 찾으시오.
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

  public:
    Node() {}
    Node(__int16 d) { this->data = d; }
  }; // end Node class

  Node* header;

public:
  LinkedList() { header = new Node(); }
  void addNode(__int16 d);
  void addNode(Node* n);
  void retrieve();
  Node* findLoop(Node* head);
  Node* getStartNode(Node* n, __int16 length);
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

void LinkedList::addNode(Node* n)
{
  Node* iterNode = header;

  while (iterNode->next != NULL)
  {
    iterNode = iterNode->next;
  }

  iterNode->next = n;
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

LinkedList::Node* LinkedList::getStartNode(Node* n, __int16 length)
{
  for (int i = 0; i < length; i++)
  {
    n = n->next;
  }

  return n;
}

LinkedList::Node* LinkedList::findLoop(Node* head)
{
  Node* fast = head;
  Node* slow = head;

  while (fast != NULL && fast->next != NULL)
  {
    slow = slow->next;
    fast = fast->next->next;

    if (fast == slow) break;
  }

  if (fast == NULL || fast->next == NULL) return NULL;

  slow = head;

  while (fast != slow)
  {
    slow = slow->next;
    fast = fast->next;
  }

  return fast;
}

int main()
{
  LinkedList l1, l2;
  l1.addNode(1);
  l1.addNode(2);
  l1.addNode(3);
  l1.addNode(4);
  l1.addNode(5);
  l1.addNode(6);
  l1.addNode(7);
  l1.addNode(8);
  l1.addNode(l1.getStartNode(l1.header, 2));

  LinkedList::Node* n = l2.findLoop(l1.header->next);

  if (n != NULL) cout << "Start of loop: " << n->data << endl;
  else cout << "Loop not found" << endl;

  return 0;
}
