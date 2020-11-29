#pragma once
#include <iostream>
#include <string>


template<class T, class K>
class Table {
protected:
    enum state { FULL, DELETED };
    class Item {
    public:
        T data;
        K key;
        state flag;
        Item(T d, K k, state f) : data(d), key(k), flag(f) {}
    };
private:
    int _size;

public:
    Item** myTable;

    Table(int n) {
        _size = getPrimeSize(n);
        myTable = new Item * [_size];
        for (int i = 0; i < size(); i++)
            myTable[i] = NULL;
    }

    ~Table() {
        for (int i = 0; i < size(); i++)
        {
            if (myTable[i] != NULL)
                delete myTable[i];
        }
        delete[] myTable;
    }
    int size() {
        return _size;
    }

    virtual int h1(K key) { return 0; }
    virtual int h2(K key) { return 0; }

    int hash(K key, int i = 0)
    {
        int index = (h1(key) + i * (h2(key) + 1)) % size();
        
        if (i == size())
            return -1;
        
        if (myTable[i] != NULL)
            index = hash(key, i + 1);
        
        return index;
    }

    int search(K key) {
        int index = hash(key, 0);
        if (myTable[index] == NULL)
        {
            return -1;
        }
        if (myTable[index]->flag == DELETED)
        {
            return -1;
        }
        return index;
    }

    void insert(T d, K k) {
        Item* temp = new Item(d, k, FULL);
        int index = hash(k, 0);
        if (index == -1)
        {
            std::cout << "table is full\n";
            return;
        }
        myTable[index] = temp;
    }

    void remove(K key)
    {
        int i = search(key);
        if (i != -1)
            myTable[i]->flag = DELETED;
    }

    void update(T data, K key)
    {
        int i = search(key);
        if (i != -1)
            myTable[i]->data = data;
    }

    virtual std::string show()
    {
        return "";
    }

    void print() {
        std::cout << this->show();
    }

    int getPrimeSize(int newSize)
    {
        if (isPrime(newSize))
            return newSize;
        for (int up = newSize + 1, down = newSize - 1; down > 2; up++, down--)
        {
            if (isPrime(up)) {
                return up;
            }
            else if (isPrime(down)) {
                return down;
            }
        }
        return newSize;
    }

    bool isPrime(int num)
    {
        // Corner case 
        if (num <= 1)
            return false;

        // Check from 2 to n-1 
        for (int i = 2; i < num; i++)
            if (num % i == 0)
                return false;

        return true;
    }
};
