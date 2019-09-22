#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
    // FIXME
}

void Test() {
    AssertEqual(IsPalindrom("a"), true, "Len: 1; a is palindrom");
    AssertEqual(IsPalindrom("aa"), true, "Len: 2 (even); aa is palindrom");
    AssertEqual(IsPalindrom("aaa"), true, "Len: 3 (odd); aaa is palindrom");
    AssertEqual(IsPalindrom("aba"), true, "Len: 3 (odd); different chars; aba is palindrom");
    AssertEqual(IsPalindrom("abba"), true, "Len: 4 (even); different chars; abba is palindrom");

    AssertEqual(IsPalindrom("ab"), false, "Len: 2 (even); different chars; ab is NOT palindrom");
    AssertEqual(IsPalindrom("abb"), false, "Len: 3 (odd); different chars; abb is NOT palindrom");

    AssertEqual(IsPalindrom(""), true, "Len: 0; empty string is palindrom");

    AssertEqual(IsPalindrom(" "), true, "Spaces: 1 space string is palindrom");
    AssertEqual(IsPalindrom("  "), true, "Spaces: 2 spaces string is palindrom");
    AssertEqual(IsPalindrom("   "), true, "Spaces: 3 spaces string is palindrom");
    AssertEqual(IsPalindrom(" aa"), false, "Spaces: before");
    AssertEqual(IsPalindrom("aa "), false, "Spaces: after");
    AssertEqual(IsPalindrom(" aa "), true, "Spaces: before and after");
    AssertEqual(IsPalindrom("a a"), true, "Spaces: middle");
    AssertEqual(IsPalindrom(" a a"), false, "Spaces: before, middle");
    AssertEqual(IsPalindrom("a a "), false, "Spaces: middle, after");
    AssertEqual(IsPalindrom(" a a "), true, "Spaces: before, middle, after");
}

int main() {
  TestRunner runner;
  runner.RunTest(Test, "Test");

  return 0;
}
