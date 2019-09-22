#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <cmath>

#define PI 3.14

using namespace std;


class Figure {
public:
    Figure(const string& name) : _name(name) {}

    string Name() const {
        return _name;
    }

    virtual double Perimeter() const = 0;

    virtual double Area() const = 0;

private:
    const string _name;
};


class Triangle : public Figure {
public:
    Triangle(double a, double b, double c)
        : Figure("TRIANGLE"), _a(a), _b(b), _c(c) {}

    double Perimeter() const override {
        return _a + _b + _c;
    }

    double Area() const override {
        double p = Perimeter() / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }

private:
    double _a;
    double _b;
    double _c;
};


class Rect : public Figure {
public:
    Rect(double w, double h) : Figure("RECT"), _w(w), _h(h) {}

    double Perimeter() const override {
        return 2 * (_w + _h);
    }

    double Area() const override {
        return _w * _h;
    }

private:
    double _w;
    double _h;
};


class Circle : public Figure {
public:
    Circle(double r) : Figure("CIRCLE"), _r(r) {}

    double Perimeter() const override {
        return 2 * PI * _r;
    }

    double Area() const override {
        return PI * _r * _r;
    }

private:
    double _r;
};


shared_ptr<Figure> CreateFigure(istringstream& is) {
    string name;
    is >> name;
    if (name == "TRIANGLE") {
        double a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if (name == "RECT") {
        double w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    } else if (name == "CIRCLE") {
        double r;
        is >> r;
        return make_shared<Circle>(r);
    }
}


int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                << current_figure->Name() << " "
                << current_figure->Perimeter() << " "
                << current_figure->Area() << endl;
            }
        }
    }

    return 0;
}
