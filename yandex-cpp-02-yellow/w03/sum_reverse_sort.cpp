#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    reverse(s.begin(), s.end());

    return s;
}

void Sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}

int main() {
    cout << Sum(1, 2) << endl;
    cout << Reverse("abcd") << endl;
    cout << Reverse("abc") << endl;
    vector<int> v = {10, 1, 5, 2, 4, 3};
    Sort(v);
    cout << v[0] << endl;

    return 0;
}
