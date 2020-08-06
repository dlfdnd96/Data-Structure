/*
*** 주어진 두 개의 단방향 Linked List에서
*** 교차되는 노드를 찾으시오.
*** 단, 교차점은 값이 아닌 주소이다.
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
  void retrieve();
  Node* findIntersection(Node* n1, Node* n2); // 교차점 찾기
  __int16 getListLength(Node* n); // Linked List 길이 구하기
  Node* getNodeStart(Node* n, __int16 data); // Node의 시작점 설정
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

LinkedList::Node* LinkedList::findIntersection(Node* n1, Node* n2)
{
  // 각 node의 길이를 구함
  __int16 len1 = getListLength(n1);
  __int16 len2 = getListLength(n2);

  // node를 뒤에서부터 시작하여 길이를 맞춤
  if (len1 > len2) n1 = getNodeStart(n1, len1 - len2);
  else if (len1 < len2) n2 = getNodeStart(n2, len2 - len1);

  // 교차점 검색
  while (n1->next != NULL && n2->next != NULL)
  {
    if (n1->data == n2->data) return n1;

    n1 = n1->next;
    n2 = n2->next;
  }

  return NULL;
}

__int16 LinkedList::getListLength(Node* n)
{
  __int16 total = 1;

  while (n->next != NULL)
  {
    n = n->next;
    ++total;
  }

  return total;
}

LinkedList::Node* LinkedList::getNodeStart(Node* n, __int16 data)
{
  for (int i = 0; i < data; i++)
  {
    n = n->next;
  }

  return n;
}

int main()
{
  LinkedList l1, l2, l3;
  l1.addNode(5);
  l1.addNode(7);
  l1.addNode(9);
  l1.addNode(10);
  l1.addNode(7);
  l1.addNode(6);
  l1.retrieve();
  /* 교차점이 있는 설정 */
  //l2.addNode(6);
  //l2.addNode(8);
  //l2.addNode(10);
  //l2.addNode(7);
  //l2.addNode(6);

  /* 교차점이 없는 설정 */
  l2.addNode(1);
  l2.addNode(2);
  l2.addNode(3);
  l2.addNode(4);
  l2.addNode(5);
  l2.retrieve();

  LinkedList::Node* n = l3.findIntersection(l1.header->next, l2.header->next);

  if (n != NULL) cout << "Intersection: " << n->data << endl;
  else cout << "Not Found" << endl;

  return 0;
}
