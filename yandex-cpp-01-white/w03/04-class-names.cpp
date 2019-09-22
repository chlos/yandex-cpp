#include <iostream>
#include <map>
#include <string>

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
        if(first_name == "" && last_name == "") {
            return "Incognito";
        } else if (first_name != "" && last_name == "") {
            return first_name + " with unknown last name";
        } else if (first_name == "" && last_name != "") {
            return last_name + " with unknown first name";
        }

        return first_name + " " + last_name;
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
};

//void PrintSortedStrings(SortedStrings& strings) {
    //for (const string& s : strings.GetSortedStrings()) {
        //cout << s << " ";
    //}
    //cout << endl;
//}

//int main() {
    //Person person;

    ////person.ChangeFirstName(1965, "Polina");
    //person.ChangeLastName(1967, "Sergeeva");
    //for (int year : {1900, 1965, 1990}) {
        //cout << person.GetFullName(year) << endl;
    //}

    //person.ChangeFirstName(1970, "Appolinaria");
    //for (int year : {1969, 1970}) {
        //cout << person.GetFullName(year) << endl;
    //}

    //person.ChangeLastName(1968, "Volkova");
    //for (int year : {1969, 1970}) {
        //cout << person.GetFullName(year) << endl;
    //}

    //return 0;
//}
