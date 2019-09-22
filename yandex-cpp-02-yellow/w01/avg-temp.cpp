#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void PrintVector(vector<int64_t> v) {
    for (auto e : v) {
        std::cout << e << " ";
    }
        std::cout << "\n";
}

int main() {
    int n;
    cin >> n;

    vector<int64_t> days_temp;
    int64_t t;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        days_temp.push_back(t);
    }
    //PrintVector(days_temp);     // FIXME

    //int64_t avg = accumulate(days_temp.begin(), days_temp.end(), 0) / static_cast<int64_t>(days_temp.size());
    int64_t sum = 0;
    for (auto x : days_temp) {
        sum += x;
    }
    int64_t avg = sum / static_cast<int64_t>(days_temp.size());
    //cout << "sum = " << sum << "\n";    // FIXME
    //cout << "avg = " << avg << "\n";    // FIXME

    int k = 0;
    vector<int64_t> days_result;
    for (int i = 0; i < n; ++i) {
        if (days_temp[i] > avg) {
            ++k;
            days_result.push_back(i);
        }
    }
    cout << k << "\n";
    PrintVector(days_result);

    return 0;
}
