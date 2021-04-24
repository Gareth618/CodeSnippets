#include <bits/stdc++.h>
using namespace std;

template<class T>
class SegTree {
    int n;
    vector<T> tree;
    function<T(const T&, const T&)> fun;
    T ide;

    void build(int node, int left, int right, vector<T>& v) {
        if (left == right) {
            tree[node] = v[left];
            return;
        }
        int mid = (left + right) / 2;
        build(2 * node, left, mid, v);
        build(2 * node + 1, mid + 1, right, v);
        tree[node] = fun(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int left, int right, int pos, T val, function<void(T&, const T&)> upd) {
        if (left == right) {
            upd(tree[node], val);
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid)
            update(2 * node, left, mid, pos, val, upd);
        else
            update(2 * node + 1, mid + 1, right, pos, val, upd);
        tree[node] = fun(tree[2 * node], tree[2 * node + 1]);
    }

    T query(int node, int left, int right, int qLeft, int qRight) {
        if (left == qLeft && right == qRight)
            return tree[node];
        int mid = (left + right) / 2;
        if (qRight <= mid)
            return query(2 * node, left, mid, qLeft, qRight);
        if (qLeft > mid)
            return query(2 * node + 1, mid + 1, right, qLeft, qRight);
        return fun(
            query(2 * node, left, mid, qLeft, mid),
            query(2 * node + 1, mid + 1, right, mid + 1, qRight)
        );
    }

public:
    SegTree(int n, function<T(const T&, const T&)> fun = plus<T>(), T ide = T()) :
        n(n), tree(4 * n, ide), fun(fun), ide(ide) { }
    SegTree(vector<T> v, function<T(const T&, const T&)> fun = plus<T>(), T ide = T()) :
        SegTree(v.size(), fun, ide) { build(1, 0, n - 1, v); }

    void update(int pos, T val, function<void(T&, const T&)> upd = [](T& x, const T& y) { x = y; }) {
        update(1, 0, n - 1, pos, val, upd);
    }

    T query(int left, int right) {
        if (left > right)
            return ide;
        return query(1, 0, n - 1, left, right);
    }
};
