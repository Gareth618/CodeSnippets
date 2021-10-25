#include <bits/stdc++.h>
using namespace std;

template<class T>
class FenTree {
    int n;
    vector<T> bit;
    function<void(T& x, T y)> add;
    function<void(T& x, T y)> sub;

    void updateAdd(int pos, T val) {
        for (int i = pos; i <= n; i += i & -i)
            add(bit[i], val);
    }

    void updateSub(int pos, T val) {
        for (int i = pos; i <= n; i += i & -i)
            sub(bit[i], val);
    }

public:
    FenTree(int n,
        function<void(T& x, T y)> add = [](T& x, T y) { x += y; },
        function<void(T& x, T y)> sub = [](T& x, T y) { x -= y; }
    ) : n(n), bit(n + 1), add(add), sub(sub) { }

    void update(int pos, T val) {
        updateAdd(pos, val);
    }

    void update(int left, int right, T val) {
        if (left <= right) {
            updateAdd(left, val);
            if (right < n) updateSub(right + 1, val);
        }
    }

    T query(int pos) {
        T sum = 0;
        for (int i = pos; i >= 1; i -= i & -i)
            add(sum, bit[i]);
        return sum;
    }

    T query(int left, int right) {
        if (left > right)
            return 0;
        T ans = 0;
        add(ans, query(right));
        sub(ans, query(left - 1));
        return ans;
    }

    int kth(int k) {
        int lo = 0, hi = n + 1;
        while (hi - lo > 1) {
            const int md = (lo + hi) / 2;
            (k > query(md) ? lo : hi) = md;
        }
        return hi;
    }
};

template<class T>
class FenTree2D {
    int m, n;
    vector<vector<T>> bit;
    function<void(T& x, T y)> add;
    function<void(T& x, T y)> sub;

    void updateAdd(int x, int y, T val) {
        for (int i = x; i <= m; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                add(bit[i][j], val);
    }

    void updateSub(int x, int y, T val) {
        for (int i = x; i <= m; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                sub(bit[i][j], val);
    }

public:
    FenTree2D(int m, int n,
        function<void(T& x, T y)> add = [](T& x, T y) { x += y; },
        function<void(T& x, T y)> sub = [](T& x, T y) { x -= y; }
    ) : m(m), n(n), bit(m + 1, vector<T>(n + 1)), add(add), sub(sub) { }

    void update(int x, int y, T val) {
        updateAdd(x, y, val);
    }

    void update(int x1, int y1, int x2, int y2, T val) {
        if (x1 <= x2 && y1 <= y2) {
            updateAdd(x1, y1, val);
            if (x2 < m) updateSub(x2 + 1, y1, val);
            if (y2 < n) updateSub(x1, y2 + 1, val);
            if (x2 < m && y2 < n) updateAdd(x2 + 1, y2 + 1, val);
        }
    }

    T query(int x, int y) {
        T sum = 0;
        for (int i = x; i >= 1; i -= i & -i)
            for (int j = y; j >= 1; j -= j & -j)
                add(sum, bit[i][j]);
        return sum;
    }

    T query(int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2)
            return 0;
        T ans = 0;
        add(ans, query(x2, y2));
        sub(ans, query(x1 - 1, y2));
        sub(ans, query(x2, y1 - 1));
        add(ans, query(x1 - 1, y1 - 1));
        return ans;
    }
};
