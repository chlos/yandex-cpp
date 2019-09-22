#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Specialization {
    Specialization(const string& new_value) {
        value = new_value;
    }

    string value;
};

struct Course {
    explicit Course(const string& new_value) {
        value = new_value;
    }

    string value;
};

struct Week {
    explicit Week(const string& new_value) {
        value = new_value;
    }

    string value;
};

struct LectureTitle {
    explicit LectureTitle(
        const Specialization& new_specialization,
        const Course& new_course,
        const Week& new_week
    ) {
        specialization = new_specialization.value;
        course = new_course.value;
        week = new_week.value;
    }
    string specialization;
    string course;
    string week;
};

//int main() {
    // ok
    //LectureTitle title(
        //Specialization("C++"),
        //Course("White belt"),
        //Week("4th")
    //);

    // not ok
    //LectureTitle title("C++", "White belt", "4th");

    //LectureTitle title(string("C++"), string("White belt"), string("4th")); //FIXME

    //LectureTitle title = {"C++", "White belt", "4th"};

    //LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}}; // FIXME

    //LectureTitle title(
        //Course("White belt"),
        //Specialization("C++"),
        //Week("4th")
    //);

    //LectureTitle title(
        //Specialization("C++"),
        //Week("4th"),
        //Course("White belt")
    //);
//}
