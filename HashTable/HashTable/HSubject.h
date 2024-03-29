#pragma once
#include "Table.h"
#include <list>
#include <sstream>
/// <summary>
/// implument the gennric hash table 
/// the key is a string 
/// the data is a list of strings
/// </summary>
class HSubject :
    public Table<std::list<std::string>, std::string>
{
public:
    HSubject(int n);
    void startNewTable();
    void addSubjectAndTitle(std::string subject, std::string title);
    void printS(std::string subject);
    void printN(std::string subject, int N);
    virtual int h1(std::string key);
    virtual int h2(std::string key);
    virtual std::string show();
    friend std::ostream& operator<<(std::ostream& output, HSubject& h)
    {
        return (output << h.show());
    }
};

