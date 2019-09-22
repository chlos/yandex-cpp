#include <iomanip>
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;


class Athletes {
public:
    Athletes()
        : athlete_pos(N_MAX_ + 1, athletes.end()) {}

    void Add(int athlete_current, int athlete_pair) {
        athlete_pos[athlete_current] = athletes.insert(
            athlete_pos[athlete_pair],
            athlete_current
        );
    }

    void Print() {
        for (auto athlete : athletes) {
            cout << athlete << " ";
        }
        cout << endl;
    }
private:
    const int N_MAX_ = 100'000;

    list<int> athletes;
    using Position = list<int>::iterator;
    vector<Position> athlete_pos;
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
