#include <bits/stdc++.h>
using namespace std;

template<class T>
bool prime(T n) {
    if (n < 2)
        return false;
    for (T d = 2; d * d <= n; d++)
        if (n % d == 0)
            return false;
    return true;
}

template<class T>
vector<pair<T, int>> getDiv(T n) {
    vector<pair<T, int>> div;
    for (T d = 2; d * d <= n; d++)
        if (n % d == 0) {
            div.emplace_back(d, 0);
            while (n % d == 0) {
                div.back().second++;
                n /= d;
            }
        }
    if (n > 1)
        div.emplace_back(n, 1);
    return div;
}

template<class T>
vector<T> getAllDiv(T n) {
    vector<T> l, r;
    for (T d = 1; d * d <= n; d++)
        if (n % d == 0) {
            l.push_back(d);
            if (d != n / d)
                r.push_back(n / d);
        }
    for (int i = int(r.size()) - 1; i >= 0; i--)
        l.push_back(r[i]);
    return l;
}

vector<vector<int>> getDivUpTo(int n) {
    vector<vector<int>> div(n + 1);
    for (int i = 2; i <= n; i++)
        if (div[i].empty())
            for (int j = i; j <= n; j += i)
                div[j].push_back(i);
    return div;
}

vector<vector<int>> getAllDivUpTo(int n) {
    vector<vector<int>> div(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            div[i].push_back(j);
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

vector<int> phiUpTo(int n) {
    vector<int> phi(n + 1);
    for (int i = 1; i <= n; i++)
        phi[i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
            phi[j] -= phi[i];
    return phi;
}
