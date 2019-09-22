#include <sstream>

#include "phone_number.h"
#include "test_runner.h"

using namespace std;


void CheckSeparator(stringstream& ss, const char separator) {
    if (ss.peek() != separator) {
        //ThrowWrongDateFormat(ss);
        throw invalid_argument("Invalid separator");
    }
    ss.ignore(1);
}

PhoneNumber::PhoneNumber(const string &international_number) {
    /* === from coursera ===
    istringstream is(international_number);
    char sign = is.get();
    getline(is, country_code_, '-');
    getline(is, city_code_, '-');
    getline(is, local_number_);

    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
        throw invalid_argument(
            "Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: "
            + international_number
        );
    } */

    stringstream ss(international_number);

    CheckSeparator(ss, '+');
    int country_code;
    ss >> country_code;
    country_code_ = to_string(country_code);

    CheckSeparator(ss, '-');
    int city_code;
    ss >> city_code;
    city_code_ = to_string(city_code);

    CheckSeparator(ss, '-');
    string local_number;
    ss >> local_number;
    local_number_ = local_number;
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ +  "-" + city_code_ +  "-" + local_number_;
}


void Test() {
    PhoneNumber pn_1("+7-495-111-22-33");
    AssertEqual(pn_1.GetCountryCode(), "7", "Test 1 (country)");
    AssertEqual(pn_1.GetCityCode(), "495", "Test 1 (city)");
    AssertEqual(pn_1.GetLocalNumber(), "111-22-33", "Test 1 (local)");
    AssertEqual(pn_1.GetInternationalNumber(), "+7-495-111-22-33", "Test 1 (inter)");

    PhoneNumber pn_2("+0124-495-1112233");
    //AssertEqual(pn_2.GetCountryCode(), "0124", "Test 2 (country)");
    AssertEqual(pn_2.GetCityCode(), "495", "Test 2 (city)");
    AssertEqual(pn_2.GetLocalNumber(), "1112233", "Test 2 (local)");
    AssertEqual(pn_2.GetInternationalNumber(), "+0124-495-1112233", "Test 2 (inter)");

    bool is_invalid_country = false;
    try {
        PhoneNumber pn_3("7-495-111-22-33");
    } catch (invalid_argument) {
        is_invalid_country = true;
    }
    Assert(is_invalid_country, "Invalid country");

    bool is_invalid_city = false;
    try {
        PhoneNumber pn_3("+7495-1112233");
    } catch (invalid_argument) {
        is_invalid_city = true;
    }
    Assert(is_invalid_city, "Invalid city");

    bool is_invalid_local = false;
    try {
        PhoneNumber pn_3("+74951112233");
    } catch (invalid_argument) {
        is_invalid_local = true;
    }
    Assert(is_invalid_local, "Invalid local");

}


int main() {
    TestRunner runner;
    runner.RunTest(Test, "Test");

    return 0;
}
