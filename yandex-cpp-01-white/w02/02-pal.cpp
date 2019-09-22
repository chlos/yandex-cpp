#include <iostream>
#include <string>

bool IsPalindrom(std::string s) {
    for (int i = 0; i < s.length() / 2; ++i) {
        if (s[i] != s[s.length() - 1 - i]) {
            return false;
        }
    }
    return true;
}

// int main() {
//     std::string s;
//     std::cin >> s;
//
//     std::cout << IsPalindrom(s) << "\n";
//
//     return 0;
// }
