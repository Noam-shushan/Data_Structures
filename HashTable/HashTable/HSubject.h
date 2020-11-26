#pragma once
#include "Table.h"
#include <list>

class HSubject :
    public Table<std::list<std::string>*, std::string>
{
public:
    HSubject(int newSize);
    ~HSubject();
    void startNewTable() {}
    friend std::ostream& operator<<(std::ostream& output,
         Table<std::list<std::string>*, std::string>::Item*);
    int h1(std::string key);
    int h2(std::string key);
    void printS(std::string subject);
    void printN(std::string subject, int N);
    void addSubjectAndTitle(std::string subject, std::string title);
};

