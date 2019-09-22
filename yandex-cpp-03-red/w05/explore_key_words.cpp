#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <algorithm>
#include <future>
#include <functional>
using namespace std;

const size_t N_THREADS = 4;
const size_t N_LINES = 10000;

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

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats& other) {
        for (const auto& entry : other.word_frequences) {
            word_frequences[entry.first] += entry.second;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats stats;

    vector<string> words = SplitIntoWords(line);
    for (const string& word : words) {
        if (key_words.count(word)) {
            stats.word_frequences[word] += 1;
        }
    }

    return stats;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
    Stats result;
    for (string line; getline(input, line);) {
        result += ExploreLine(key_words, line);
    }
    return result;
}


Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats result;
    vector<string> lines;
    string line;
    while (getline(input, line)) {
        lines.push_back(move(line));
    }

    vector<stringstream> streams;
    streams.reserve(N_THREADS);
    for (size_t i = 0; i < N_THREADS; ++i) {
        stringstream ss;
        for (
            auto it = lines.begin() + lines.size() * i / N_THREADS;
            it != lines.end() && it != lines.begin() + lines.size() * (i + 1) / N_THREADS;
            ++it
        ) {
            ss << *it << '\n';
        }
        streams.emplace_back(move(ss));
    }

    vector<future<Stats>> futures;
    futures.reserve(N_THREADS);
    for (auto& e : streams) {
        futures.emplace_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(e)));
    }
    for (auto& e : futures) {
        result += e.get();
    }
    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    {
        LOG_DURATION ("ExploreKeyWords");
        TestRunner tr;
        RUN_TEST(tr, TestBasic);
    }
}
