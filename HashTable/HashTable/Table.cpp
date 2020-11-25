#include "Table.h"

/// <summary>
/// constractor
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
/// <param name="newSize"></param>
template<class T, class K>
Table<T, K>::Table(int newSize)
{
    _size = getPrimeSize(newSize);
    myTable.assign(size(), NULL);
}

template<class T, class K>
Table<T, K>::~Table()
{
    for (int i = 0; i < size(); i++)
    {
        if (myTable[i] != NULL)
            delete myTable[i];
    }
}

template<class T, class K>
int Table<T, K>::getPrimeSize(int newSize)
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
}

template<class T, class K>
int Table<T, K>::size()
{
    return _size;
}

template<class T, class K>
int Table<T, K>::capacity()
{
    return _capacity;
}


template<class T, class K>
int Table<T, K>::hash(K key, int i)
{
    int index = (h1(key) + i * (h2(key) + 1)) % size();
    if (i == size())
        return -1;
    if (myTable[index] == NULL)
        return index;
    if (myTable[index].flag == full)
        index = hash(key, i + 1);
    return index;
}

template<class T, class K>
int Table<T, K>::search(K key)
{
    int index = hash(key, 0);
    if (myTable[index] == NULL)
    {
        return -1;
    }
    if (myTable[index].flag == deleted)
    {
        return -1;
    }
    return index;
}

template<class T, class K>
void Table<T, K>::insert(T data, K key)
{
    int i = hash(key, 0);
    if (i == -1)
    {
        return;
    }
    myTable[i] = new Item(data, key, full);
    _capacity++;
}

template<class T, class K>
void Table<T, K>::remove(K key)
{
    int i = search(key);
    if (i == -1)
    {
        return;
    }
    myTable[i].flag = deleted;
}

template<class T, class K>
void Table<T, K>::update(T data, K key)
{
    int i = search(key);
    if (i != -1)
    {
        myTable[i].data = data;
    }
}

template<class T, class K>
void Table<T, K>::print()
{
    for (int i = 0; i < size(); i++) {
        if (myTable[i] != NULL)
        {
            std::cout << "key = " << myTable[i]->key << " value = " << myTable[i]->data << "\n";
        }
    }
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
