#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void PrintVector(vector<int> v) {
    for (auto e : v) {
        std::cout << e << " ";
    }
        std::cout << "\n";
}

int main() {
    int n;
    cin >> n;

    vector<int> days_temp;
    int t;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        days_temp.push_back(t);
    }
    //PrintVector(days_temp);     // FIXME

    int avg = accumulate(days_temp.begin(), days_temp.end(), 0) / days_temp.size();
    //cout << "avg = " << avg << "\n";    // FIXME

    int k = 0;
    vector<int> days_result;
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
