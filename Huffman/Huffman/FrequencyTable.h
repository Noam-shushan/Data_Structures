#pragma once
#include <map>
#include <string>

class FrequencyTable
{
	std::map<char, int> myTable;
public:
	FrequencyTable(std::string word);
	void add(char c);
	std::map<char, int>::iterator begin();
	std::map<char, int>::iterator end();
};

