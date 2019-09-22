#include <iostream>
#include <string>

int main() {
    std::string s1, s2, s3;
    std::cin >> s1 >> s2 >> s3;

    if (s1 <= s2 && s1 <= s3) {
        std::cout << s1 << "\n";
    } else if (s2 <= s1 && s2 <= s3) {
        std::cout << s2 << "\n";
    } else {
        std::cout << s3 << "\n";
    }

    return 0;
}
