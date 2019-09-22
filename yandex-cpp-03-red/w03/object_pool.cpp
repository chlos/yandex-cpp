#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        T* object;
        if (!objects_deallocated_.empty()) {
            object = objects_deallocated_.front();
            objects_deallocated_.pop();
        } else {
            object = new T;
        }
        objects_allocated_.insert(object);

        return object;
    }

    T* TryAllocate() {
        T* object;
        if (!objects_deallocated_.empty()) {
            object = objects_deallocated_.front();
            objects_deallocated_.pop();
        } else {
            return nullptr;
        }
        objects_allocated_.insert(object);

        return object;
    }

    void Deallocate(T* object) {
        const bool is_allocated = (objects_allocated_.find(object) != objects_allocated_.end());
        if (objects_allocated_.empty() || !is_allocated) {
            throw invalid_argument("Object not allocated");
        }

        objects_deallocated_.push(object);
        objects_allocated_.erase(object);
    }

    ~ObjectPool() {
        for (auto object : objects_allocated_) {
            delete object;
        }

        while (!objects_deallocated_.empty()) {
            delete objects_deallocated_.front();
            objects_deallocated_.pop();
        }
    }

private:
    set<T*> objects_allocated_;
    queue<T*> objects_deallocated_;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
