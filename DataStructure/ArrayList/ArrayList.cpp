/*
*** 자바의 ArrayList를 구현하라
*/
#include <iostream>

template <typename T>
class ArrayList
{
public:
    ArrayList()
    {
        this->mSize = 1;
        this->mData = new T[this->mSize];
        this->mIndex = 0;
    }
    void Add(T obj)
    {
        if (this->mIndex == this->mSize - 1)
        {
            doubling();
        }

        this->mData[this->mIndex] = obj;
        ++(this->mIndex);
    }
    T Get(int index)
    {
        if (index > this->mIndex - 1)
        {
            throw std::out_of_range("ArrayIndexOutOfBound");
        }
        else if (index < 0)
        {
            throw std::invalid_argument("Negative Value");
        }

        return this->mData[index];
    }
    void Remove(int index)
    {
        if (index > this->mIndex - 1)
        {
            throw std::out_of_range("ArrayIndexOutOfBound");
        }
        else if (index < 0)
        {
            throw std::invalid_argument("Negative Value");
        }

        for (int x = index; x < sizeof(this->mData) - 1; ++x)
        {
            mData[x] = mData[x + 1];
        }

        --(this->mIndex);
    }
private:
    void doubling()
    {
        this->mSize = this->mSize * 2;
        T* newData = new T[this->mSize];
        for (int index = 0; index < sizeof(mData); ++index)
        {
            newData[index] = mData[index];
        }

        mData = newData;
    }
private:
    T* mData;
    int mSize;
    int mIndex;
};

int main()
{
    ArrayList<char>* al = new ArrayList<char>();
    try
    {
        al->Add('0');
        al->Add('1');
        al->Add('2');
        al->Add('3');
        al->Add('4');
        al->Add('5');
        al->Add('6');
        al->Add('7');
        al->Add('8');
        al->Add('9');

        std::cout << al->Get(5) << std::endl;
        al->Remove(5);
        std::cout << al->Get(5) << std::endl;
        std::cout << al->Get(110) << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception Occur: " << e.what() << std::endl;
    }

    return 0;
}
