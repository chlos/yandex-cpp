#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string filename = "input.txt";
    ifstream input(filename);
    string line;
    while (getline(input, line)) {
        cout << line << endl;
    }

    return 0;
}
