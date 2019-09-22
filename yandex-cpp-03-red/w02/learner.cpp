#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;


/*** coursera solution:
class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (dict.find(word) == dict.end()) {
        ++newWords;
        dict.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() const {
    return {dict.begin(), dict.end()};
  }
};
 */


class Learner {
private:
    vector<string> dict;
    set<string> unique_dict;

public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            //if (find(dict.begin(), dict.end(), word) == dict.end()) {
            if (unique_dict.count(word) == 0) {
                ++newWords;
                dict.push_back(word);
                unique_dict.insert(word);
            }
        }
        return newWords;
    }

    vector<string> KnownWords() {
        sort(dict.begin(), dict.end());
        dict.erase(unique(dict.begin(), dict.end()), dict.end());
        return dict;
    }
};

int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}
