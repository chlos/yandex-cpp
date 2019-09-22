#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    q.bus = "";
    q.stop = "";
    q.stops = {};

    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;

        is >> q.bus;

        int stop_count;
        is >> stop_count;
        string stop;
        for (int i = 0; i < stop_count; ++i) {
            is >> stop;
            q.stops.push_back(stop);
      }
    } else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;

        cin >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;

        cin >> q.bus;
    } else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

  return is;
}

// DEBUG
ostream& operator << (ostream& os, const Query& q) {
    os << "QueryType: '" << static_cast<int>(q.type)
       << "'; bus: '" << q.bus << "'; stop: '" << q.stop << "'; stops: '";
    for (const auto& s : q.stops) {
        os << s << " ";
    }
    os << "'";
    return os;
}

struct BusesForStopResponse {
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  return os;
}

struct StopsForBusResponse {
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  return os;
}

struct AllBusesResponse {
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
            buses_to_stops[bus].push_back(stop);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) == 0) {
            cout << "No stop" << endl;
        } else {
            for (const string& bus : stops_to_buses.at(stop)) {
                cout << bus << " ";
            }
            cout << endl;
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (buses_to_stops.count(bus) == 0) {
            cout << "No bus" << endl;
        } else {
            for (const string& stop : buses_to_stops.at(bus)) {
                cout << "Stop " << stop << ": ";
                if (stops_to_buses.at(stop).size() == 1) {
                    cout << "no interchange";
                } else {
                    for (const string& other_bus : stops_to_buses.at(stop)) {
                        if (bus != other_bus) {
                            cout << other_bus << " ";
                        }
                    }
                }
                cout << endl;
            }
        }
    }

    AllBusesResponse GetAllBuses() const {
        if (buses_to_stops.empty()) {
            cout << "No buses" << endl;
        } else {
            for (const auto& bus_item : buses_to_stops) {
                cout << "Bus " << bus_item.first << ": ";
                for (const string& stop : bus_item.second) {
                    cout << stop << " ";
                }
                cout << endl;
            }
        }
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};


int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        //cout << "i = " << i << endl;   // FIXME
        //cout << "q = " << q << endl;   // FIXME
        switch (q.type) {
        case QueryType::NewBus:
            //cout << "=== NEW BUS" << endl;   // FIXME
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            //cout << "=== BUSES FOR STOP" << endl;   // FIXME
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            //cout << "=== STOP FOR BUSES" << endl;   // FIXME
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            //cout << "=== ALL BUSES" << endl;   // FIXME
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
