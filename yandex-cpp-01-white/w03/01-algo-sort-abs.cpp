#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Print(vector<int> v) {
    for (auto e : v) {
        cout << e << " ";
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;
    vector<int> nums;
    for (int i = 0; i < N; ++i) {
        int n;
        cin >> n;
        nums.push_back(n);
    }

    //Print(nums);
    sort(
        nums.begin(), nums.end(),
        [](int n1, int n2) {return abs(n1) < abs(n2);}
    );
    Print(nums);

    return 0;
}

