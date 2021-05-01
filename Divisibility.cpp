#include <bits/stdc++.h>
using namespace std;

template<class T>
bool prime(T n) {
    if (n == 1)
        return false;
    if (n % 2 == 0)
        return n == 2;
    for (T d = 3; d * d <= n; d += 2)
        if (n % d == 0)
            return false;
    return true;
}

template<class T>
vector<pair<T, int>> getDiv(T n) {
    vector<pair<T, int>> div;
    auto divide = [&](T d) {
        if (n % d)
            return;
        div.emplace_back(d, 0);
        while (n % d == 0) {
            div.back().second++;
            n /= d;
        }
    };
    divide(2);
    for (T d = 3; d * d <= n; d += 2)
        divide(d);
    if (n > 1)
        div.emplace_back(n, 1);
    return div;
}

template<class T>
int divNum(const vector<pair<T, int>>& div) {
    int ans = 1;
    for (auto [p, e] : div)
        ans *= e + 1;
    return ans;
}

template<class T>
T divSum(const vector<pair<T, int>>& div) {
    T ans = 1;
    for (auto [p, e] : div) {
        T pwr = p;
        for (int i = 0; i < e; i++)
            pwr *= p;
        ans *= (pwr - 1) / (p - 1);
    }
    return ans;
}

template<class T>
T phi(const vector<pair<T, int>>& div) {
    T ans = 1;
    for (auto [p, e] : div) {
        ans *= p - 1;
        for (int i = 1; i < e; i++)
            ans *= p;
    }
    return ans;
}

vector<int> phiUpToN(int n) {
    vector<int> phi(n + 1);
    for (int i = 1; i <= n; i++)
        phi[i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
            phi[j] -= phi[i];
    return phi;
}
