#include <iostream>
#include <string>
#include <vector>

void PrintVector(std::vector<std::string> v) {
    for (auto e : v) {
        std::cout << e << " ";
    }
        std::cout << "\n";
}


bool IsPalindrom(std::string s) {
    for (int i = 0; i < s.length() / 2; ++i) {
        if (s[i] != s[s.length() - 1 - i]) {
            return false;
        }
    }

    return true;
}


std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {
    std::vector<std::string> result_words;
    for (auto word : words) {
        if (IsPalindrom(word) && word.size() >= minLength) {
            result_words.push_back(word);
        }
    }

    return result_words;
}

//int main() {
//    //std::string s;
//    //std::cin >> s;
//    //std::cout << PalindromFilter({"aaaaa", "bbbbbb", "xxx", "foobar"}, 5) << "\n";
//    PalindromFilter({"aaaaa", "bbbbbb", "xxx", "foobar"}, 5);
//    PalindromFilter({"aaaaa", "bbbbbb", "xxx", "foobar"}, 5);
//    return 0;
//}
