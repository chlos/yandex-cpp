#pragma once

#include <string>
#include <iostream>

using namespace std;


struct BusesForStopResponse {
  // FIXME
};

struct StopsForBusResponse {
  // FIXME
};

struct AllBusesResponse {
  // FIXME
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

ostream& operator << (ostream& os, const StopsForBusResponse& r);

ostream& operator << (ostream& os, const AllBusesResponse& r);
