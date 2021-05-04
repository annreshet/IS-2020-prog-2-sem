#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>
#include <set>
#include <iterator>
#include <functional>

template<class TIterator, typename UnaryPredicate>
bool allOf(TIterator begin, TIterator end, UnaryPredicate pred) {
    for (; begin != end; begin++) {
        if (!pred(*begin))
            return false;
    }
    return true;
}

template<class TIterator, typename UnaryPredicate>
bool anyOf(TIterator begin, TIterator end, UnaryPredicate pred) {
    for (; begin != end; begin++) {
        if (pred(*begin))
            return true;
    }
    return false;
}

template<class TIterator, typename UnaryPredicate>
bool noneOf(TIterator begin, TIterator end, UnaryPredicate pred) {
    for (; begin != end; begin++) {
        if (pred(*begin))
            return false;
    }
    return true;
}

template<class TIterator, typename UnaryPredicate>
bool oneOf(TIterator begin, TIterator end, UnaryPredicate pred) {
    int cnt = 0;
    for (; begin != end; begin++) {
        if (pred(*begin)) {
            cnt++;
            if (cnt > 1)
                break;
        }
    }
    return cnt == 1? true:false;
}

template<class TIterator, typename UnaryPredicate>
bool isSorted(TIterator begin, TIterator end, UnaryPredicate pred) {
    for (; begin != end - 1; begin++) {
        if (!pred(*begin, *(begin + 1)))
            return false;
    }
    return true;
}

template<class TIterator>
bool isSorted(TIterator begin, TIterator end) {
    bool r = true;
    for (; begin != end - 1; begin++) {
        if (*begin > *(begin + 1)) {
            r = false;
            break;
        }
    }
    return r;
}

template<class TIterator, typename UnaryPredicate>
bool isPartitioned(TIterator begin, TIterator end, UnaryPredicate pred) {
    auto it = begin;
    for (; begin != end; begin++) {
        if (!pred(*begin)) {
            it = begin;
            break;
        }
    }
    for (it; it != end; it++) {
        if (pred(*it))
            return false;
    }
    return true;
}

template<class TIterator, typename T>
TIterator findNot(TIterator begin, TIterator end, const T& value) {
    for (; begin != end; begin++) {
        if (*begin != value)
            return begin;
    }
    return end;
}

template<class TIterator, typename T>
TIterator findBackward(TIterator begin, TIterator end, const T& value) {
    auto it = end;
    for (; begin != end; begin++) {
        if (*begin == value)
            it = begin;
    }
    return it;
}

template<class TIterator, typename UnaryPredicate>
bool isPalindrome(TIterator begin, TIterator end, UnaryPredicate pred) {
    auto it = end;
    end--;
    while (begin != end && begin != it) {
        if (!pred(*begin, *end))
            return false;
        begin++;
        end--;
    }
    return true;
}
