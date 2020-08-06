/* 
*** 단방향 LinkedList의 끝에서 K번째 노드를
*** 찾는 알고리즘을 구현하라
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
  LinkedList() { this->header = new Node(); }
  void addNode(__int16 d);
  void retrieve();
  Node* KthToLast(Node* first, __int16 k, unsigned short* countPtr); // 뒤에서 부터 노드를 세는 함수
  Node* KthToLastUsingDoublePointer(Node* first, __int16 k); // 포인터 2개를 사용하여 뒤에서 부터 노드를 세는 함수
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

LinkedList::Node* LinkedList::KthToLast(Node* first, __int16 k, unsigned short* countPtr)
{
  if (first == NULL) return NULL;

  Node* found = KthToLast(first->next, k, countPtr);
  *countPtr = *countPtr + 1;
  
  if (*countPtr == k) return first;

  return found;
}

LinkedList::Node* LinkedList::KthToLastUsingDoublePointer(Node* first, __int16 k)
{
  Node* runnerNode = header;
  Node* iterNode = header;

  for (int i = 0; i < k; i++)
  {
    if (runnerNode == NULL) return NULL;
    runnerNode = runnerNode->next;
  }

  while (runnerNode != NULL)
  {
    runnerNode = runnerNode->next;
    iterNode = iterNode->next;
  }

  return iterNode;
}

int main()
{
  LinkedList ll;

  ll.addNode(0);
  ll.addNode(1);
  ll.addNode(2);
  ll.addNode(3);
  ll.retrieve();

  __int16 k = 1;
  unsigned short count = 0;

  // LinkedList::Node* found = ll.KthToLast(ll.header, k, &count);
  LinkedList::Node* found = ll.KthToLastUsingDoublePointer(ll.header, k);
  cout << found->data << endl;

  return 0;
}
