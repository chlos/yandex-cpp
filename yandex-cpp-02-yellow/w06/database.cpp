#include "database.h"


ostream& operator << (ostream& ost, const Entry& entry) {
    ost << entry.date << ' ' << entry.event;
    return ost;
}
ostream& operator << (ostream& ost, const vector<Entry>& events) {
    for (const Entry& e : events) {
        ost << e << endl;
    }
    return ost;
}
ostream& operator << (ostream& ost, const vector<string>& events) {
    for (const string& ev : events){
        ost << ev << " ";
    }
    return ost;
}

bool operator < (const Entry& A, const Entry& B) {
    if (A.date == B.date) {
        return A.event < B.event;
    }
    else {
        return A.date < B.date;
    }
}
bool operator == (const Entry& A, const Entry& B) {
    return (A.date == B.date) && (A.event == B.event);
}
bool operator != (const Entry& A, const Entry& B) {
    return !(A == B);
}
bool operator == (const string& A, const Entry& B) {
    stringstream ss;
    ss << B.date << ' ' << B.event;
    return (A == B.event || A == ss.str());
}
bool operator != (const string& A, const Entry& B) {
    return !(A == B);
}


void Database::Add(const Date& date, const string& event) {
    if (_entriesUnique.count({date, event}) == 0) {
        _eventsByDate[date].push_back(event);
        _entriesUnique.insert({date, event});
    }
}

void Database::Print(ostream& out) const {
    for (const auto& Day : _eventsByDate){
        if(!Day.second.empty()) {
            for(const string& event : Day.second){
                out << Day.first << " " << event << endl;
            }
        }
    }
}

string Database::Last(const Date& date) const {
    stringstream result;
    if (date == Date{0,0,0}) throw invalid_argument("No entries");;

    auto firstGreaterIt = _eventsByDate.upper_bound(date);
    if (firstGreaterIt != begin(_eventsByDate)) {
        // the last date less or equal to date:
        auto lastNotGreaterIt = prev(firstGreaterIt);
        // if there are events at this date
        if (!lastNotGreaterIt->second.empty()) {
            result << lastNotGreaterIt->first << " " << lastNotGreaterIt->second.back();
        }
        return result.str();
    } else {
        throw invalid_argument("No entries");
    }
}

vector<Entry> Database::FindIf(const function<bool(const Date&, const string&)> pred) const {
    vector<Entry> found;
    for (const auto& entry : _eventsByDate) {
        for(const auto& event : entry.second) {
            if (pred(entry.first, event)) {
                found.push_back({entry.first, event});
            }
        }
    }
    return found;
}

int Database::RemoveIf(const function<bool(const Date&, const string&)> pred) {
    int count2 = 0, total = 0;
    for (auto& entry : _eventsByDate) {
        int del = 0;
        const Date& date = entry.first;

        auto bound = stable_partition(
            entry.second.begin(),
            entry.second.end(),
            [date, pred] (const string& event) {
                bool Erase = pred(date, event);
                return !Erase;
            }
        );

        if (bound != entry.second.end()) {
            del = entry.second.end() - bound;
        }

        for(int i = 0; i < del; ++i) {
            if(!entry.second.empty()) {
                Entry entry_to_erase {date, entry.second.back()};
                _entriesUnique.erase(entry_to_erase);
                entry.second.pop_back();
                ++count2;
            } else {
                _eventsByDate.erase(date);
            }
        }

        total += count2;
        count2 = 0;
        if(entry.second.empty()) {
            _eventsByDate.erase(date);
        }
    }
    return total;
}
