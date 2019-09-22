#include <iomanip>
#include <iostream>
#include <deque>
#include <set>
#include <map>
#include <utility>

using namespace std;


struct BookingEntry {
    int64_t time;
    string hotel_name;
    int room_count;
    int id;
};


class Booking {
public:
    int GetClientCount(string hotel_name) {
        if (hotel_clients_.count(hotel_name) == 0) {
            return 0;
        };
        return hotel_clients_.at(hotel_name).size();
    }

    int GetRoomCount(string hotel_name) {
        if (hotel_rooms_booked_.count(hotel_name) == 0) {
            return 0;
        };
        return hotel_rooms_booked_.at(hotel_name);
    }

    void Book(int64_t time, string hotel_name, int client_id, int room_count) {
        Adjust_(time, hotel_name);

        bookings_.push_back({time, hotel_name, room_count, client_id});
        hotel_rooms_booked_[hotel_name] += room_count;
        hotel_clients_[hotel_name].insert(client_id);
    }

private:
    static const int DAY_SECONDS_ = 86400;

    deque<BookingEntry> bookings_;
    map<string, int64_t> hotel_rooms_booked_;
    map<string, set<int64_t>> hotel_clients_;

    void Adjust_(int64_t time, string hotel_name) {
        while (!bookings_.empty() && bookings_.front().time <= (time - DAY_SECONDS_)) {
            auto entry_rm = bookings_.front();
            hotel_rooms_booked_[entry_rm.hotel_name] -= entry_rm.room_count;
            hotel_clients_[entry_rm.hotel_name].erase(entry_rm.id);
            bookings_.pop_front();
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Booking booking;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            int client_id;
            int room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            booking.Book(time, hotel_name, client_id, room_count);

        } else if (query_type == "CLIENTS"){
            string hotel_name;
            cin >> hotel_name;
            cout << booking.GetClientCount(hotel_name) << '\n';

        } else if (query_type == "ROOMS"){
            string hotel_name;
            cin >> hotel_name;
            cout << booking.GetRoomCount(hotel_name) << '\n';
        }
    }

    return 0;
}
