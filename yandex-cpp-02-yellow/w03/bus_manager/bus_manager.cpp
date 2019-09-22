#include <string>
#include <vector>
#include <map>

#include "bus_manager.h"
#include "responses.h"

using namespace std;


void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    for (const string& stop : stops) {
        stops_to_buses[stop].push_back(bus);
        buses_to_stops[bus].push_back(stop);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
        cout << "No stop" << endl;
    } else {
        for (const string& bus : stops_to_buses.at(stop)) {
            cout << bus << " ";
        }
        cout << endl;
    }
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
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
