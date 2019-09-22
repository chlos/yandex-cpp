#pragma once

#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

#include "date.h"

using namespace std;


struct Entry {
    Date date;
    string event;
};


ostream& operator<< (ostream& ost, const Entry& entry);
ostream& operator<< (ostream& ost, const vector<Entry>& events);
ostream& operator<< (ostream& ost, const vector<string>& events);
bool operator< (const Entry& A, const Entry& B);
bool operator== (const Entry& A, const Entry& B);
bool operator== (const Entry& A, const Entry& B);
bool operator!= (const Entry& A, const Entry& B);
bool operator== (const string& A, const Entry& B);
bool operator!= (const string& A, const Entry& B);


class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& out) const;
    string Last(const Date& date) const;
    vector<Entry> FindIf(const function<bool(const Date&, const string&)> pred) const;
    int RemoveIf(const function<bool(const Date&, const string&)> pred);

private:
    map<Date, vector<string>> _eventsByDate;
    set<Entry> _entriesUnique;
};
