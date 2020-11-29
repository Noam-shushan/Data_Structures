#include "HSubject.h"
/// <summary>
/// constructor
/// </summary>
/// <param name="n"></param>
HSubject::HSubject(int n) : Table(n)
{
}

void HSubject::startNewTable()
{
}
/// <summary>
/// Add a new subject with a new title to the table
/// or add a new title to an existing subject in the table
/// </summary>
/// <param name="subject"></param>
/// <param name="title"></param>
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
/// <summary>
/// print the data of an a given subject
/// </summary>
/// <param name="subject"></param>
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
/// <summary>
/// print N titles of a given subject
/// </summary>
/// <param name="subject"></param>
/// <param name="N">the number of title to print</param>
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
/// <summary>
/// the first hash function 
/// </summary>
/// <param name="key"></param>
/// <returns>sum of all ascii value in the key mod by the size of the table</returns>
int HSubject::h1(std::string key)
{
	int result = 0;
	for (std::string::size_type i = 0; i < key.size(); i++) {
		result += key[i]; // suming the caracters by the ascii value
	}
	return result % size();
}
/// <summary>
/// the second hash function
/// good hashing function that i found on web
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
int HSubject::h2(std::string key)
{
	int result = 5381;

	for (std::string::size_type i = 0; i < key.size(); i++)
		result = ((result << 5) + result) + key[i];

	return result;
}
/// <summary>
/// show all data of any entry in the table
/// </summary>
/// <returns>string contian all the infromtion</returns>
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
				if ((++temp) != myTable[i]->data.end()) //to avoid the last one
					out << ", ";
			}
			out << "\n";
		}
	}
	return out.str();
}

