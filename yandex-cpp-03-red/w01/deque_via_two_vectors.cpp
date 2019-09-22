#include <iostream>
#include <vector>

//#include "test_runner.h"

using namespace std;


template <typename T>
class Deque {
public:
    Deque() {};

    bool Empty() const {
        return _front.empty() && _back.empty();
    }

    size_t Size() const {
        return _front.size() + _back.size();
    }

    T& operator[](size_t index) {
        return At(index);
    }

    const T& operator[](size_t index) const {
        const T& e = At(index);
        return e;
    }

    T& At(size_t index) {
        if (index >= Size()) {
            throw out_of_range("Out of range");
        }

        if (index < _front.size()) {
            return _front[_front.size() - 1 - index];
        } else {
            return _back[index - _front.size()];
        }
    }

    const T& At(size_t index) const {
        if (index >= Size()) {
            throw out_of_range("Out of range");
        }

        if (index < _front.size()) {
            return _front[_front.size() - 1 - index];
        } else {
            return _back[index - _front.size()];
        }
    }

    T& Front() {
        if (!_front.empty()) {
            return _front.back();
        } else if (!_back.empty()) {
            return _back.front();
        } else {
            throw out_of_range("Out of range");
        }
    }

    const T& Front() const {
        if (!_front.empty()) {
            return _front.back();
        } else if (!_back.empty()) {
            return _back.front();
        } else {
            throw out_of_range("Out of range");
        }
    }

    T& Back() {
        if (!_back.empty()) {
            return _back.back();
        } else if (!_front.empty()) {
            return _front.front();
        } else {
            throw out_of_range("Out of range");
        }
    }

    const T& Back() const {
        if (!_back.empty()) {
            return _back.back();
        } else if (!_front.empty()) {
            return _front.front();
        } else {
            throw out_of_range("Out of range");
        }
    }

    void PushFront(const T& element) {
        _front.push_back(element);
    }

    void PushBack(const T& element) {
        _back.push_back(element);
    }

private:
    vector<T> _front;
    vector<T> _back;
};


/*
void TestEmpty() {
    Deque<int> dq;
    ASSERT(dq.Empty());
}

void TestSize() {
    Deque<int> dq_0;
    ASSERT_EQUAL(dq_0.Size(), 0);

    Deque<int> dq_1;
    dq_1.PushFront(1);
    ASSERT_EQUAL(dq_1.Size(), 1);

    Deque<int> dq_1b;
    dq_1b.PushBack(1);
    ASSERT_EQUAL(dq_1b.Size(), 1);

    Deque<int> dq_2;
    dq_2.PushFront(1);
    dq_2.PushBack(1);
    ASSERT_EQUAL(dq_2.Size(), 2);
}

void TestFront() {
    Deque<int> dq_empty;
    bool is_exception = false;
    try {
        dq_empty.Front();
    } catch (out_of_range&) {
        is_exception = true;
    }
    ASSERT(is_exception);

    Deque<int> dq_1;
    dq_1.PushFront(1);
    int res = dq_1.Front();
    ASSERT_EQUAL(res, 1);
    Deque<int> dq_2;
    dq_2.PushFront(2);
    dq_2.PushFront(1);
    res = dq_2.Front();
    ASSERT_EQUAL(res, 1);

    Deque<int> dq_1b;
    dq_1b.PushBack(1);
    res = dq_1b.Front();
    ASSERT_EQUAL(res, 1);
    Deque<int> dq_2b;
    dq_2b.PushBack(1);
    dq_2b.PushBack(2);
    res = dq_2b.Front();
    ASSERT_EQUAL(res, 1);

    Deque<int> dq_2fb;
    dq_2fb.PushFront(1);
    dq_2fb.PushBack(2);
    res = dq_2fb.Front();
    ASSERT_EQUAL(res, 1);
    Deque<int> dq_4fb;
    dq_4fb.PushFront(2);
    dq_4fb.PushFront(1);
    dq_4fb.PushBack(3);
    dq_4fb.PushBack(4);
    res = dq_4fb.Front();
    ASSERT_EQUAL(res, 1);
}

void TestBack() {
    Deque<int> dq_empty;
    bool is_exception = false;
    try {
        dq_empty.Back();
    } catch (out_of_range&) {
        is_exception = true;
    }
    ASSERT(is_exception);

    Deque<int> dq_1;
    dq_1.PushBack(1);
    int res = dq_1.Back();
    ASSERT_EQUAL(res, 1);
    Deque<int> dq_2;
    dq_2.PushBack(2);
    dq_2.PushBack(1);
    res = dq_2.Back();
    ASSERT_EQUAL(res, 1);

    Deque<int> dq_1f;
    dq_1f.PushFront(1);
    res = dq_1f.Back();
    ASSERT_EQUAL(res, 1);
    Deque<int> dq_2f;
    dq_2f.PushFront(1);
    dq_2f.PushFront(2);
    res = dq_2f.Back();
    ASSERT_EQUAL(res, 1);

    Deque<int> dq_2fb;
    dq_2fb.PushFront(2);
    dq_2fb.PushBack(1);
    res = dq_2fb.Back();
    ASSERT_EQUAL(res, 1);
}

void TestAt() {
    Deque<int> dq_1f;
    dq_1f.PushFront(1);
    int res = dq_1f.At(0);
    ASSERT_EQUAL(res, 1);

    Deque<int> dq_1b;
    dq_1b.PushBack(1);
    res = dq_1b.At(0);
    ASSERT_EQUAL(res, 1);
}
*/


int main() {
    /*
    TestRunner tr;
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestSize);
    RUN_TEST(tr, TestFront);
    RUN_TEST(tr, TestBack);
    RUN_TEST(tr, TestAt);
    */
}
