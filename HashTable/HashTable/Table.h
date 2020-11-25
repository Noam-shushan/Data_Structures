#pragma once
#include <string>
#include <iostream>
#include <vector>

template <class T, class K>
class Table
{
protected:
	enum state { full, deleted };
	class Item
	{
	public:
		T data;
		K key;
		state flag;
		Item() {}
		Item(T& d, K& k, state& f) : data(d), key(k), flag(f) { }
	};

private:	
	std::vector<Item*> myTable;
	int _size;
	int _capacity;

public:
	Table(int newSize);
	~Table();
	int size();
	int capacity();
	int getPrimeSize(int newSize);
	virtual int h1(K key) {}
	virtual int h2(K key) {}
	int hash(K key, int i);
	int search(K key);
	void insert(T data, K key);
	void remove(K key);
	void update(T data, K key);
	void print();
	Item* operator[](K key) {
		int index = hash(key, 0);
		if (index < 0 || index >= _size)
			throw "table overflow";
		return myTable[index];
	}
};

bool isPrime(int num);