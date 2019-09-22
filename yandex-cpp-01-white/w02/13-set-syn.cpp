#include <iostream>
#include <set>
#include <map>

using namespace std;

void PrintMap(map<string, set<string>> m) {
    cout << "\n\n=====\n";  // FIXME
    for (auto e : m) {
        cout << e.first << ":";
        for (auto v_e : e.second) {
            cout << " " << v_e;
        }
        cout << endl;
    }
}

bool is_synonym(map<string, set<string>>& synonyms, const string& word1, const string& word2) {
    if (synonyms[word1].count(word2)) {
        return true;
    } else {
        return false;
    }
}

int count_synonyms(map<string, set<string>>& synonyms, const string& word) {
    return synonyms[word].size();
}

int main() {
    map<string, set<string>> synonyms;

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string cmd;
        cin >> cmd;
        //cout << "\nq = " << i << "; cmd = " << cmd << endl;    // FIXME

        if (cmd == "ADD") {
            string word1, word2;
            cin >> word1 >> word2;
            synonyms[word1].insert(word2);
            synonyms[word2].insert(word1);
            //cout << "added: " << word1 << " " << word2 << endl;     // FIXME
            //PrintMap(synonyms);    // FIXME

        } else if (cmd == "COUNT") {
            string word;
            cin >> word;
            cout << count_synonyms(synonyms, word) << endl;

        } else if (cmd == "CHECK") {
            string word1, word2;
            cin >> word1 >> word2;
            //cout << "check words: " << word1 << " " << word2 << endl;     // FIXME
            if (is_synonym(synonyms, word1, word2)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }

    }

    //PrintMap(synonyms);    // FIXME

    return 0;
}
