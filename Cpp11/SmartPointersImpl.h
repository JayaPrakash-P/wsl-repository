//SOURCE : ChatGPT

#include <iostream>

template<typename T>
class MySharedPtr {
private:
    T* ptr_;
    int* count_;
public:
    MySharedPtr() : ptr_(nullptr), count_(nullptr) {}

    explicit MySharedPtr(T* ptr) : ptr_(ptr), count_(new int(1)) {}

    MySharedPtr(const MySharedPtr<T>& other) : ptr_(other.ptr_), count_(other.count_) {
        (*count_)++;
    }

    MySharedPtr<T>& operator=(const MySharedPtr<T>& other) {
        if (this != &other) {
            if (ptr_ && (--(*count_) == 0)) {
                delete ptr_;
                delete count_;
            }
            ptr_ = other.ptr_;
            count_ = other.count_;
            (*count_)++;
        }
        return *this;
    }

    ~MySharedPtr() {
        if (ptr_ && (--(*count_) == 0)) {
            delete ptr_;
            delete count_;
        }
    }

    T* operator->() const {
        return ptr_;
    }

    T& operator*() const {
        return *ptr_;
    }

    int use_count() const {
        return count_ ? *count_ : 0;
    }
};

class MyClass {
public:
    MyClass() { std::cout << "MyClass constructed" << std::endl; }
    ~MyClass() { std::cout << "MyClass destroyed" << std::endl; }
};

int main() {
    MySharedPtr<MyClass> ptr1(new MyClass);
    MySharedPtr<MyClass> ptr2 = ptr1;
    std::cout << "Number of shared_ptr objects pointing to the MyClass instance: " << ptr1.use_count() << std::endl;
    return 0;
}
