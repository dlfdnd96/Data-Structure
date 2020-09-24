/*
*** 해쉬 테이블을 구현하라
*/
#include <iostream>
#include <string>

template <typename T>
struct LinkedList
{
    struct LinkedListNode
    {
        T mLinkedListData;
        LinkedListNode* mNextLinkedListNode;
    }; // end LinkedLinstNode struct

    LinkedList() : mLinkedListHeader(new LinkedListNode()) {}
    void AddLinkedListNode(T data) const
    {
        LinkedListNode* addNode = new LinkedListNode();
        addNode->mLinkedListData = data;
        LinkedListNode* iter = mLinkedListHeader;
        while (iter->mNextLinkedListNode != nullptr)
        {
            iter = iter->mNextLinkedListNode;
        }

        iter->mNextLinkedListNode = addNode;
    }
    void DeleteLinkedListNode(T data) const
    {
        LinkedListNode* iter = mLinkedListHeader;
        while (iter->mNextLinkedListNode != nullptr)
        {
            if (iter->mNextLinkedListNode->mLinkedListData == data)
            {
                iter->mNextLinkedListNode = iter->mNextLinkedListNode->mNextLinkedListNode;
            }
            else
            {
                iter = iter->mNextLinkedListNode;
            }
        }
    }
    void RetrieveLinkedList() const
    {
        LinkedListNode* iter = mLinkedListHeader;
        while (iter->mNextLinkedListNode != nullptr)
        {
            std::cout << iter->mLinkedListData << " -> ";
            iter = iter->mNextLinkedListNode;
        }

        std::cout << iter->mLinkedListData << std::endl;
    }

    LinkedListNode* mLinkedListHeader;
}; // end LinkedList struct

struct HashTable
{
    struct HashTableNode
    {
        HashTableNode(const std::string key, const std::string value) : mHashKey(key), mHashValue(value) {}
        std::string GetHashValue() const;
        void SetHashValue(const std::string value);

        std::string mHashKey;
        std::string mHashValue;
    }; // end HashTableNode struct

    HashTable(const int size) : mHashTableData(new LinkedList<HashTableNode>[size]) {}
    int GetHashCode(const std::string key) const;
    int ConvertToIndex(const int hashCode) const;
    const HashTableNode* SearchKey(LinkedList<HashTableNode>* list, const std::string key);

    LinkedList<HashTableNode>* mHashTableData;
}; // end HashTable struct

std::string HashTable::HashTableNode::GetHashValue() const
{
    return this->mHashValue;
}
void HashTable::HashTableNode::SetHashValue(const std::string value)
{
    this->mHashValue = value;
}

int HashTable::GetHashCode(const std::string key) const
{
    int hashCode = 0;
    for (char c : key)
    {
        hashCode += c;
    }

    return hashCode;
}

int HashTable::ConvertToIndex(const int hashCode) const
{
    int linkedListSize = _msize(mHashTableData);

    return hashCode % linkedListSize;
}

const HashTable::HashTableNode* HashTable::SearchKey(LinkedList<HashTableNode>* list, const std::string key)
{
    if (list == nullptr)
    {
        return nullptr;
    }

    for (int index = 0; index < _msize(list) / sizeof(LinkedList<HashTableNode>); ++index)
    {
        if (list[index].key.equals(key))
        {
            return list[index];
        }
    }
}

int main()
{
    LinkedList<int> ll;
    ll.AddLinkedListNode(1);
    ll.AddLinkedListNode(2);
    ll.AddLinkedListNode(3);
    ll.AddLinkedListNode(4);
    ll.RetrieveLinkedList();
    ll.DeleteLinkedListNode(2);
    ll.RetrieveLinkedList();

    return 0;
}
