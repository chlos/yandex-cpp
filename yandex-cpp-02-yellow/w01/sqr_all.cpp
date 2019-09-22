#include <iostream>
#include <map>
#include <vector>

using namespace std;


template <typename T> vector<T>
    operator * (const vector<T>& v1, const vector<T>& v2);
template <typename TKey, typename TValue>
    map<TKey, TValue> operator * (const map<TKey, TValue>& m1, const map<TKey, TValue>& m2);
template <typename TFirst, typename TSecond>
    pair<TFirst, TSecond> operator * (const pair<TFirst, TSecond>& p1, const pair<TFirst, TSecond>& p2);
template <typename T> T Sqr(T x);


template <typename T>
vector<T> operator * (const vector<T>& v1, const vector<T>& v2) {
    vector<T> result;
    for (int i = 0; i < v1.size(); ++i) {
        result.push_back(v1.at(i) * v2.at(i));
    }
    return result;
}


template <typename TKey, typename TValue>
map<TKey, TValue> operator * (const map<TKey, TValue>& m1, const map<TKey, TValue>& m2) {
    map<TKey, TValue> result;
    for (const auto& e : m1) {
        TKey key = e.first;
        result[key] = e.second * m2.at(key);
    }
    return result;
}


template <typename TFirst, typename TSecond>
pair<TFirst, TSecond> operator * (const pair<TFirst, TSecond>& p1, const pair<TFirst, TSecond>& p2) {
    return make_pair(p1.first * p2.first, p1.second * p2.second);
}


template <typename T>
T Sqr(T x) {
    return x * x;
}


int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    auto p = make_pair(2, 3);
    auto p_sqr = Sqr(p);
    cout << "pair: " << p_sqr.first << " " << p_sqr.second << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    return 0;
}
