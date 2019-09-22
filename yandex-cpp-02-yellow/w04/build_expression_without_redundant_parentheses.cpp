#include <iostream>
#include <string>
#include <queue>

using namespace std;


struct t_operation {
    string data;
    int priority;
};

int main() {
    int x;
    cin >> x;
    int n;
    cin >> n;
    cin.get();

    int brackets_num = 0;

    int priority_prev = 100;
    queue<t_operation> operations;
    for (int i = 0; i < n; ++i) {
        t_operation operation;
        getline(cin, operation.data);
        if (operation.data.front() == '*' || operation.data.front() == '/') {
            operation.priority = 1;
        } else {
            operation.priority = 0;
        }
        operations.push(operation);

        if (priority_prev < operation.priority) {
            ++brackets_num;
        }
        priority_prev = operation.priority;
    }

    t_operation operation_prev;
    operation_prev.priority = 100;
    cout << string(brackets_num, '(') << to_string(x);
    while (!operations.empty()) {
        t_operation operation_curr = operations.front();
        operations.pop();
        if (operation_prev.priority < operation_curr.priority) {
            cout << ") ";
        } else {
            cout << " ";
        }
        cout << operation_curr.data;
        operation_prev = operation_curr;
    }
    cout << endl;

    return 0;
}
