#include <iostream>
#include <vector>

using namespace std;

//void PrintVector(vector<int> v) {
//    for (auto e : v) {
//        std::cout << e << " ";
//    }
//        std::cout << "\n";
//}

void Reverse(vector<int>& numbers) {
    int swp;
    for (unsigned long i = 0; i < numbers.size() / 2; ++i) {
        //cout << "=====\n";
        //cout << "numbers[i] = " << numbers[i] << " ; numbers[numbers.size() - 1 - i] = " << numbers[numbers.size() - 1 - i] << "\n";
        swp = numbers[i];
        numbers[i] = numbers[numbers.size() - 1 - i];
        numbers[numbers.size() - 1 - i] = swp;
        //cout << "numbers[i] = " << numbers[i] << " ; numbers[numbers.size() - 1 - i] = " << numbers[numbers.size() - 1 - i] << "\n";
    }

}

//int main() {
//    vector<int> numbers = {1, 5, 3, 4, 2};
//    PrintVector(numbers);
//    Reverse(numbers);
//    PrintVector(numbers);
//
//    return 0;
//}
