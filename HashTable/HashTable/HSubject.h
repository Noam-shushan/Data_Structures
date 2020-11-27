#pragma once
#include "Table.h"
#include <list>
#include <sstream>

class HSubject :
    public Table<list<string>, string>
{
public:
    HSubject(int n);
    ~HSubject();
    void startNewTable();
    void addSubjectAndTitle(string subject, string title);
    void printS(string subject);
    void printN(string subject, int N);
    virtual int h1(string key);
    virtual int h2(string key);
    virtual string show();
    friend ostream& operator<<(ostream& output, HSubject& h)
    {
        return (output << h.show());
    }
};

