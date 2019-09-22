#include "test_runner.h"
#include <vector>
#include <numeric>
#include <future>

using namespace std;

const size_t PAGE_SIZE = 2000;


template <typename Iterator>
class Page {
private:
    Iterator _begin;
    Iterator _end;
    size_t _size;

public:
    Page(Iterator begin, Iterator end)
        : _begin(begin)
        , _end(end)
        , _size(distance(_begin, _end))
    {}

    Iterator begin() const {
        return _begin;
    }

    Iterator end() const {
        return _end;
    }

    size_t size() const {
        return _size;
    }
};


template <typename Iterator>
class Paginator {
private:
    vector<Page<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (auto it = begin; it < end; it += page_size) {
            pages.push_back({it, min(it + page_size, end)});
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }
};


template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}


template<typename Vectors>
int64_t CalculateMatrixSumSingleThread(const Vectors& matrix) {
    int64_t result = 0;
    for (const auto& row : matrix) {
        result += accumulate(begin(row), end(row), 0);
    }

    return result;
}


int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
     vector<future<int64_t>> futures;
     for (const auto& page : Paginate(matrix, PAGE_SIZE)) {
         futures.push_back(
            async([=] {
                return CalculateMatrixSumSingleThread(page);
            })
         );
     }

     int64_t result = 0;
     for (auto& f : futures) {
         result += f.get();
     }

     return result;
}


void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
