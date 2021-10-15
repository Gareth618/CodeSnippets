#include <bits/stdc++.h>
using namespace std;

template<class T>
class Deque {
    int ptr;
    deque<pair<T, int>> dq;
    function<bool(T, T)> fun;
    T ide;

public:
    Deque(function<bool(T, T)> fun = [](T x, T y) { return min(x, y); }, T ide = 1e9) :
        ptr(0), fun(fun), ide(ide) { }

    void push(T val) {
        while (!dq.empty() && val < dq.back().first)
            dq.pop_back();
        dq.emplace_back(val, ++ptr);
    }

    void pop(int len) {
        while (!dq.empty() && dq.front().second <= ptr - len)
            dq.pop_front();
    }

    T query() {
        return dq.empty() ? ide : dq.front().first;
    }
};
