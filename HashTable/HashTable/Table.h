#pragma once
#include <iostream>
#include <string>

/// <summary>
/// Generic hash table application with open addrasing
/// can receive any type of key and any type of data
/// when the hashing functions have to be implemented
/// </summary>
/// <typeparam name="K">the key of the entry</typeparam>
/// <typeparam name="T">the data of the entry</typeparam>
template<class T, class K>
class Table {
protected:
    enum state { FULL, DELETED };
    /// <summary>
    /// one entry in the table
    /// </summary>
    class Item {
    public:
        T data;
        K key;
        state flag;
        Item(T d, K k, state f) : data(d), key(k), flag(f) {}
    };
private:
    int _size; // the size of the table

public:
    Item** myTable; // the table
    /// <summary>
    /// constractor
    /// </summary>
    /// <param name="n">size of the table</param>
    Table(int n) {
        _size = getPrimeSize(n); // get prime number clost to the nubmer that input
        myTable = new Item * [_size];
        for (int i = 0; i < size(); i++)
            myTable[i] = NULL; // Initializes the table
    }
    /// <summary>
    /// distractor
    /// </summary>
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
    /// <summary>
    /// hashing functions that need to override
    /// </summary>
    /// <param name="key"></param>
    /// <returns>the hashing index</returns>
    virtual int h1(K key) { return 0; }
    virtual int h2(K key) { return 0; }
    /// <summary>
    /// the main hash function work in double hasing
    /// </summary>
    /// <param name="key">the key to hash</param>
    /// <param name="i">An indicator that moves to the next item
    ///  to avoid collisions </param>
    /// <returns>the final hashing index</returns>
    int hash(K key, int i = 0) 
    {
        int index = (h1(key) + i * (h2(key) + 1)) % size();
        
        if (i == size()) // the table is full
            return -1;
        
        if (myTable[i] != NULL) // not empty entry
            index = hash(key, i + 1);
        
        return index;
    }
    /// <summary>
    /// search the entry of the given key
    /// </summary>
    /// <param name="key"></param>
    /// <returns>the index of the entry in the table</returns>
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
    /// <summary>
    /// Insert a new entry the the table
    /// </summary>
    /// <param name="d">the data of the entry</param>
    /// <param name="k">the key of the entry</param>
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
    /// <summary>
    /// Remove an entry from the table by marking the entry as deleted 
    /// </summary>
    /// <param name="key">the key of the entry</param>
    void remove(K key)
    {
        int i = search(key);
        if (i != -1)
            myTable[i]->flag = DELETED;
    }
    /// <summary>
    /// Update the data of a gevin entry
    /// </summary>
    /// <param name="data"></param>
    /// <param name="key"></param>
    void update(T data, K key)
    {
        int i = search(key);
        if (i != -1)
            myTable[i]->data = data;
    }
    /// <summary>
    /// the output of the table, need to overrid in the inheritance class
    /// </summary>
    /// <returns></returns>
    virtual std::string show()
    {
        return "";
    }
    /// <summary>
    /// print all the data of any entry in the table
    /// </summary>
    void print() {
        std::cout << this->show();
    }
    /// <summary>
    /// Get prime number that is close to the given number of the size 
    /// </summary>
    /// <param name="newSize"></param>
    /// <returns>prime size</returns>
    int getPrimeSize(int newSize)
    {
        if (isPrime(newSize))
            return newSize;
        for (int up = newSize + 1, down = newSize - 1; down > 2; up++, down--)
        {
            if (isPrime(up)) { // go up
                return up;
            }
            else if (isPrime(down)) { // go down
                return down;
            }
        }
        return newSize;
    }
    /// <summary>
    /// check if a given number is a prime number
    /// </summary>
    /// <param name="num"></param>
    /// <returns></returns>
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
