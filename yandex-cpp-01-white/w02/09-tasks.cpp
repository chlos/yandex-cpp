#include <iostream>
#include <string>
#include <vector>

using namespace std;

void PrintVector(vector<vector<string>> v) {
    int i = 1;
    for (auto ev : v) {
        cout << i << ": ";
        for (auto es: ev) {
            cout << es << " ";
        }
        ++i;
        cout << endl;
    }
}

int main() {
    const vector<int> DAYS_IN_MONTH = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int MONTHS_IN_YEAR = DAYS_IN_MONTH.size();

    int current_month = 0;
    vector<vector<string>> tasks(DAYS_IN_MONTH[current_month]);

    int q = 0;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string cmd;
        cin >> cmd;

        if (cmd == "ADD") {
            int add_i;
            cin >> add_i;
            string add_s;
            cin >> add_s;
            tasks[add_i - 1].push_back(add_s);

        } else if (cmd == "NEXT") {
            if (current_month < MONTHS_IN_YEAR - 1) {
                ++current_month;
            } else {
                current_month = 0;
            }
            vector<string> tasks_to_move;
            if (DAYS_IN_MONTH[current_month - 1] > DAYS_IN_MONTH[current_month]) {
                for (int i = DAYS_IN_MONTH[current_month]; i < DAYS_IN_MONTH[current_month - 1]; ++i) {
                    for (auto task_in_day : tasks[i]) {
                        tasks_to_move.push_back(task_in_day);
                    }
                }
            }
            tasks.resize(DAYS_IN_MONTH[current_month]);
            tasks[DAYS_IN_MONTH[current_month] - 1].insert(
                end(tasks[DAYS_IN_MONTH[current_month] - 1]),
                begin(tasks_to_move), end(tasks_to_move)
            );

        } else if (cmd == "DUMP") {
            int dump_i;
            cin >> dump_i;
            cout << tasks[dump_i - 1].size();
            for (auto task : tasks[dump_i - 1]) {
                cout << " " << task;
            }
            cout << endl;
        }
    }

    return 0;
}
