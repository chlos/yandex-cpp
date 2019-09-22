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
    map<string, vector<string>> buses, stops;

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        //cout << "\nq = " << i << endl;    // FIXME
        string cmd;
        cin >> cmd;
        //cout << cmd << endl;  // FIXME

        if (cmd == "NEW_BUS") {
            string bus;
            cin >> bus;
            int stop_count;
            cin >> stop_count;
            for (int i = 0; i < stop_count; ++i) {
                string stop_name;
                cin >> stop_name;
                buses[bus].push_back(stop_name);
                stops[stop_name].push_back(bus);
            }

        } else if (cmd == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;
            if (stops.count(stop) > 0) {
                for (auto b : stops[stop]) {
                    cout << b << " ";
                }
                cout << endl;
            } else {
                cout << "No stop" << endl;
            }

        } else if (cmd == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;
            if (buses.count(bus) > 0) {
                for (auto stop : buses[bus]) {
                    cout << "Stop " << stop << ":";
                    bool no_interchange = true;
                    for (auto bus_inter: stops[stop]) {
                        if (bus_inter != bus) {
                            no_interchange = false;
                            cout << " " << bus_inter;
                        }
                    }
                    if (no_interchange) {
                        cout << " no interchange";
                    }
                    cout << endl;
                }
            } else {
                cout << "No bus" << endl;
            }

        } else if (cmd == "ALL_BUSES") {
            if (!buses.empty()) {
                for (auto bus_info : buses) {
                    cout << "Bus " << bus_info.first << ":";
                    for (auto stop : bus_info.second) {
                        cout << " " << stop;
                    }
                    cout << endl;
                }
            } else {
                cout << "No buses" << endl;
            }

        }

    }

    //cout << "\n\n=====\n";  // FIXME
    //PrintMap(buses);    // FIXME
    //cout << endl;       // FIXME
    //PrintMap(stops);    // FIXME

    return 0;
}
