#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string filename_input = "input.txt";
    ifstream input(filename_input);

    cout << fixed << setprecision(3);
    double value = 0;
    while (input >> value) {
        cout << value << endl;
    }

    return 0;
}
