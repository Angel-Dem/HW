#include <iostream>
#include <vector>

template <typename T>
class Vector {
    T* ptr;
    size_t size_;
    size_t capacity_;
    friend void print (const Vector<int>& a);
public:
    Vector() : ptr(nullptr), size_(0), capacity_(0) {}
    ~Vector(){ delete[] ptr;}

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void push_back(T value) {
        if (size_ == capacity_) {
            size_t newCap = (capacity_ == 0 ? 1 : capacity_ * 2);
            int* newData = new int[newCap];

            for (size_t i = 0; i < size_; i++) {
                newData[i] = ptr[i];
            }

            delete[] ptr;
            ptr = newData;
            capacity_ = newCap;
        }
        ptr[size_++] = value;
    }
    int& operator[] (size_t value) const {
        return ptr[value];
    }

    void pop_back() {
        if (size_ == 0)
            return;
        size_--;
    }

    void clear() {
        if (size_ == 0) return;
        for (int i = 0; i < size_; i++) ptr[i].~T();
        size_ = 0;
    }
    void insert(T value, size_t it) {
        if (it > size_) {
            std::cout<<"Error: iterator out of range\n";
            return;
        }
        if (size_ == capacity_) {
            size_t newCap = (capacity_ == 0 ? 1 : capacity_ * 2);
            int* newData = new int[newCap];
            for (size_t i = 0; i < it; i++) {
                newData[i] = ptr[i];
            }
            newData[it] = value;
            for (size_t i = it; i < size_; i++) {
                newData[i + 1] = ptr[i];
            }
            delete[] ptr;
            ptr = newData;
            capacity_ = newCap;
        }
        else {
            for (size_t i = size_; i > it; i--) {
                ptr[i] = ptr[i - 1];
            }
            ptr[it] = value;
        }
        size_++;
    }
    void erase(size_t it) {
        if (it >size_){
            std::cout <<"Error: iterator out of range\n";
            return;
        }
        for (size_t i = it; i < size_ - 1; i++) {
            ptr[i] = ptr[i + 1];
        }

        size_--;
    }
    Vector(const Vector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;

        ptr = new int[capacity_];
        for (size_t i = 0; i < size_; i++)
            ptr[i] = other.ptr[i];
    }

};

void print(const Vector<int>& a) {
    for (int i = 0;i < a.size_;++i) {
        std::cout << a[i] << " ";
    }
    std::cout << '\n';
}

int main() {
    Vector<int> v;

    std::cout << "Push back 1, 2, 3\n";
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << "v: ";
    print(v);
    std::cout << "\nSize: " << v.size() << ", Capacity: " << v.capacity() << "\n";

    std::cout << "\nInsert 10 at position 1\n";
    v.insert(10, 1);
    std::cout << "v: ";
    print(v);

    std::cout << "\nErase element at position 2\n";
    v.erase(2);
    std::cout << "v: ";
    print(v);

    std::cout << "\nPop back\n";
    v.pop_back();
    std::cout << "v: ";
    print(v);

    std::cout << "\nClear vector\n";
    v.clear();
    std::cout << "Size: " << v.size() << ", empty? " << v.empty() << "\n";

    std::cout << "\nTest copy\n";
    v.push_back(5);
    v.push_back(6);
    Vector<int> v2 = v;

    std::cout << "v2 after copy: ";
    print(v);

    std::cout << "\nLet v2[0] = 100\n";
    v2[0] = 100;

    std::cout << "v2: ";
    print(v);

    std::cout << "original: ";
    print(v);

    return 0;
}
