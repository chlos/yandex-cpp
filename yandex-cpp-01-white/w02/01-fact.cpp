#include <iostream>

int Factorial(int n) {
    if (n <= 1) {
        return 1;
    }

    return n * Factorial(n - 1);
}

int main() {
    int x;
    std::cin >> x;

    std::cout << Factorial(x) << "\n";

    return 0;
}

