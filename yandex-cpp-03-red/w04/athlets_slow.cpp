#include <iomanip>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;


class Athletes {
public:
    Athletes()
        : athletes_existing(N_MAX_) {}

    void Add(int athlete_current, int athlete_pair) {
        if (athletes_existing[athlete_pair]) {
            auto it = find(athletes.begin(), athletes.end(), athlete_pair);
            athletes.insert(it, athlete_current);
        } else {
            athletes.push_back(athlete_current);
        }

        athletes_existing[athlete_current] = true;
    }

    void Print() {
        for (auto athlete : athletes) {
            cout << athlete << " ";
        }
        cout << endl;
    }
private:
    const int N_MAX_ = 100000;

    list<int> athletes;
    vector<bool> athletes_existing;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Athletes athletes;

    size_t N;
    cin >> N;

    for (size_t i = 0; i < N; ++i) {
        int athlete_current, athlete_pair;
        cin >> athlete_current >> athlete_pair;
        athletes.Add(athlete_current, athlete_pair);
    }
    athletes.Print();

    return 0;
}
