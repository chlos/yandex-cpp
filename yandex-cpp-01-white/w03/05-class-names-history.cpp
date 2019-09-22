#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_name_years[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        last_name_years[year] = last_name;
    }

    string GetFullName(int year) {
        string first_name = GetName(first_name_years, year);
        string last_name = GetName(last_name_years, year);
        return PrepareFullNameToPrint(first_name, last_name);
    }

    string GetFullNameWithHistory(int year) {
        string full_first_name = GetAllNames(first_name_years, year);
        string full_last_name = GetAllNames(last_name_years, year);
        return PrepareFullNameToPrint(full_first_name, full_last_name);
    }

private:
    map<int, string> first_name_years;
    map<int, string> last_name_years;

    string GetName(const map<int, string>& name_years, int year) {
        for (int year_curr = year; year_curr >= 0; --year_curr) {
            if (name_years.count(year_curr)) {
                return name_years.at(year_curr);
            }
        }

        return "";
    }

    string GetAllNames(const map<int, string>& name_years, int year) {
        string names_history = "";
        string previous_name_found = "";
        bool history_begin = true;

        for (int year_curr = year; year_curr >= 0; --year_curr) {
            if (name_years.count(year_curr)) {
                string name_found = name_years.at(year_curr);
                if (name_found == previous_name_found) {
                    continue;
                }

                if (names_history == "") {
                    names_history += name_found;
                } else {
                    if (history_begin) {
                        names_history += " (";
                        names_history += name_found;
                        history_begin = false;
                    } else {
                        names_history += ", ";
                        names_history += name_found;
                    }
                }

                previous_name_found = name_found;
            }
        }
        if (!history_begin) {
            names_history += ")";
        }


        return names_history;
    }

    string PrepareFullNameToPrint(const string& first_name, const string& last_name) {
        if(first_name == "" && last_name == "") {
            return "Incognito";
        } else if (first_name != "" && last_name == "") {
            return first_name + " with unknown last name";
        } else if (first_name == "" && last_name != "") {
            return last_name + " with unknown first name";
        }

        return first_name + " " + last_name;
    }
};

//int main() {
    //Person person;

    //person.ChangeFirstName(1900, "Eugene");
    //person.ChangeFirstName(1901, "Eugene1901");
    //person.ChangeFirstName(1902, "Eugene");
    //person.ChangeFirstName(1903, "Eugene");
    //person.ChangeFirstName(1920, "Evgeny");
    //person.ChangeLastName(1900, "Sokolov");
    //person.ChangeLastName(1910, "Sokolov");
    //person.ChangeLastName(1910, "Sokoloff");
    //person.ChangeLastName(1930, "Sokolov");
    //cout << person.GetFullNameWithHistory(1940) << endl;

    //return 0;
//}
