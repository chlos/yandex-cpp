#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> v;
    for (int i = 1; i <= n; ++i) {
        v.push_back(i);
    }

    sort(v.begin(), v.end(), greater<int>());

    /* coursera
    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    iota(permutation.begin(), permutation.end(), 1);
  
    // reverse          -> http://ru.cppreference.com/w/cpp/algorithm/reverse
    // Меняет порядок следования элементов в диапазоне на противоположный
    reverse(permutation.begin(), permutation.end());
    */

    do {
        for (auto i : v) {
            cout << i << " ";
        }
        cout << endl;
    } while (prev_permutation(v.begin(), v.end()));
  
    return 0;
}
