#include <bits/stdc++.h>
using namespace std;

template<class T>
class FenTree {
    int n;
    vector<T> bit;

public:
    FenTree(int n) :
        n(n), bit(n + 1) { }

    void update(int pos, T val) {
        for (int i = pos; i <= n; i += i & -i)
            bit[i] += val;
    }

    void update(int left, int right, T val) {
        if (left <= right) {
            update(left, +val);
            if (right < n) update(right + 1, -val);
        }
    }

    T query(int pos) {
        T sum = 0;
        for (int i = pos; i >= 1; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    T query(int left, int right) {
        if (left > right)
            return 0;
        return query(right) - query(left - 1);
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

public:
    FenTree2D(int m, int n) :
        m(m), n(n), bit(m + 1, vector<T>(n + 1)) { }

    void update(int x, int y, T val) {
        for (int i = x; i <= m; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                bit[i][j] += val;
    }

    void update(int x1, int y1, int x2, int y2, T val) {
        if (x1 <= x2 && y1 <= y2) {
            update(x1, y1, +val);
            if (x2 < m) update(x2 + 1, y1, -val);
            if (y2 < n) update(x1, y2 + 1, -val);
            if (x2 < m && y2 < n) update(x2 + 1, y2 + 1, +val);
        }
    }

    T query(int x, int y) {
        T sum = 0;
        for (int i = x; i >= 1; i -= i & -i)
            for (int j = y; j >= 1; j -= j & -j)
                sum += bit[i][j];
        return sum;
    }

    T query(int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2)
            return 0;
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};

template<int MOD = int(1e9 + 7)>
class ModFenTree {
    static inline void add(int& a, int b) { a += b; if (a >= MOD) a -= MOD; }
    static inline void sub(int& a, int b) { a -= b; if (a <    0) a += MOD; }

    int n;
    vector<int> bit;

public:
    ModFenTree(int n) :
        n(n), bit(n + 1) { }

    void update(int pos, int val) {
        for (int i = pos; i <= n; i += i & -i)
            add(bit[i], val);
    }

    void update(int left, int right, int val) {
        if (left <= right) {
            update(left, +val);
            if (right < n) update(right + 1, -val);
        }
    }

    int query(int pos) {
        int sum = 0;
        for (int i = pos; i >= 1; i -= i & -i)
            add(sum, bit[i]);
        return sum;
    }

    int query(int left, int right) {
        if (left > right)
            return 0;
        int ans = 0;
        add(ans, query(right));
        sub(ans, query(left - 1));
        return ans;
    }
};

template<int MOD = int(1e9 + 7)>
class ModFenTree2D {
    static inline void add(int& a, int b) { a += b; if (a >= MOD) a -= MOD; }
    static inline void sub(int& a, int b) { a -= b; if (a <    0) a += MOD; }

    int m, n;
    vector<vector<int>> bit;

public:
    ModFenTree2D(int m, int n) :
        m(m), n(n), bit(m + 1, vector<int>(n + 1)) { }

    void update(int x, int y, int val) {
        for (int i = x; i <= m; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                add(bit[i][j], val);
    }

    void update(int x1, int y1, int x2, int y2, int val) {
        if (x1 <= x2 && y1 <= y2) {
            update(x1, y1, +val);
            if (x2 < m) update(x2 + 1, y1, -val);
            if (y2 < n) update(x1, y2 + 1, -val);
            if (x2 < m && y2 < n) update(x2 + 1, y2 + 1, +val);
        }
    }

    int query(int x, int y) {
        int sum = 0;
        for (int i = x; i >= 1; i -= i & -i)
            for (int j = y; j >= 1; j -= j & -j)
                add(sum, bit[i][j]);
        return sum;
    }

    int query(int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2)
            return 0;
        int ans = 0;
        add(ans, query(x2, y2));
        sub(ans, query(x1 - 1, y2));
        sub(ans, query(x2, y1 - 1));
        add(ans, query(x1 - 1, y1 - 1));
        return ans;
    }
};
