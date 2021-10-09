#include <bits/stdc++.h>
using namespace std;

template<class T>
class RMQ {
    vector<vector<T>> dp;
    function<T(T, T)> fun;

public:
    RMQ(const vector<T>& v, function<T(T, T)> fun = [](T x, T y) { return min(x, y); }) :
        dp(log2(v.size()) + 1, vector<T>(v.size())), fun(fun) {
            dp[0] = v;
            for (int i = 1; i < int(dp.size()); i++)
                for (int j = 0; j + (1 << i) <= int(v.size()); j++)
                    dp[i][j] = fun(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
        }

    T query(int l, int r) {
        const int k = log2(r - l + 1);
        return fun(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
};

template<class T>
class RMQ2D {
    vector<vector<vector<vector<T>>>> dp;
    function<T(T, T)> fun;

public:
    RMQ2D(const vector<vector<T>>& mat, function<T(T, T)> fun = [](T x, T y) { return min(x, y); }) :
        dp(log2(mat.size()) + 1, vector(log2(mat.back().size()) + 1, vector(mat.size(), vector<T>(mat.back().size())))), fun(fun) {
            dp[0][0] = mat;
            for (int iLog = 0; iLog < int(dp.size()); iLog++)
                for (int jLog = 0; jLog < int(dp.back().size()); jLog++)
                    for (int i = 0; i + (1 << iLog) <= int(mat.size()); i++)
                        for (int j = 0; j + (1 << jLog) <= int(mat.back().size()); j++) {
                            const int iPwr = (1 << (iLog - 1));
                            const int jPwr = (1 << (jLog - 1));
                            if (iLog) dp[iLog][jLog][i][j] = fun(dp[iLog - 1][jLog][i][j], dp[iLog - 1][jLog][i + iPwr][j]);
                            if (jLog) dp[iLog][jLog][i][j] = fun(dp[iLog][jLog - 1][i][j], dp[iLog][jLog - 1][i][j + jPwr]);
                        }
        }

    T query(int i, int j, int iLen, int jLen) {
        const int iLog = log2(iLen), iPwr = (1 << iLog);
        const int jLog = log2(jLen), jPwr = (1 << jLog);
        return fun(
            fun(dp[iLog][jLog][i][j], dp[iLog][jLog][i + iLen - iPwr][j]),
            fun(dp[iLog][jLog][i][j + jLen - jPwr], dp[iLog][jLog][i + iLen - iPwr][j + jLen - jPwr])
        );
    }
};

template<class T>
class RMQ2Dsqr {
    vector<vector<vector<T>>> dp;
    function<T(T, T)> fun;

public:
    RMQ2Dsqr(const vector<vector<T>>& mat, function<T(T, T)> fun = [](T x, T y) { return min(x, y); }) :
        dp(log2(max(mat.size(), mat.back().size())) + 1, vector(mat.size(), vector<T>(mat.back().size()))), fun(fun) {
            dp[0] = mat;
            for (int log = 1; log < int(dp.size()); log++)
                for (int i = 0; i + (1 << log) <= int(mat.size()); i++)
                    for (int j = 0; j + (1 << log) <= int(mat.back().size()); j++) {
                        const int pwr = (1 << (log - 1));
                        dp[log][i][j] = fun(
                            fun(dp[log - 1][i][j], dp[log - 1][i + pwr][j]),
                            fun(dp[log - 1][i][j + pwr], dp[log - 1][i + pwr][j + pwr])
                        );
                    }
        }

    T query(int i, int j, int len) {
        const int log = log2(len), pwr = (1 << log);
        return fun(
            fun(dp[log][i][j], dp[log][i + len - pwr][j]),
            fun(dp[log][i][j + len - pwr], dp[log][i + len - pwr][j + len - pwr])
        );
    }
};
//