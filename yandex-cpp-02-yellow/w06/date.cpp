#include "date.h"

Date::Date() {
    year = 0;
    month = 0;
    day = 0;
}

Date::Date(int y, int m, int d) {
    CheckValues(m, d);

    year = y;
    month = m;
    day = d;
}

Date::Date (const string& str) {
    int y, m, d;
    stringstream ss(str);
    ss >> y;
    CheckSeparator(ss);
    ss >> m;
    CheckSeparator(ss);
    ss >> d;
    if (!ss.eof()) {
        ThrowWrongDateFormat(ss);
    }

    CheckValues(m, d);

    year = y;
    month = m;
    day = d;
}

int Date::GetYear() const {
    return year;
};

int Date::GetMonth() const {
    return month;
};

int Date::GetDay() const {
    return day;
};


void CheckSeparator(stringstream& ss) {
    if (ss.peek() != '-') {
        ThrowWrongDateFormat(ss);
    }
    ss.ignore(1);
}

void ThrowWrongDateFormat(const stringstream& ss) {
    throw runtime_error("Wrong date format: " + ss.str());
}

void CheckValues(int m, int d) {
    if (m < 0 || m > 12) {
        throw runtime_error("Month value is invalid: " + to_string(m));
    }
    if (d < 0 || d > 31) {
        throw runtime_error("Day value is invalid: " + to_string(d));
    }
}


bool operator==(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() == rhs.GetDay();
        }
        return false;
    }
    return false;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs == rhs || lhs < rhs;
}

bool operator>(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() > rhs.GetDay();
        }
        return lhs.GetMonth() > rhs.GetMonth();
    }
    return lhs.GetYear() > rhs.GetYear();
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return lhs == rhs || lhs > rhs;
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() << '-'
           << setw(2) << setfill('0') << date.GetMonth() << '-'
           << setw(2) << setfill('0') << date.GetDay();
    return stream;
}


Date ParseDate(istream& is) {
    string date_s;
    //getline(s, date_s, ' ');  // FIXME
    is >> date_s;
    return Date(date_s);
}
