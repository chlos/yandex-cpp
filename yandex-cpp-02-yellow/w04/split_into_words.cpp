#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto word_begin_it = begin(s);

    while (true) {
        auto word_end_it = find(word_begin_it, end(s), ' ');
        result.push_back(string(word_begin_it, word_end_it));

        if (word_end_it == end(s)) {
            break;
        }
        word_begin_it = ++word_end_it;
    }

    return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
