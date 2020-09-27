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
        LinkedListNode() : mNextLinkedListNode(nullptr) {}

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

    LinkedListNode* mLinkedListHeader;
}; // end LinkedList struct

struct HashTable
{
    struct HashTableNode
    {
        HashTableNode() {}
        HashTableNode(const std::string key, const std::string value) : mHashKey(key), mHashValue(value) {}

        std::string mHashKey;
        std::string mHashValue;
    }; // end HashTableNode struct

    HashTable(const int size) : mHashTableData(new LinkedList<HashTable::HashTableNode>[size]) {}
    int GetHashCode(const std::string key) const;
    int ConvertToIndex(const int hashCode) const;
    HashTableNode* SearchKey(LinkedList<HashTable::HashTableNode>* list, const std::string key);
    void PutHash(const std::string key, const std::string value);
    std::string GetHash(std::string key);

    LinkedList<HashTable::HashTableNode>* mHashTableData;
}; // end HashTable struct

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
    size_t linkedListSize = _msize(mHashTableData) / sizeof(mHashTableData);

    return hashCode % linkedListSize;
}

HashTable::HashTableNode* HashTable::SearchKey(LinkedList<HashTable::HashTableNode>* list, const std::string key)
{
    if (list->mLinkedListHeader == nullptr)
    {
        return nullptr;
    }

    LinkedList<HashTable::HashTableNode>::LinkedListNode* iter = list->mLinkedListHeader;
    while (iter->mNextLinkedListNode != nullptr)
    {
        if (iter->mNextLinkedListNode->mLinkedListData.mHashKey == key)
        {
            return &(iter->mNextLinkedListNode->mLinkedListData);
        }
        else
        {
            iter = iter->mNextLinkedListNode;
        }
    }

    return nullptr;
}

void HashTable::PutHash(const std::string key, const std::string value)
{
    int hashCode = GetHashCode(key);
    int index = ConvertToIndex(hashCode);
    LinkedList<HashTable::HashTableNode>* list = &(mHashTableData[index]);
    if (list->mLinkedListHeader == nullptr)
    {
        list = new LinkedList<HashTable::HashTableNode>();
        mHashTableData[index] = *list;
    }

    HashTable::HashTableNode* node = SearchKey(list, key);
    if (node == nullptr)
    {
        HashTable::HashTableNode newHashTableNode(key, value);
        list->AddLinkedListNode(newHashTableNode);
    }
    else
    {
        node->mHashValue = value;
    }
}

std::string HashTable::GetHash(std::string key)
{
    int hashCode = GetHashCode(key);
    int index = ConvertToIndex(hashCode);
    LinkedList<HashTable::HashTableNode>* list = &(mHashTableData[index]);
    HashTable::HashTableNode* node = SearchKey(list, key);

    return node == nullptr ? "Not Found" : node->mHashValue;
}

int main()
{
    HashTable h(3);
    h.PutHash("sung", "She is pretty");
    h.PutHash("jin", "She is a model");
    h.PutHash("hee", "She is an angel");
    h.PutHash("min", "She is cute");
    h.PutHash("sung", "She is cute");
    std::cout << h.GetHash("sung") << std::endl;
    std::cout << h.GetHash("jin") << std::endl;
    std::cout << h.GetHash("hee") << std::endl;
    std::cout << h.GetHash("min") << std::endl;
    std::cout << h.GetHash("jae") << std::endl;
    
    return 0;
}
