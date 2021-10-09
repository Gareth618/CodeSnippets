#include <bits/stdc++.h>
using namespace std;

class SparseTable {
    vector<vector<int>> dp;

public:
    SparseTable(const vector<int>& fun) :
        dp(log2(fun.size()) + 1, vector<int>(fun.size())) {
        dp[0] = fun;
        for (int i = 1; i < int(dp.size()); i++)
            for (int j = 0; j < int(fun.size()); j++)
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
    }

    int nthIteration(int x, int n) {
        for (int bit = 0; bit <= int(dp.size()); bit++)
            if (n & (1 << bit))
                x = dp[bit][x];
        return x;
    }

    int partition(int l, int r) {
        int ans = 1;
        for (int i = dp.size() - 1; i >= 0; i--)
            if (dp[i][l] <= r) {
                l = dp[i][l];
                ans += (1 << i);
            }
        return ans;
    }
};
//