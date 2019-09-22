#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(
        make_move_iterator(range_begin),
        make_move_iterator(range_end)
    );
    auto one_third = (range_end - range_begin) / 3;
    auto elements_first_third = elements.begin() + one_third;
    auto elements_second_third = elements_first_third + one_third;
    MergeSort(elements.begin(), elements_first_third);
    MergeSort(elements_first_third, elements_second_third);
    MergeSort(elements_second_third, elements.end());

    vector<typename RandomIt::value_type> tmp;
    merge(
        make_move_iterator(elements.begin()), make_move_iterator(elements_first_third),
        make_move_iterator(elements_first_third), make_move_iterator(elements_second_third),
        back_inserter(tmp)
    );
    merge(
        make_move_iterator(tmp.begin()), make_move_iterator(tmp.end()),
        make_move_iterator(elements_second_third), make_move_iterator(elements.end()),
        range_begin
    );
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
