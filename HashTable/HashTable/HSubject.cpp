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

void HSubject::printS(std::string subject)
{
	int index = search(subject);

	if (index == -1)
	{
		std::cout << "ERROR\n";
		return;
	}

	for (std::list<std::string>::iterator iter = myTable[index]->data.begin();
		iter != myTable[index]->data.end(); iter++)
	{
		std::cout << *iter << " ";
	}
	std::cout << "\n";
}

void HSubject::printN(std::string subject, int N)
{
	int index = search(subject);
	if (index == -1)
	{
		std::cout << "ERROR\n";
		return;
	}
	int i = 0;
	for (std::list<std::string>::iterator iter = myTable[index]->data.begin();
		iter != myTable[index]->data.end() && i < N; iter++, i++)
	{
		std::cout << *iter << " ";
	}
	std::cout << "\n";
}

int HSubject::h1(std::string key)
{
	int result = 0;
	for (std::string::size_type i = 0; i < key.size(); i++) {
		result += key[i];
	}
	return result % size();
}

int HSubject::h2(std::string key)
{
	int result = 5381;

	for (std::string::size_type i = 0; i < key.size(); i++)
		result = ((result << 5) + result) + key[i];

	return result;
}

std::string HSubject::show()
{
	std::stringstream out;
	for (int i = 0; i < size(); i++)
	{
		if (myTable[i] != NULL && myTable[i]->flag != DELETED) 
		{
			out << myTable[i]->key << ": ";
			std::list<std::string>::iterator iter = myTable[i]->data.begin();
			std::list<std::string>::iterator temp;
			for (; iter != myTable[i]->data.end(); iter++)
			{
				out << *iter;
				temp = iter;
				if ((++temp) != myTable[i]->data.end())
					out << ", ";
			}
			out << "\n";
		}
	}
	return out.str();
}

