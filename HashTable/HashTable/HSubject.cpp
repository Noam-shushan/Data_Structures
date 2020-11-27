#include "HSubject.h"

HSubject::HSubject(int n) : Table(n)
{
}

HSubject::~HSubject()
{
}

void HSubject::startNewTable()
{
}

void HSubject::addSubjectAndTitle(std::string subject, std::string title)
{
	int key = search(subject);
	if (key != -1)
	{
		myTable[key]->data.push_front(title);
		return;
	}
	std::list<std::string> myList;
	myList.push_front(title);
	insert(myList, subject);
}

void HSubject::printS(string subject)
{
	int index = search(subject);
	if (index == -1)
		return;

	for (std::list<std::string>::iterator iter = myTable[index]->data.begin();
		iter != myTable[index]->data.end(); iter++)
	{
		std::cout << *iter << "\n";
	}
}

void HSubject::printN(string subject, int N)
{
	int index = search(subject);
	if (index == -1)
		return;
	int i = 0;
	for (std::list<std::string>::iterator iter = myTable[index]->data.begin();
		iter != myTable[index]->data.end() && i < N; iter++, i++)
	{
		std::cout << *iter << "\n";
	}
}

int HSubject::h1(string key)
{
	int result = 0;
	for (std::string::size_type i = 0; i < key.size(); i++) {
		result += key[i];
	}
	return result % size();
}

int HSubject::h2(string key)
{
	int result = 5381;

	for (std::string::size_type i = 0; i < key.size(); i++)
		result = ((result << 5) + result) + key[i];

	return result;
}

string HSubject::show()
{
	stringstream out;
	for (int i = 0; i < size(); i++)
	{
		if (myTable[i] != NULL) {
			out << "key: " << myTable[i]->key << "\ndata: ";
			list<string>::iterator it = myTable[i]->data.begin();
			list<string>::iterator temp;
			for (; it != myTable[i]->data.end(); it++)
			{
				out << *it;
				temp = it;
				if ((++temp) != myTable[i]->data.end())
					out << ", ";
			}
			out << "\n\n";
		}
	}
	return out.str();
}

