/*
*** ����1:
*** � ���ڸ� �ڸ��� ���� �� ���� Linked List�� ��Ҵ�.
*** �� ��, 1�� �ڸ��� ����� ������ �Ųٷ� �����Ǿ� �ִ�.
*** �̷��� ������ Linked List �� ���� �޾Ƽ� �ջ��ϰ�
*** ���� ���·� Linked List�� ��Ƽ� ��ȯ�϶�
*** ����:
*** ��->��->�� ==> 419
*** ��->��->�� ==> 346
***                ---
*** ���� ���:     765
*** ���� ���: ��->��->��
*/

/*
*** ����2:
*** � ���ڸ� �ڸ��� ���� �� ���� Linked List�� ��Ҵ�.
*** Linked List �� ���� �޾Ƽ� �ջ��ϰ�
*** ���� ���·� Linked List�� ��Ƽ� ��ȯ�϶�
*** ����:
*** ��->��->�� ==> 419
*** ��->��     ==>  34
***                ---
*** ���� ���:     453
*** ���� ���: ��->��->��
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

  class Storage
  {
  public:
    bool carry = false;
    Node* result = nullptr;
  }; // end Digit class

  Node* header;

public:
  LinkedList() { header = new Node(); }
  void addNode(__int16 d);
  void deleteNode(__int16 d);
  Node* getNode(__int16 n);
  Node* digitAddUp(Node* l1, Node* l2, bool carry);
  Node* digitAddUp02(Node* l1, Node* l2);
  Node* insertBefore(Node* n, __int16 data); // ���ο� node�� ���� node ���ʿ� ����
  Node* LPadList(Node* l, __int16 length); // ���ο� node�� ���� node ���ʿ� �߰�
  Storage* addLists(Node* l1, Node* l2); // Node ������ ����
  __int16 getListLength(Node* l); // Node�� ���̸� ����
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

LinkedList::Node* LinkedList::digitAddUp(Node* l1, Node* l2, bool carry)
{
  // ����� �� �������� NULL
  if (l1 == NULL && l2 == NULL && carry == false) return NULL;

  Node* result = new Node();
  __int32 value = carry;

  // ����
  if (l1 != NULL) value += l1->data;
  if (l2 != NULL) value += l2->data;

  // ĳ�� Ȯ��
  result->data = value % 10;

  if (l1 != NULL || l2 != NULL)
  {
    // ����Լ�
    Node* next = digitAddUp(
      l1 == NULL ? NULL : l1->next,
      l2 == NULL ? NULL : l2->next,
      value >= 10 ? true : false
    );
    result->next = next;
  }

  return result;
}

LinkedList::Node* LinkedList::digitAddUp02(Node* l1, Node* l2)
{
  // Node ���̸� ����
  __int16 len1 = getListLength(l1);
  __int16 len2 = getListLength(l2);

  // ���̰� ª�� node�� �ٸ� node ���̸�ŭ 0���� ä��
  if (len1 < len2) l1 = LPadList(l1, len2 - len1);
  else l2 = LPadList(l2, len1 - len2);

  // ��ü�� �̿��Ͽ� ������ ����
  Storage* storage = addLists(l1, l2);

  // �� �տ� carry�� ������ carry �߰�
  if (storage->carry) storage->result = insertBefore(storage->result, storage->carry);
  
  return storage->result;
}

__int16 LinkedList::getListLength(Node* l)
{
  __int16 total = 0;

  while (l != NULL)
  {
    total++;
    l = l->next;
  }

  return total;
}

LinkedList::Node* LinkedList::insertBefore(Node* n, __int16 data)
{
  Node* before = new Node(data);

  if (n != NULL) before->next = n;

  return before;
}

LinkedList::Node* LinkedList::LPadList(Node* l, __int16 length)
{
  Node* head = l;

  for (int i = 0; i < length; i++)
  {
    head = insertBefore(head, 0);
  }

  return head;
}

LinkedList::Storage* LinkedList::addLists(Node* l1, Node* l2)
{
  if (l1 == NULL && l2 == NULL)
  {
    Storage* storage = new Storage();
    return storage;
  }

  Storage* storage = addLists(l1->next, l2->next);
  __int32 value = storage->carry + l1->data + l2->data;
  __int16 data = value % 10;

  storage->result = insertBefore(storage->result, data);
  storage->carry = value / 10;

  return storage;
}

int main()
{
  LinkedList l1, l2, l3;
  /* 1�� ���� */
  //l1.addNode(9);
  //l1.addNode(1);
  //l1.addNode(4);
  //l1.retrieve();
  //l2.addNode(6);
  //l2.addNode(4);
  //l2.addNode(3);
  //l2.retrieve();
  //LinkedList::Node* sumNode = l3.digitAddUp(l1.header->next, l2.header->next, false);
  //while (sumNode->next != NULL)
  //{
  //  cout << sumNode->data << " -> ";
  //  sumNode = sumNode->next;
  //}
  //cout << sumNode->data;

  /* 2�� ���� */
  //l1.addNode(4);
  //l1.addNode(1);
  l1.addNode(9);
  l1.addNode(1);
  l1.retrieve();
  //l2.addNode(3);
  //l2.addNode(4);
  l2.addNode(1);
  l2.addNode(1);
  l2.retrieve();
  LinkedList::Node* sumNode = l3.digitAddUp02(l1.header, l2.header);
  while (sumNode->next != NULL)
  {
    cout << sumNode->data << " -> ";
    sumNode = sumNode->next;
  }
  cout << sumNode->data;

  return 0;
}
