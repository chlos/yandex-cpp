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
    auto one_third = (range_end - range_begin) / 3;
    auto elements_first_third = elements.begin() + one_third;
    auto elements_second_third = elements_first_third + one_third;
    MergeSort(elements.begin(), elements_first_third);
    MergeSort(elements_first_third, elements_second_third);
    MergeSort(elements_second_third, elements.end());

    vector<typename RandomIt::value_type> tmp;
    merge(
        elements.begin(), elements_first_third,
        elements_first_third, elements_second_third,
        back_inserter(tmp)
    );
    merge(
        tmp.begin(), tmp.end(),
        elements_second_third, elements.end(),
        range_begin
    );
}

int main() {
    //vector<int> v = {1, 3, 2, 4, 10, 9, 8, 11, 11, 7};
    vector<int> v = {1, 3, 2, 4, 10, 9, 8, 11, 11};
    PrintV(v);
    MergeSort(v.begin(), v.end());
    PrintV(v);

    return 0;
}
