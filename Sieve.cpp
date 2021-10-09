#include <bits/stdc++.h>
using namespace std;

class Sieve {
    vector<bool> sieve;
    vector<int> primes;

public:
    Sieve(int n) : sieve(n + 1) {
        sieve[0] = sieve[1] = true;
        for (int j = 4; j <= n; j += 2)
            sieve[j] = true;
        for (int i = 3; i * i <= n; i += 2)
            if (!sieve[i])
                for (int j = i * i; j <= n; j += 2 * i)
                    sieve[j] = true;
        primes.push_back(2);
        for (int i = 3; i <= n; i += 2)
            if (!sieve[i])
                primes.push_back(i);
    }

    auto begin() { return primes.begin(); }
    auto end() { return primes.end(); }

    template<class T>
    bool prime(T n) {
        if (n < int(sieve.size()))
            return !sieve[n];
        for (int d : primes) {
            if (1LL * d * d > n)
                break;
            if (n % d == 0)
                return false;
        }
        return true;
    }

    template<class T>
    vector<pair<T, int>> getDiv(T n) {
        vector<pair<T, int>> div;
        auto divide = [&](int d) {
            if (n % d)
                return;
            div.emplace_back(d, 0);
            while (n % d == 0) {
                div.back().second++;
                n /= d;
            }
        };
        for (int d : primes) {
            if (1LL * d * d > n)
                break;
            divide(d);
        }
        if (n > 1)
            div.emplace_back(n, 1);
        return div;
    }
};
//