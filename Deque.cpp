#include <bits/stdc++.h>
using namespace std;

template<class T>
class Deque {
    int ptr;
    deque<pair<T, int>> dq;
    function<bool(T, T)> fun;
    T null;

public:
    Deque(function<bool(T, T)> fun = [](T x, T y) { return min(x, y); }, T null = 1e9) :
        ptr(0), fun(fun), null(null) { }

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
        return dq.empty() ? null : dq.front().first;
    }
};
