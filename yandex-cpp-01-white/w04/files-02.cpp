#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string filename_input = "input.txt";
    string filename_output = "output.txt";
    ifstream input(filename_input);
    ofstream output(filename_output);
    string line;
    while (getline(input, line)) {
        output << line << endl;
    }

    return 0;
}
