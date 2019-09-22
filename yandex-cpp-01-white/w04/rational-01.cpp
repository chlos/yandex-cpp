#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:
    Rational() {
        _numerator = 0;
        _denominator = 1;
    }

    Rational(int numerator, int denominator) {
        _numerator = numerator;
        _denominator = denominator;
        simplify();
    }

    int Numerator() const {
        return _numerator;
    }

    int Denominator() const {
        return _denominator;
    }

    friend bool operator==(const Rational& lhs, const Rational& rhs) {
        return (lhs._numerator == rhs._numerator) && (lhs._denominator == rhs._denominator);
    }

    friend bool operator<(const Rational& lhs, const Rational& rhs) {
        return lhs._numerator * rhs._denominator < rhs._numerator * lhs._denominator;
    }

    friend bool operator>(const Rational& lhs, const Rational& rhs) {
        return lhs._numerator * rhs._denominator > rhs._numerator * lhs._denominator;
    }

    friend Rational operator+(const Rational& lhs, const Rational& rhs) {
        return Rational(
            lhs._numerator * rhs._denominator + rhs._numerator * lhs._denominator,
            lhs._denominator * rhs._denominator
        );
    }

    friend Rational operator-(const Rational& lhs, const Rational& rhs) {
        return Rational(
            lhs._numerator * rhs._denominator - rhs._numerator * lhs._denominator,
            lhs._denominator * rhs._denominator
        );
    }

    friend Rational operator*(const Rational& lhs, const Rational& rhs) {
        return Rational(
            lhs._numerator * rhs._numerator,
            lhs._denominator * rhs._denominator
        );
    }

    friend Rational operator/(const Rational& lhs, const Rational& rhs) {
        return Rational(
            lhs._numerator * rhs._denominator,
            lhs._denominator * rhs._numerator
        );
    }

    friend ostream& operator<<(ostream& stream, const Rational& rational) {
        stream << rational._numerator << "/" << rational._denominator;
        return stream;
    }

    friend istream& operator>>(istream& stream, Rational& rational) {
        stream >> rational._numerator;
        stream.ignore(1);
        stream >> rational._denominator;
        rational.simplify();
        return stream;
    }

private:
    int _numerator;
    int _denominator;

    int get_nod(int a, int b) {
        while (a > 0 && b > 0) {
            if (a > b) {
                a = a % b;
            } else {
                b = b % a;
            }
        }
        return a + b;
    }

    void simplify() {
        int sign = 1;
        if (_numerator < 0 && _denominator < 0) {
            sign = 1;
            //_numerator = -_numerator;
            //_denominator = -_denominator;
        } else if (_numerator < 0 || _denominator < 0) {
            sign = -1;
        }
        _numerator = abs(_numerator);
        _denominator = abs(_denominator);

        int nod = get_nod(_numerator, _denominator);
        //cout << "n = " << numerator << "; d = " << denominator << "; nod = " << nod << endl;    // FIXME
        _numerator = sign * (_numerator / nod);
        _denominator = _denominator / nod;
    }
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        //cout << r.Numerator() << "/" << r.Denominator() << endl;
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        //cout << r.Numerator() << "/" << r.Denominator() << endl;
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(-4, -6);
        //cout << r.Numerator() << "/" << r.Denominator() << endl;
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(-4, -6) != 2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (
            defaultConstructed.Numerator() != 0 ||
            defaultConstructed.Denominator() != 1
        ) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
