#include <iostream>
#include <string>
#include <vector>

using namespace std;

//void PrintVector(std::vector<std::string> v) {
//    for (auto e : v) {
//        std::cout << e << " ";
//    }
//        std::cout << "\n";
//}

void MoveStrings(vector<string>& source, vector<string>& destination) {
    for (auto str : source) {
        destination.push_back(str);
    }
    source.clear();
}

//int main() {
//    vector<string> src = {"a", "b", "c"};
//    vector<string> dst = {"z"};
//
//    PrintVector(src);
//    PrintVector(dst);
//    MoveStrings(src, dst);
//    PrintVector(src);
//    PrintVector(dst);
//
//    return 0;
//}
