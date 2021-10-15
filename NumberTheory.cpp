#include <bits/stdc++.h>
using namespace std;

template<int MOD = int(1e9 + 7)>
struct Math {
    static inline void add(int& a, int b) { a += b; if (a >= MOD) a -= MOD; }
    static inline void sub(int& a, int b) { a -= b; if (a <    0) a += MOD; }

    static int pwr(int x, int n) {
        if (!n)
            return 1;
        if (n % 2)
            return 1LL * x * pwr(1LL * x * x % MOD, n / 2) % MOD;
        return pwr(1LL * x * x % MOD, n / 2);
    }

    static int modInv(int x) {
        return pwr(x, MOD - 2);
    }

    static tuple<int, int, int> euclid(int a, int b = MOD) {
        int xa = 1, ya = 0;
        int xb = 0, yb = 1;
        while (b) {
            const int q = a / b;
            const int r = a % b;
            a = b;
            b = r;
            const int xr = xa - q * xb;
            const int yr = ya - q * yb;
            xa = xb; xb = xr;
            ya = yb; yb = yr;
        }
        return make_tuple(a, xa, ya);
    }
};

template<int MOD = int(1e9 + 7)>
class Fact {
    vector<int> fact;
    vector<int> mInv;

public:
    Fact(int n) : fact(n + 1), mInv(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++)
            fact[i] = 1LL * fact[i - 1] * i % MOD;
        mInv[n] = Math<MOD>::modInv(fact[n]);
        for (int i = n - 1; i >= 0; i--)
            mInv[i] = 1LL * mInv[i + 1] * (i + 1) % MOD;
    }

    int getFact(int n) { return fact[n]; }
    int getMInv(int n) { return mInv[n]; }

    int perm(int n) { return fact[n]; }
    int arra(int n, int k) { return 1LL * fact[n] * mInv[n - k] % MOD; }
    int comb(int n, int k) { return 1LL * fact[n] * mInv[k] % MOD * mInv[n - k] % MOD; }
    int cata(int n) { return 1LL * fact[2 * n] * mInv[n + 1] % MOD * mInv[n] % MOD; }
};
