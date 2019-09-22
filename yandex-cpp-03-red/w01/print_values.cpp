#include "test_runner.h"

#include <ostream>
using namespace std;

//#define PRINT_VALUES(out, x, y) {                   \
    //out << (x) << endl;                             \
    //out << (y) << endl;                             \
//}
#define PRINT_VALUES(out, x, y) (out << (x) << endl << (y) << endl)

int main() {
    TestRunner tr;
    tr.RunTest([] {
      ostringstream output;
      PRINT_VALUES(output, 5, "red belt");
      ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }, "PRINT_VALUES usage example");

    cout << "\n=====" << endl;
    bool check = true;
    if (check) PRINT_VALUES(cout, 'x', 'y'); else PRINT_VALUES(cout, "xx", "yy");
    check = false;
    if (check) PRINT_VALUES(cout, 'x', 'y'); else PRINT_VALUES(cout, "xx", "yy");
    for (int i = 0; i < 5; ++i) PRINT_VALUES(cout, i, i * 10);

    cout << "\n=====" << endl;
    check = true;
    if (check) PRINT_VALUES(cout, "if", ";");
    else {
        PRINT_VALUES(cout, "else", ";");
    }
    check = false;
    if (check) {
        PRINT_VALUES(cout, "if", ";");
    } else PRINT_VALUES(cout, "else", ";");
}
