/* �ܹ��� Linked List ���� */

#include <iostream>

using namespace std;

class Node
{
public:
  __int16 data;
  Node* next = nullptr;

public:
  Node(__int8 d) { this->data = d; } // constructure
  void addNode(__int16 d); // node�� �߰�
  void deleteNode(__int16 d); // node�� ����
  void retrieve(); // ��� node�� ���
}; // end class

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

void Node::deleteNode(__int16 d)
{
  Node* nodeIter = this;

  while (nodeIter->next != NULL)
  {
    if (nodeIter->next->data == d) nodeIter->next = nodeIter->next->next;
    else nodeIter = nodeIter->next;
  }
}

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
