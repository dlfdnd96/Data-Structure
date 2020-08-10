/*
*** 단방향 Linked List 구현
*** 
*** Author: iwryu
*** Since: 20-07-31
*/

#include <iostream>

using namespace std;

class Node
{
// Public 변수
public:
  __int16 data; // Node의 data
  Node* next = nullptr;

// Public 함수
public:
  Node(__int8 d) { this->data = d; } // Constructure
  void addNode(__int16 d);
  void deleteNode(__int16 d);
  void retrieve();
}; // end class

/*
*** Node를 추가
*** 
*** Author: iwryu
*** Since: 20-07-31
*** Params: d
*** Return:
*/
void Node::addNode(__int16 d)
{
  Node* end = new Node(d);
  Node* nodeIter = this;

  while (nodeIter->next != NULL)
  {
    nodeIter = nodeIter->next;
  }

  nodeIter->next = end;
}

/*
*** Node를 삭제
***
*** Author: iwryu
*** Since: 20-07-31
*** Params: d
*** Return:
*/
void Node::deleteNode(__int16 d)
{
  Node* nodeIter = this;

  while (nodeIter->next != NULL)
  {
    if (nodeIter->next->data == d)
    {
      Node* deleteNode = nodeIter->next;
      nodeIter->next = nodeIter->next->next;
      delete deleteNode;
    }
    else nodeIter = nodeIter->next;
  }
}

/*
*** 모든 node를 출력
***
*** Author: iwryu
*** Since: 20-07-31
*** Params:
*** Return:
*/
void Node::retrieve()
{
  Node* nodeIter = this;

  while (nodeIter->next != NULL)
  {
    cout << nodeIter->data << " -> ";
    nodeIter = nodeIter->next;
  }

  cout << nodeIter->data << endl;
}

int main()
{
  Node head(0);
  head.addNode(1);
  head.addNode(2);
  head.addNode(3);
  head.addNode(4);
  head.retrieve();
  head.deleteNode(2);
  head.deleteNode(3);
  head.retrieve();

  return 0;
}
