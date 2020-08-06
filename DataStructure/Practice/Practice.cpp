#include <iostream>

using namespace std;

class LinkedList
{
public:
  class Node
  {
  public:
    __int16 data;
    Node* next;

  public:
    Node() {}
    Node(__int32 d) { this->data = d; }
  };

  Node* header;

  class Storage
  {
  public:
    bool carry = false;
    Node* result = nullptr;
  };

public:
  LinkedList() { this->header = new Node(); }
  void addNode(__int16 d);
  void retrieve();
  Node* digitAddUp(Node* n1, Node* n2, bool carry);
  __int16 getListLength(Node* n);
  Node* LPadList(Node* n1, __int16 length);
  Node* insertBefore(Node* n1, __int16 data);
  Storage* addLists(Node* n1, Node* n2);
};

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

LinkedList::Node* LinkedList::digitAddUp(Node* n1, Node* n2, bool carry)
{
  __int16 len1 = getListLength(n1);
  __int16 len2 = getListLength(n2);

  if (len1 > len2) n2 = LPadList(n2, len1 - len2);
  else n1 = LPadList(n1, len2 - len1);

  Storage* storage = addLists(n1, n2);

  if (storage->carry) storage->result = insertBefore(storage->result, storage->carry);

  return storage->result;
}

__int16 LinkedList::getListLength(Node* n1)
{
  __int16 total = 0;

  while (n1->next != NULL)
  {
    n1 = n1->next;
    total++;
  }

  return total;
}

LinkedList::Node* LinkedList::LPadList(Node* n, __int16 length)
{
  Node* head = n;

  for (int i = 0; i < length; i++)
  {
    head = insertBefore(head, 0);
  }

  return head;
}

LinkedList::Node* LinkedList::insertBefore(Node* n, __int16 data)
{
  Node* before = new Node(data);

  if (n != NULL) before->next = n;

  return before;
}

LinkedList::Storage* LinkedList::addLists(Node* n1, Node* n2)
{
  if (n1 == NULL && n2 == NULL)
  {
    Storage* storage = new Storage();
    return storage;
  }

  Storage* storage = addLists(n1->next, n2->next);
  __int32 value = storage->carry + n1->data + n2->data;
  __int16 data = value % 10;

  storage->result = insertBefore(storage->result, data);
  storage->carry = value / 10;

  return storage;
}

int main()
{
  LinkedList l1, l2, l3, l4, l5;
  LinkedList::Node* addUpNode;
  l1.addNode(9);
  l1.addNode(1);
  l1.addNode(4);
  l1.retrieve();
  l2.addNode(6);
  l2.addNode(4);
  l2.addNode(3);
  l2.retrieve();
  l4.addNode(9);
  l4.addNode(9);
  l4.retrieve();
  l5.addNode(1);
  l5.addNode(1);
  l5.retrieve();
  addUpNode = l3.digitAddUp(l4.header->next, l5.header->next, false);
  while (addUpNode->next != NULL)
  {
    cout << addUpNode->data << " -> ";
    addUpNode = addUpNode->next;
  }
  cout << addUpNode->data << endl;

  return 0;
}
