#include "HSubject.h"

HSubject::HSubject(int newSize) : Table(newSize)
{
}

HSubject::~HSubject()
{
	for (int i = 0; i < size(); i++) 
	{
		if(getTable()[i] != NULL)
		{
			delete getTable()[i]->data;
		}
	}
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

void HSubject::printS(std::string subject)
{
	int index = search(subject);
	if (index == -1)
		return;
	
	for (std::list<std::string>::iterator iter = getTable()[index]->data->begin();
		iter != getTable()[index]->data->end(); iter++)
	{
		std::cout<< *iter << "\n";
	}
}

void HSubject::printN(std::string subject, int N)
{
	int index = search(subject);
	if (index == -1)
		return;
	int i = 0;
	for (std::list<std::string>::iterator iter = getTable()[index]->data->begin();
		iter != getTable()[index]->data->end() && i < N; iter++, i++)
	{
		std::cout << *iter << "\n";
	}
}

void HSubject::addSubjectAndTitle(std::string subject, std::string title)
{
	int key = search(subject);
	if (key != -1) 
	{
		getTable()[key]->data->push_front(title);
		return;
	}
	std::list<std::string>* myList = new std::list<std::string>();
	myList->push_front(title);
	insert(myList, subject);
}

std::ostream& operator<<(std::ostream& output,
	 Table<std::list<std::string>*, std::string>::Item* item)
{
	output << "key: " << item->key << "\nvalue:\n";
	for(std::list<std::string>::iterator iter = item->data->begin();
		iter != item->data->end(); iter++)
	{
		output << *iter <<"\n";
	}
	return output;
}


