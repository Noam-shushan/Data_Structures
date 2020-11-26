#pragma once
#include <string>
#include <iostream>

template <typename T, typename K>
class Table
{
protected:
	enum state { FULL, DELETED };
	class Item
	{
	public:
		T data;
		K key;
		state FLAG;
		Item() {}
		Item(T& d, K& k, state& f) : data(d), key(k), FLAG(f) { }
	};

private:
	Item** myTable;
	int _size;
	int _capacity;

public:
	Table(int newSize);
	~Table();
	int size();
	int capacity();
	int getPrimeSize(int newSize);
	virtual int h1(K key) = 0;
	virtual int h2(K key) = 0;
	int hash(K key, int i);
	int search(K key);
	void insert(T data, K key);
	void remove(K key);
	bool update(T data, K key);
	void print();
	Item* operator[](K key)
	{
		int index = hash(key, 0);
		if (index < 0 || index >= _size)
			throw "table overflow";
		return myTable[index];
	}
	Item** getTable() {
		return myTable;
	}

};

bool isPrime(int num);