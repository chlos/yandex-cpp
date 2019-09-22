#include <iostream>
#include <string>

using namespace std;

int main() {
    char ch_target = 'f';
    int found = 0, i = 0;
    string s;
    cin >> s;
    for (auto ch : s) {
        if (ch == ch_target) {
            ++found;
        }
        if (found == 2) {
            cout << i << "\n";
            return 0;
        }
        ++i;
    }

    if (found == 1) {
        cout << -1 << "\n";
    } else {
        cout << -2 << "\n";
    }
}
