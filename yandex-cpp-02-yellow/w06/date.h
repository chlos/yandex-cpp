#pragma once

#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

class Date {
public:
    Date();
    Date(int y, int m, int d);
    Date (const string& str);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    int year, month, day;
};

void CheckSeparator(stringstream& ss);
void ThrowWrongDateFormat(const stringstream& ss);
void CheckValues(int m, int d);

bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& stream, const Date& date);

Date ParseDate(istream& s);
