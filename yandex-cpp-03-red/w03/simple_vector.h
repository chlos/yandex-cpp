#pragma once

#include <algorithm>
#include <cstdlib>
using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() {
        data_ = nullptr;

        size_ = 0;
        capacity_ = 0;
    }
    explicit SimpleVector(size_t size) {
        data_ = new T[size];

        size_ = size;
        capacity_ = size;
    }

    ~SimpleVector() {
        delete[] data_;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    T* begin() {
        return data_;
    }
    T* end() {
        return data_ + Size();
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T& value) {
        if (Size() >= Capacity()) {
            DoubleCapacity_();
        }
        data_[Size()] = value;
        ++size_;
    }

private:
    T* data_;

    size_t size_;
    size_t capacity_;

    void DoubleCapacity_() {
        size_t new_capacity;
        if (Capacity() == 0) {
            new_capacity = 1;
        } else {
            new_capacity = Capacity() * 2;
        }

        T* new_data = new T[new_capacity];
        if (Capacity() != 0) {
            copy(begin(), end(), new_data);
            delete[] data_;
        }

        data_ = new_data;
        capacity_ = new_capacity;
    }
};
