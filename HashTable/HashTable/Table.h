#pragma once
#include <string>

template <class T, class K>
class Table
{
protected:
	enum state { empty, full, deleted };
	template <class T, class K>
	class Item
	{
	public:
		T data;
		K key;
		state flag;
		Item() {}
		Item(T d, K k, state f) : data(d), key(k), flag(f) { }
	};

private:	
	Item<T, K> myTable[];
	int size;

public:
	Table(int newSize);
	~Table();
	int getSize();
	int getPrimeSize(int newSize);
	virtual int h1(K key) = 0;
	virtual int h2(K key) = 0;
	int hash(K key, int i);
	int search(K key);
	void insert(T data, K key);
	void remove(T data, K key);
	void update(K key);
	void print();
};

bool isPrime(int num);