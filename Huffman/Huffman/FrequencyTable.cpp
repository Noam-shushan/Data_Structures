#include "FrequencyTable.h"

FrequencyTable::FrequencyTable(std::string word)
{
	for (int i = 0; i < word.size(); i++)
		add(word[i]);
}

void FrequencyTable::add(char c)
{
	if (myTable.find(c) != myTable.end())
		myTable.find(c)->second++;
	else
		myTable.insert(std::pair<char, int>(c, 1));
}

std::map<char, int>::iterator FrequencyTable::begin()
{
	return myTable.begin();
}

std::map<char, int>::iterator FrequencyTable::end()
{
	return myTable.end();
}