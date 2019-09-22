#include <iostream>
#include <vector>

using namespace std;

enum class PersonStatus {
    Quiet,
    Worry,
};

void PrintVector(vector<PersonStatus> v) {
    for (auto e : v) {
        std::cout << static_cast<int>(e) << " ";
    }
        std::cout << "\n";
}

int main() {
    vector<PersonStatus> persons;
    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        string cmd;
        int cmd_k = 0;
        cin >> cmd;
        if (cmd == "WORRY" || cmd == "QUIET" || cmd == "COME") {
            cin >> cmd_k;
        }
        //cout << "cmd = " << cmd << " ; k = " << cmd_k << "\n";    // FIXME

        if (cmd == "COME") {
            for (int p = 0; p < abs(cmd_k); ++p) {
                //cout << "=== come\n";    // FIXME
                if (cmd_k > 0) {
                    //cout << "add\n";    // FIXME
                    persons.push_back(PersonStatus::Quiet);
                } else if (cmd_k < 0) {
                    //cout << "remove\n";    // FIXME
                    persons.pop_back();
                }
            }
        } else if (cmd == "WORRY") {
            persons[cmd_k] = PersonStatus::Worry;
        } else if (cmd == "QUIET") {
            persons[cmd_k] = PersonStatus::Quiet;
        }  else if (cmd == "WORRY_COUNT") {
            int worry_count = 0;
            for (auto person : persons) {
                if (person == PersonStatus::Worry) {
                    ++worry_count;
                }
            }
            cout << worry_count << "\n";
        }

        //PrintVector(persons);   // FIXME
    }

    return 0;
}
