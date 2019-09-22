#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void PrintV(vector<T> elements) {
    for (auto e : elements) {
        cout << e << ' ';
    }
    cout << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto elements_middle = elements.begin() + (range_end - range_begin) / 2;
    MergeSort(elements.begin(), elements_middle);
    MergeSort(elements_middle, elements.end());

    merge(
        elements.begin(), elements_middle,
        elements_middle, elements.end(),
        range_begin
    );
}

int main() {
    vector<int> v = {1, 3, 2, 4};
    PrintV(v);
    MergeSort(v.begin(), v.end());
    PrintV(v);

    return 0;
}
