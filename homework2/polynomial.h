#pragma once
#include <iostream>
#include <algorithm>
#include <sstream>

class Polynomial {
private:
    int minPwr;
    int maxPwr;
    int* array;
public:
    int getSize() const;
    Polynomial();
    Polynomial(int minPwr, int maxPwr, const int* array);
    Polynomial(const Polynomial &other);
    virtual ~Polynomial();
    Polynomial& operator=(const Polynomial &other);
    static Polynomial RemoveZeros(const Polynomial &p);
    bool operator==(const Polynomial &other);
    bool operator!=(const Polynomial &other);
    Polynomial operator-() const;
    friend Polynomial NewArray(const Polynomial &first, const Polynomial &second, bool flag);
    Polynomial& operator+=(const Polynomial &other);
    Polynomial& operator-=(const Polynomial &other);
    friend Polynomial operator*(const Polynomial &p, int number);
    friend Polynomial operator*(int number, const Polynomial &p);
    friend Polynomial operator*(const Polynomial &first, const Polynomial &second);
    Polynomial operator*=(const Polynomial &other) const;
    Polynomial operator/(int number);
    Polynomial operator/=(int number);
    friend std::ostream& operator<<(std::ostream& ss, const Polynomial& p);
    friend std::istream& operator>>(std::istream& in, Polynomial& p);
    int operator[](int i) const;
    int& operator[](int i);
    double get(int i) const;
};
Polynomial operator+(const Polynomial &first, const Polynomial &second);
Polynomial operator-(const Polynomial &first, const Polynomial &second);
