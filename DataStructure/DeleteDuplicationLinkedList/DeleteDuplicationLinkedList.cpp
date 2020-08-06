/* 
*** 정렬되어 있지 않는 Linked List Nodd의
*** 중복 값을 삭제하라
*/
#include <iostream>
#include <unordered_set>

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
  unordered_set<__int16> dataHashSet;

public:
  LinkedList() { this->header = new Node(); }
  void addNode(__int16 d);
  void deleteDuplicationNodeUsingHashSet(); // HashSet을 이용하여 중복값 제거
  void deleteDuplicationNodeUsingPointer(); // 포인터를 이용하여 중복값 제거
  void retrieve();
}; // end Node class

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

void LinkedList::deleteDuplicationNodeUsingHashSet()
{
  Node* iterNode = header;

  while (iterNode->next != NULL)
  {
    // 노드 값이 HashSet과 중복여부 확인
    auto iterHashSet = dataHashSet.find(iterNode->next->data);

    if (iterHashSet == dataHashSet.end()) // 노드의 값이 중복 값이 아니라면
    {
      dataHashSet.insert(iterNode->data);
      iterNode = iterNode->next;
    }
    else iterNode->next = iterNode->next->next;
  }
}

void LinkedList::deleteDuplicationNodeUsingPointer()
{
  Node* iterNode = header;

  while (iterNode != NULL && iterNode->next != NULL)
  {
    // 중복 값을 찾을 포인터 선언
    Node* iterNodeRunner = iterNode;

    while (iterNodeRunner->next != NULL)
    {
      if (iterNode->data == iterNodeRunner->next->data) iterNodeRunner->next = iterNodeRunner->next->next;
      else iterNodeRunner = iterNodeRunner->next;
    }

    iterNode = iterNode->next;
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

int main()
{
  LinkedList ll;
  ll.addNode(3);
  ll.addNode(2);
  ll.addNode(1);
  ll.addNode(2);
  ll.addNode(4);
  ll.addNode(1);
  ll.addNode(5);
  ll.addNode(3);
  ll.retrieve();
  // ll.deleteDuplicationNodeUsingHashSet();
  ll.deleteDuplicationNodeUsingPointer();
  ll.retrieve();

  return 0;
}
