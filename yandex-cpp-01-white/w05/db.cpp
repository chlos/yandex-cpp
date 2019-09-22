#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

class Date {
public:
    Date() {
        year = 0;
        month = 0;
        day = 0;
    }

    Date(int y, int m, int d) {
        CheckValues(m, d);

        year = y;
        month = m;
        day = d;
    }

    Date (const string& str) {
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

    int GetYear() const {
        return year;
    };

    int GetMonth() const {
        return month;
    };

    int GetDay() const {
        return day;
    };

private:
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
        if (m < 1 || m > 12) {
            throw runtime_error("Month value is invalid: " + to_string(m));
        }
        if (d < 1 || d > 31) {
            throw runtime_error("Day value is invalid: " + to_string(d));
        }
    }

    int year, month, day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
}

ostream& operator<<(ostream& stream, const Date& date) {
    cout << setfill('0');
    stream << setw(4) << date.GetYear() << "-"
           << setw(2) << date.GetMonth() << "-"
           << setw(2) << date.GetDay();
    return stream;
}


class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        db[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (db.count(date)) {
            if (db[date].count(event)) {
                db[date].erase(event);
                return true;
            }
        }
        return false;
    }

    int  DeleteDate(const Date& date) {
        int deleted_num = 0;
        if (db.count(date)) {
            deleted_num = db[date].size();
            db.erase(date);
        }

        return deleted_num;
    }

    set<string> Find(const Date& date) const {
        set<string> events;
        if (db.count(date)) {
            for (const auto& event : db.at(date)) {
                events.insert(event);
            }
        }

        return events;
    }

    void Print() const {
        for (const auto& entry : db) {
            for (const auto& event : entry.second) {
                cout << entry.first << " " << event << endl;
            }
        }
    }

private:
    map<Date, set<string>> db;
};


void parse_command(const string& command, Database& db) {
    stringstream command_ss(command);
    string action = "";
    string date_s = "";
    string event = "";
    getline(command_ss, action, ' ');
    getline(command_ss, date_s, ' ');
    getline(command_ss, event, ' ');

    if (action == "") {
        return;
    }

    Date date;
    if (action == "Add" || action == "Del" || action == "Find") {
        try {
            date = Date(date_s);
        } catch (exception &e) {
            cout << e.what() << endl;
            return;
        }
    }

    if (action == "Add") {
        db.AddEvent(date, event);
    } else if (action == "Del") {
        if (event != "") {
            if (db.DeleteEvent(date, event)) {
                cout << "Deleted successfully" << endl;
            } else {
                cout << "Event not found" << endl;
            }
        } else {
            int deleted_num = db.DeleteDate(date);
            cout << "Deleted " << deleted_num << " events" << endl;
        }
    } else if (action == "Find") {
        set<string> events = db.Find(date);
        for (const auto& e : events) {
            cout << e << endl;
        }
    } else if (action == "Print") {
        db.Print();
    } else {
        cout << "Unknown command: " << action << endl;
    }
}

int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
      parse_command(command, db);
  }

  return 0;
}
