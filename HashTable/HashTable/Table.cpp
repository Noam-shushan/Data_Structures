#include "Table.h"

/// <summary>
/// constractor
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
/// <param name="newSize"></param>
template<class T, class K>
inline Table<T, K>::Table(int newSize)
{
    size = getPrimeSize(newSize);
	myTable = new Item[size];
}

template<class T, class K>
Table<T, K>::~Table()
{
    for (int i = 0; i < getSize(); i++)
        delete myTable[i];
    delete[] myTable;
}

template<class T, class K>
inline int Table<T, K>::getPrimeSize(int newSize)
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
int Table<T, K>::getSize()
{
    return size;
}

template<class T, class K>
int Table<T, K>::hash(K key, int i)
{
    int index = h1(key) + i * h2(key);
    if (myTable[index].flag == full)
        index = hash(key, i + 1);
    return index;
}
 
template<class T, class K>
inline int Table<T, K>::search(K key)
{
    int index = hash(key, 0);
    if (myTable[index].falg == deleted) 
    {
        std::count << "this item is deleted\n";
        return -1;
    }
    if (myTable[index].falg == empty)
    {
        std::count << "this item is empty\n";
        return -1;
    }
    return index;
}

template<class T, class K>
inline void Table<T, K>::insert(T& data, K& key)
{
    int i = hash(key);

    myTable[] = new Item(data, key, full);
}

template<class T, class K>
inline void Table<T, K>::remove(T& data, K& key)
{
    
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
