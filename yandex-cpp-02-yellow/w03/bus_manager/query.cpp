#include <iostream>
#include <string>
#include <vector>

#include "query.h"

using namespace std;

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
