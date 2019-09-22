#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
    //throw 1;
    //throw system_error(error_code());
    return "12:33:42";
}

class TimeServer {
public:
    string GetCurrentTime() {
        try {
            LastFetchedTime = AskTimeServer();
        } catch (const system_error&) {
        } catch (const exception& e) {
            throw;
        }

        return LastFetchedTime;
    }

private:
    string LastFetchedTime = "00:00:00";
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
