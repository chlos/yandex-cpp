#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void Print(vector<string> v) {
    for (auto e : v) {
        cout << e << " ";
    }
    cout << endl;
}

string TolowerString(const string& s) {
    string lower_s = "";
    for (auto c : s) {
        lower_s += tolower(c);
    }

    return lower_s;
}

int main() {
    int N;
    cin >> N;
    vector<string> strs;
    for (int i = 0; i < N; ++i) {
        string str;
        cin >> str;
        strs.push_back(str);
    }

    //Print(strs);
    // TODO: use lexicographical_compare()
    sort(
        strs.begin(), strs.end(),
        [](const string& x1, const string& x2) {return TolowerString(x1) < TolowerString(x2);}
    );
    Print(strs);

    return 0;
}

