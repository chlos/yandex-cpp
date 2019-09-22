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

//class Rational {
//public:
//  Rational();
//  Rational(int numerator, int denominator) {
//  }
//
//  int Numerator() const {
//  }
//
//  int Denominator() const {
//  }
//};

void TestDefaultNumerator() {
    Rational r = {};
    AssertEqual(r.Numerator(), 0, "TestDefaultNumerator");
}

void TestDefaultDenominator() {
    Rational r = {};
    AssertEqual(r.Denominator(), 1, "TestDefaultDenominator");
}

void TestDefaultReduction() {
    Rational r = {2, 4};
    AssertEqual(r.Numerator(), 1, "TestDefaultReduction: num");
    AssertEqual(r.Denominator(), 2, "TestDefaultReduction: denom");
}

void TestNegative() {
    Rational r1 = {-1, 2};
    AssertEqual(r1.Numerator(), -1, "TestNegative: num: -1/2");
    AssertEqual(r1.Denominator(), 2, "TestNegative: denom: -1/2");
    Rational r2 = {1, -2};
    AssertEqual(r2.Numerator(), -1, "TestNegative: num: 1/-2");
    AssertEqual(r2.Denominator(), 2, "TestNegative: denom: 1/-2");
    Rational r3 = {-1, -2};
    AssertEqual(r3.Numerator(), 1, "TestNegative: num: -1/-2");
    AssertEqual(r3.Denominator(), 2, "TestNegative: denom: -1/-2");
}

void TestZero() {
    Rational r = {0, 2};
    AssertEqual(r.Numerator(), 0, "TestZero: num: 0/2");
    AssertEqual(r.Denominator(), 1, "TestZero: denom: 0/2");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefaultNumerator, "Test default numerator");
  runner.RunTest(TestDefaultDenominator, "Test default denominator");
  runner.RunTest(TestDefaultReduction, "Test default reduction");
  runner.RunTest(TestNegative, "Test negative");
  runner.RunTest(TestZero, "Test zero");

  return 0;
}
