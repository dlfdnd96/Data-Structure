/*
*** 2개의 stack으로 하나의 queue를 구현하라
*/

#include <iostream>
#include <stack>

using std::cout;
using std::endl;

template <typename T>
class Queue
{
public:
    Queue()
    {
        this->mStackNewest = new std::stack<T>();
        this->mStackOldest = new std::stack<T>();
    }
    const int GetSize() const
    {
        return mStackNewest->size() + mStackOldest->size();
    }
    void Add(T value)
    {
        mStackNewest->push(value);
    }
    const T DoPeek() const
    {
        return mStackOldest->top();
    }
    const T DoRemove()
    {
        shiftStacks();

        T stackOldestValue = mStackOldest->top();
        mStackOldest->pop();

        return stackOldestValue;
    }

private:
    std::stack<T>* mStackNewest;
    std::stack<T>* mStackOldest;

    void shiftStacks()
    {
        if (mStackOldest->empty())
        {
            while (!mStackNewest->empty())
            {
                T stackNewestValue = mStackNewest->top();
                mStackNewest->pop();
                mStackOldest->push(stackNewestValue);
            }
        }
    }
}; // end Queue class

int main()
{
    const std::unique_ptr<Queue<int>> queueUniquePointer = std::make_unique<Queue<int>>();
    queueUniquePointer->Add(1);
    queueUniquePointer->Add(2);
    queueUniquePointer->Add(3);
    cout << queueUniquePointer->DoRemove() << endl;
    cout << queueUniquePointer->DoRemove() << endl;
    cout << queueUniquePointer->DoRemove() << endl;

    return 0;
}
