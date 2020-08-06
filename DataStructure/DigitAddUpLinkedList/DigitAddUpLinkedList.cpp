/*
*** 문제1:
*** 어떤 숫자를 자릿수 별로 한 개씩 Linked List에 담았다.
*** 이 때, 1의 자리가 헤더에 오도록 거꾸로 구성되어 있다.
*** 이러한 종류의 Linked List 두 개를 받아서 합산하고
*** 같은 형태로 Linked List에 담아서 반환하라
*** 예시:
*** ⑨->①->④ ==> 419
*** ⑥->④->③ ==> 346
***                ---
*** 더한 결과:     765
*** 최종 결과: ⑤->⑥->⑦
*/

/*
*** 문제2:
*** 어떤 숫자를 자릿수 별로 한 개씩 Linked List에 담았다.
*** Linked List 두 개를 받아서 합산하고
*** 같은 형태로 Linked List에 담아서 반환하라
*** 예시:
*** ④->①->⑨ ==> 419
*** ③->④     ==>  34
***                ---
*** 더한 결과:     453
*** 최종 결과: ④->⑤->③
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
  Node* insertBefore(Node* n, __int16 data); // 새로운 node를 기존 node 왼쪽에 연결
  Node* LPadList(Node* l, __int16 length); // 새로운 node를 기존 node 왼쪽에 추가
  Storage* addLists(Node* l1, Node* l2); // Node 덧셈을 수행
  __int16 getListLength(Node* l); // Node의 길이를 구함
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
  // 계산이 다 끝났으면 NULL
  if (l1 == NULL && l2 == NULL && carry == false) return NULL;

  Node* result = new Node();
  __int32 value = carry;

  // 덧셈
  if (l1 != NULL) value += l1->data;
  if (l2 != NULL) value += l2->data;

  // 캐리 확인
  result->data = value % 10;

  if (l1 != NULL || l2 != NULL)
  {
    // 재귀함수
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
  // Node 길이를 구함
  __int16 len1 = getListLength(l1);
  __int16 len2 = getListLength(l2);

  // 길이가 짧은 node는 다른 node 길이만큼 0으로 채움
  if (len1 < len2) l1 = LPadList(l1, len2 - len1);
  else l2 = LPadList(l2, len1 - len2);

  // 객체를 이용하여 덧셈을 수행
  Storage* storage = addLists(l1, l2);

  // 맨 앞에 carry가 있으면 carry 추가
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
  /* 1번 문제 */
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

  /* 2번 문제 */
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
