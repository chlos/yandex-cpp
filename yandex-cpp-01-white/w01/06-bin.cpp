#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> res;

    while (n > 1) {
        res.push_back(n % 2);
        n = n / 2;
        //cout << "n = " << n << " n % 2 = " << n % 2 << "\n";
    }
    res.push_back(1);


    reverse(res.begin(), res.end());
    for (auto i : res) {
        cout << i;
    }
    cout << "\n";

    return 0;
}
