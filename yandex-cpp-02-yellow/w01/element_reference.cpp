#include <iostream>
#include <map>

using namespace std;


template <typename TKey, typename TValue>
TValue& GetRefStrict(map<TKey, TValue>& m, TKey k) {
    if (m.count(k)) {
        return m.at(k);
    } else {
        throw runtime_error("Wrong key");
    }
}


int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    cout << item << endl;
    item = "newvalue";
    cout << m[0] << endl;

    string& wrong_item = GetRefStrict(m, 7);
    cout << wrong_item << endl;

    return 0;
}
