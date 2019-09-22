#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <mutex>
#include <future>
using namespace std;

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T())
        : value(move(initial))
    {
    }

    struct Access {
        T& ref_to_value;
        lock_guard<mutex> lck;
    };

    Access GetAccess() {
        return {value, lock_guard<mutex>(mtx)};
    }

private:
    T value;
    mutex mtx;
};

class InvertedIndex {
public:
    InvertedIndex() = default;
    explicit InvertedIndex(istream& document_input);

    const vector<pair<size_t, size_t>> Lookup(const string& word) const;

    const string& GetDocument(size_t id) const {
        return docs[id];
    }

    size_t GetDocumentSize() const {
        return docs.size();
    }

private:
    unordered_map<string, vector<pair<size_t, size_t>>> index;
    vector<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  void UpdateIndex(istream& document_input, Synchronized<InvertedIndex>& index);
  void AddQueriesStreamSingleThread(istream& query_input, ostream& search_results_output);

  Synchronized<InvertedIndex> index;
  vector<future<void>> futures;
};
