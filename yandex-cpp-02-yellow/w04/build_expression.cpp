#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main() {
    int x;
    cin >> x;
    int n;
    cin >> n;

    cin.get();
    queue<string> operations;
    for (int i = 0; i < n; ++i) {
        string operation;
        getline(cin, operation);
        operations.push(operation);
    }

    cout << string(n, '(') << to_string(x);
    while (!operations.empty()) {
        string operation = operations.front();
        operations.pop();
        cout << ") " << operation;
    }
    cout << endl;

    return 0;
}
