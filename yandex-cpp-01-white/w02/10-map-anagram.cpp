#include <iostream>
#include <vector>
#include <map>

using namespace std;

void PrintMap(map<char, int> m) {
    for (auto e : m) {
        cout << e.first << ": " << e.second << endl;
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    vector<bool> results;
    for (int i = 0; i < n; ++i) {
        string w1, w2;
        cin >> w1 >> w2;
        //cout << "w1 = " << w1 << "; w2 = " << w2 << endl;   // FIXME

        map<char, int> count_1, count_2;
        for (auto c : w1) {
            ++count_1[c];
        }
        //PrintMap(count_1);  // FIXME
        for (auto c : w2) {
            ++count_2[c];
        }
        //PrintMap(count_2);  // FIXME
        if (count_1 == count_2) {
            results.push_back(true);
        } else {
            results.push_back(false);
        }
    }

    for (auto r : results) {
        if (r == true) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
