#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string filename_input = "input.txt";
    ifstream input(filename_input);

    string str;
    int N = 0, M = 0;
    input >> N;
    input >> M;

    int value = 0;
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            input >> value;
            input.ignore(1);
            cout << setw(10) << value;
            if (m < M - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
