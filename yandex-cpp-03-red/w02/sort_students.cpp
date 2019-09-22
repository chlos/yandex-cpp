#include "student.h"
#include "test_runner.h"
#include "profile.h"

#include <algorithm>

using namespace std;

bool Compare(const Student& first, const Student& second) {
    return first.rating > second.rating;
}

// bool Compare(Student first, Student second) {
//     return first.Less(second);
// }

bool Compare_02(const Student& first, const Student& second) {
    return first.Less(second);
}

bool Compare_03(const Student& first, const Student& second) {
    return first.rating > second.rating;
}

void TestComparison() {
  Student newbie {
    "Ivan", "Ivanov", {
      {"c++", 1.0},
      {"algorithms", 3.0}
    },
    2.0
  };

  Student cpp_expert {
    "Petr", "Petrov", {
      {"c++", 9.5},
      {"algorithms", 6.0}
    },
    7.75
  };

  Student guru {
    "Sidor", "Sidorov", {
      {"c++", 10.0},
      {"algorithms", 10.0}
    },
    10.0
  };
  ASSERT(Compare(guru, newbie));
  ASSERT(Compare(guru, cpp_expert));
  ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting() {
  vector<Student> students {
    {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
    {"Semen", "Semenov", {{"maths", 4.}}, 4.},
    {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
    {"Petr", "Petrov", {{"maths", 3.}}, 3.},
    {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
  };
  sort(students.begin(), students.end(), Compare);
  ASSERT(is_sorted(students.begin(), students.end(),
    [](Student first, Student second) {
      return first.Less(second);
    })
  );
}

void TestPerf() {
  //vector<Student> students {
    //{"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
    //{"Semen", "Semenov", {{"maths", 4.}}, 4.},
    //{"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
    //{"Petr", "Petrov", {{"maths", 3.}}, 3.},
    //{"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
  //};
  vector<Student> students_orig;
  for (int i = 0; i < 64000; ++i) {
      students_orig.push_back({"Sidor", "Sidorov", {{"maths", 2.}}, 2.});
      students_orig.push_back({"Semen", "Semenov", {{"maths", 4.}}, 4.});
      students_orig.push_back({"Ivan", "Ivanov", {{"maths", 5.}}, 5.});
      students_orig.push_back({"Petr", "Petrov", {{"maths", 3.}}, 3.});
      students_orig.push_back({"Alexander", "Alexandrov", {{"maths", 1.}}, 1.});
  }

  {
      vector<Student> students = students_orig;
      LOG_DURATION("Compare() time");
      sort(students.begin(), students.end(), Compare);
      ASSERT(is_sorted(students.begin(), students.end(),
                  [](Student first, Student second) {
                  return first.Less(second);
                  })
            );
  }

  {
      vector<Student> students = students_orig;
      LOG_DURATION("Compare_02() time");
      sort(students.begin(), students.end(), Compare_02);
      ASSERT(is_sorted(students.begin(), students.end(),
                  [](Student first, Student second) {
                  return first.Less(second);
                  })
            );
  }

  {
      vector<Student> students = students_orig;
      LOG_DURATION("Compare_03() time");
      sort(students.begin(), students.end(), Compare_03);
      ASSERT(is_sorted(students.begin(), students.end(),
                  [](Student first, Student second) {
                  return first.Less(second);
                  })
            );
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestComparison);
  RUN_TEST(tr, TestSorting);
  RUN_TEST(tr, TestPerf);
  return 0;
}
