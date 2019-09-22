#include <iostream>
#include <cmath>

int main() {
    double a, b, c, d;
    std::cin >> a >> b >> c;

    double x1, x2;

    if (a == 0 and b == 0) {
        return 0;
    }

    if (a == 0) {
        x1 = x2 = -c / b;
        std::cout << x1 << "\n";
        return 0;
    }

    d = b * b - 4 * a * c;
    //std::cout << "d = " << d << "\n";
    if (d < 0) {
        return 0;
    } else if (d == 0) {
        x1 = x2 = (-b + sqrt(d)) / (2 * a);
        std::cout << x1 << "\n";
    } else {
        x1 = (-b + sqrt(d)) / (2 * a);
        x2 = (-b - sqrt(d)) / (2 * a);
        std::cout << x1 << " " << x2 << "\n";
    }

    return 0;
}
