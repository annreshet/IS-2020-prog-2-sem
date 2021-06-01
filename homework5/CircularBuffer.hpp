#pragma once
#include <iterator>
#include <c++/4.8.3/stdexcept>

template <typename T>
class Iter {
private:
    T* current;
    T* elements;
    size_t capacity;
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = int;
    using pointer = T*;
    using reference = T&;

    Iter(T* current, T* elements, int capacity) : current(current), elements(elements), capacity(capacity)
    {

    };

    Iter& operator = (const Iter& other) = default;

    bool operator== (Iter const& other) const {
        return current == other.current;
    };

    bool operator!= (Iter const& other) const {
        return !(*this == other);
    };

    bool operator< (Iter const& other) const {
        return current < other.current;
    };

    reference operator*() const {
        return *current;
    };

    Iter& operator++() {
        current++;
        if (current == elements + capacity) {
            current = elements;
        }
        return *this;
    };

    Iter& operator--() {
        if (current == elements) {
            current = elements + capacity - 1;
        }
        current--;
        return *this;
    };

    difference_type operator- (Iter const& other) const {
        if (*this < other)
            return (capacity + current - other.current);
        return current - other.current;
    }

    Iter& operator+= (int x) {
        x %= capacity;
        if (current + x < elements + capacity) {
            current += x;
        }
        else {
            current += x - capacity;
        }
        return *this;
    }

    Iter& operator-= (int x) {
        x %= capacity;
        if (current - x < elements) {
            current += capacity - x;
        }
        else {
            current -= x;
        }
        return *this;
    }
};

template <typename T>
Iter<T> operator- (const Iter<T>& elem, int x) {
    Iter<T> result = elem;
    result -= x;
    return result;
}

template <typename T>
Iter<T> operator+ (const Iter<T>& elem, int n) {
    Iter<T> result = elem;
    result += n;
    return result;
}

template <typename T>
class CircularBuffer {
    friend class Iter<T>;
private:
    T* elements;
    int capacity;
    int size = 0;
    int Begin = 0;
public:
    explicit CircularBuffer(int newCapacity) : capacity(newCapacity + 1) {
        elements = new T[capacity];
    }

    CircularBuffer& operator=(const CircularBuffer& other) {
        if (this == &other) {
            return *this;
        }
        delete[] elements;
        size = other.size;
        capacity = other.capacity;
        Begin = other.Begin;
        elements = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            elements[i] = other.elements[i];
        }
        return *this;
    }

    void ThrowingExceptionsYaaay(int size){
        if (size == 0) {
            std::string ex = "Buffer is empty";
            throw std::out_of_range(ex);
        }
    }

    T first() {
        ThrowingExceptionsYaaay(size);
        return elements[Begin];
    }

    T last() {
        ThrowingExceptionsYaaay(size);
        return elements[(Begin + size - 1) % capacity];
    }

    void ThrowingExceptionsAllOverThePlace(int size, int i) {
        std::string ex;
        if (i >= size) {
            ex = "You have put index " + std::to_string(i) + " which is bigger then buffer size "
                 + std::to_string(size);
            throw std::out_of_range(ex);
        }
        if (size == 0) {
            ex = "Buffer is empty";
            throw std::out_of_range(ex);
        }
        if (i < 0) {
            ex = "You have put index " + std::to_string(i) + " which is less then zero";
            throw std::out_of_range(ex);
        }
    }

    T operator [] (int i) const {
        ThrowingExceptionsAllOverThePlace(size, i);
        return elements[(Begin + i) % capacity];
    }

    T& operator [] (int i) {
        ThrowingExceptionsAllOverThePlace(size, i);
        return elements[(Begin + i) % capacity];
    }

    void addFirst(T value) {
        if (size == 0) {
            elements[0] = value;
        }
        else {
            Begin = (Begin - 1 + capacity) % capacity;
            elements[Begin] = value;
        }
        size++;
        if (size >= capacity) {
            size--;
        }
    }

    void addLast(T value) {
        if (size == 0) {
            elements[0] = value;
        }
        else {
            elements[(Begin + size) % capacity] = value;
        }
        size++;
        if (size >= capacity) {
            size--;
        }
    }

    void delFirst() {
        if (size == 1) {
            Begin = 0;
        }
        else {
            Begin = (Begin + 1) % capacity;
        }
        size--;
    }

    void delLast() {
        if (size == 1) {
            Begin = 0;
        }
        size--;
    }

    void changeCapacity(int newCapacity) {
        T* newElements = new T[newCapacity + 1];
        for (int i = 0; i < capacity; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        capacity = newCapacity + 1;
        elements = newElements;
    }

    Iter<T> begin() const {
        return Iter<T>(elements + Begin, elements, capacity);
    }

    Iter<T> end() const {
        return Iter<T>(elements + (Begin + size) % capacity, elements, capacity);
    }

    ~CircularBuffer() {
        delete[] elements;
    }
};