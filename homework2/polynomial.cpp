#include "polynomial.h"

int Polynomial::getSize() const {
    return maxPwr - minPwr + 1;
}

Polynomial::Polynomial() {
    minPwr = 0;
    maxPwr = 0;
    array = nullptr;
}

Polynomial::Polynomial(int minPwr, int maxPwr, const int *array) {
    this->minPwr = minPwr;
    this->maxPwr = maxPwr;
    this->array = new int [getSize()];
    for (int i = minPwr; i <= maxPwr; i++) {
        this->array[i - minPwr] = array[i - minPwr];
    }
}

Polynomial::Polynomial(const Polynomial &other) {
    if (other.array == nullptr) {
        this->minPwr = 0;
        this->maxPwr = 0;
        this->array = nullptr;
    } else {
        this->minPwr = other.minPwr;
        this->maxPwr = other.maxPwr;
        this->array = new int [getSize()];
        for (int i = minPwr; i <= maxPwr; i++) {
            this->array[i - minPwr] = other.array[i - minPwr];
        }
    }
}

Polynomial::~Polynomial() {
    delete[] array;
}

Polynomial &Polynomial::operator=(const Polynomial &other) {
    if (this != &other) {
        if (other.array == nullptr) {
            this->minPwr = 0;
            this->maxPwr = 0;
            this->array = nullptr;
            return *this;
        }
        else {
            delete[] array;
            this->minPwr = other.minPwr;
            this->maxPwr = other.maxPwr;
            this->array = new int [getSize()];
            for (int i = 0; i < getSize(); i++)
                this->array[i] = other.array[i];
        }
    }
    return *this;
}

//fixed too many object copying
//Polynomail&
void Polynomial::RemoveZeros() {
    if (array != nullptr) {
        int cnt1 = 0;
        int cnt2 = getSize() - 1;
        while (array[cnt1] == 0){
            minPwr++;
            cnt1++;
        }
        while (array[cnt2] == 0) {
            maxPwr--;
            cnt2--;
        }
        if (minPwr == maxPwr) {
            array[0] = array[cnt1];
        }
    }
}


bool Polynomial::operator==(const Polynomial &other) {
    if (this != &other) {
        Polynomial first = *this;
        Polynomial second = other;
        first.RemoveZeros();
        second.RemoveZeros();
        if ((first.minPwr == 0 && first.maxPwr == 0) || (second.minPwr == 0 && second.maxPwr == 0)) {
            if (first.minPwr == 0 && first.maxPwr == 0 && second.minPwr == 0 && second.maxPwr == 0)
                return true;
            else
                return false;
        }
        if ((first.minPwr == second.minPwr) && (first.maxPwr == second.maxPwr) && (first.getSize() == second.getSize())) {
            for (int i = first.minPwr; i <= first.maxPwr; i++) {
                if (first.array[i - first.minPwr] != second.array[i - first.minPwr])
                    return false;
            }
            return true;
        }
        else
            return false;
    }
    else
        return true;
}

bool Polynomial::operator!=(const Polynomial &other) {
    return !(this == &other);
}

Polynomial Polynomial::operator-() const{
    Polynomial p = *this;
    std::for_each(p.array, p.array + getSize(), [](int &i){ i = -i; });
    return p;
}

Polynomial NewArray(const Polynomial &first, const Polynomial &second, bool flag) {
    Polynomial p;
    p.minPwr = std::min(first.minPwr, second.minPwr);
    p.maxPwr = std::max(first.maxPwr, second.maxPwr);
    p.array = new int[p.getSize()] {0};
    int diff = second.minPwr - first.minPwr;
    for (int i = first.minPwr; i <= first.maxPwr; i++)
        p.array[i - first.minPwr] = first.array[i - first.minPwr];
    if (flag)
        for (int i = second.minPwr; i <= second.maxPwr; i++)
            p.array[i + diff - second.minPwr] += second.array[i - second.minPwr];
    else
        for (int i = second.minPwr; i <= second.maxPwr; i++)
            p.array[i + diff - second.minPwr] -= second.array[i - second.minPwr];
    return p;
}

Polynomial &Polynomial::operator+=(const Polynomial &other) {
    if (this->array == nullptr) {
        *this = other;
        return *this;
    }
    if (other.array == nullptr) {
        return *this;
    }
    if (this->minPwr < other.minPwr)
        *this = NewArray(*this, other, true);
    else
        *this = NewArray(other, *this, true);
    return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial &other) {
    if (this->array == nullptr) {
        *this = other;
        return *this;
    }
    if (other.array == nullptr) {
        return *this;
    }
    if (this->minPwr < other.minPwr)
        *this = NewArray(*this, other, false);
    else
        *this = NewArray(other, *this, false);
    return *this;
}

Polynomial operator+(const Polynomial &first, const Polynomial &second) {
    Polynomial ans = first;
    ans += second;
    return ans;
}

Polynomial operator-(const Polynomial &first, const Polynomial &second) {
    Polynomial ans = first;
    ans -= second;
    return ans;
}

Polynomial operator*(const Polynomial &first, const Polynomial &second) {
    Polynomial res = first;
    res *= second;
    return res;
}

Polynomial operator*(int number, const Polynomial &p) {
    Polynomial num(0, 0, new int[1] {number});
    Polynomial res = p;
    res *= num;
    return res;
}

Polynomial operator*(const Polynomial &p, int number) {
    return number * p;
}

//fixed * from *=
//fixed returns Polynomial&
Polynomial& Polynomial::operator*=(const Polynomial &other) {
    if (this->array == nullptr || other.array == nullptr) {
        *this = Polynomial();
        return *this;
    }
    int* temp = this->array;
    int oldMinPwr = this->minPwr;
    int oldMaxPwr = this->maxPwr;
    this->minPwr = this->minPwr + other.minPwr;
    this->maxPwr = this->maxPwr + other.maxPwr;
    this->array = new int[this->getSize()] {0};
    for (int i = oldMinPwr; i <= oldMaxPwr; i++) {
        for (int j = other.minPwr; j <= other.maxPwr; j++) {
            this->array[i + j - this->minPwr] += temp[i - oldMinPwr] * other.array[j - other.minPwr];
        }
    }
    return *this;
}

Polynomial Polynomial::operator/(int number) {
    Polynomial temp = *this;
    std::for_each(temp.array, temp.array + temp.getSize(), [number](int &i) { i /= number; });
    temp.RemoveZeros();
    return temp;
}

Polynomial Polynomial::operator/=(int number) {
    return *this / number;
}

std::ostream& operator<<(std::ostream& ss, const Polynomial& p){
    if (p.array == nullptr) {
        ss << 0;
        return ss;
    }
    if (p.maxPwr == p.minPwr) {
        ss << p.array[0];
    }
    else {
        int newMaxPwr = p.maxPwr;
        while (p.array[newMaxPwr - p.minPwr] == 0) {
            newMaxPwr -= 1;
        }
        if (newMaxPwr > 1 || newMaxPwr < 0) {
            if (p.array[newMaxPwr - p.minPwr] == -1)
                ss << "-x^" << newMaxPwr;
            if (p.array[newMaxPwr - p.minPwr] == 1)
                ss << "x^" << newMaxPwr;
            if ((p.array[newMaxPwr - p.minPwr]  > 1) || (p.array[newMaxPwr - p.minPwr] < -1))
                ss << p.array[newMaxPwr - p.minPwr] << "x^" << newMaxPwr;
        }
        if (newMaxPwr == 1) {
            if (p.array[newMaxPwr - p.minPwr] == -1)
                ss << "-x";
            if (p.array[newMaxPwr - p.minPwr] == 1)
                ss << "+x";
            if (p.array[newMaxPwr - p.minPwr] > 1)
                ss << "+" << p.array[newMaxPwr - p.minPwr] << "x";
            if (p.array[newMaxPwr - p.minPwr] < -1)
                ss << p.array[newMaxPwr - p.minPwr] << "x";
        }
        if (newMaxPwr == 0) {
            if (p.array[newMaxPwr - p.minPwr] > 0)
                ss << "+" << p.array[newMaxPwr - p.minPwr];
            if (p.array[newMaxPwr - p.minPwr] < 0)
                ss << p.array[newMaxPwr - p.minPwr];
        }
        for (int i = newMaxPwr - 1; i >= p.minPwr; i--) {
            if (i > 1 || i < 0) {
                if (p.array[i - p.minPwr] == -1)
                    ss << "-x^" << i;
                if (p.array[i - p.minPwr] == 1)
                    ss << "+x^" << i;
                if (p.array[i - p.minPwr]  > 1)
                    ss << "+" << p.array[i - p.minPwr] << "x^" << i;
                if (p.array[i - p.minPwr] < -1)
                    ss << p.array[i - p.minPwr] << "x^" << i;
            }
            if (i == 1) {
                if (p.array[i - p.minPwr] == -1)
                    ss << "-x";
                if (p.array[i - p.minPwr] == 1)
                    ss << "+x";
                if (p.array[i - p.minPwr] > 1)
                    ss << "+" << p.array[i - p.minPwr] << "x";
                if (p.array[i - p.minPwr] < -1)
                    ss << p.array[i - p.minPwr] << "x";
            }
            if (i == 0) {
                if (p.array[i - p.minPwr] > 0)
                    ss << "+" << p.array[i - p.minPwr];
                if (p.array[i - p.minPwr] < 0)
                    ss << p.array[i - p.minPwr];
            }
        }
    }
    return ss;
}

std::istream &operator>>(std::istream &in, Polynomial &p) {
    in >> p.minPwr >> p.maxPwr;
    p.array = new int[p.getSize()];
    for (int i = p.minPwr; i <= p.maxPwr; i++) {
        in >> p.array[i - p.minPwr];
    }
    return in;
}

int Polynomial::operator[](int i) const {
    if ((i <= this->maxPwr) && (i >= this->minPwr))
        return this->array[i - this->minPwr];
    else
        return 0;
}

int& Polynomial::operator[](int i){
    if (i > this->maxPwr) {
        int* newArr = new int[i - this->minPwr + 1] {0};
        for (int j = this->minPwr; j <= this->maxPwr; j++) {
            newArr[j - this->minPwr] = this->array[j - minPwr];
        }
        this->maxPwr = i;
        delete[] this->array;
        this->array = newArr;
    }
    if (i < this->minPwr) {
        int* newArr = new int[this->maxPwr - i + 1] {0};
        int diff = this->minPwr - i;
        for (int j = this->minPwr; j <= this->maxPwr; j++) {
            newArr[j - this->minPwr + diff] = this->array[j - this->minPwr];
        }
        this->minPwr = i;
        delete[] this->array;
        this->array = newArr;
    }
    return this->array[i - this->minPwr];
}

//fixed get O(n)
double Polynomial::get(int i) const {
    int newMinPwr = 0;
    int newMaxPwr = this->maxPwr - this->minPwr;
    double ans = this->array[getSize() - 1] * i + this->array[getSize() - 2];
    for (int j = newMaxPwr - 2; j >= newMinPwr; j--) {
        ans = ans * i + this->array[j - newMinPwr];
    }
    ans *= pow(i, this->minPwr);
    return ans;
}
