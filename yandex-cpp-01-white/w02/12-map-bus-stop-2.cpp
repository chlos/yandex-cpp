#include <iostream>
#include <vector>
#include <map>

using namespace std;

void PrintMap(map<string, vector<string>> m) {
    for (auto e : m) {
        cout << e.first << ":";
        for (auto v_e : e.second) {
            cout << " " << v_e;
        }
        cout << endl;
    }
}

int main() {
    map<vector<string>, int> buses;

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        //cout << "\nq = " << i << endl;    // FIXME
        int n;
        cin >> n;
        vector<string> stops;
        for (int j = 0; j < n; ++j) {
            string stop;
            cin >> stop;
            stops.push_back(stop);
        }
        if (buses.count(stops) > 0) {
            cout << "Already exists for " << buses[stops] << endl;
        } else {
            int new_bus_n = buses.size() + 1;
            buses[stops] = new_bus_n;
            cout << "New bus " << new_bus_n << endl;
        }
    }

    //cout << "\n\n=====\n";  // FIXME
    //PrintMap(buses);    // FIXME
    //cout << endl;       // FIXME
    //PrintMap(stops);    // FIXME

    return 0;
}
