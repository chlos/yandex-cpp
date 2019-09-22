#include <iostream>
using namespace std;

void UpdateIfGreater(int first, int& second) {
    if (first > second) {
        second = first;
    }
}

//int main() {
//    int a = 1, b = 2;
//    cout << a << " " << b << "\n";
//    UpdateIfGreater(a, b);
//    cout << a << " " << b << "\n";
//
//    a = 2, b = 1;
//    cout << a << " " << b << "\n";
//    UpdateIfGreater(a, b);
//    cout << a << " " << b << "\n";
//
//    return 0;
//}
