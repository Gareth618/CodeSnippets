#include <bits/stdc++.h>
using namespace std;

vector<int> getPi(const string& str) {
    vector<int> pi(str.size());
    int k = 0;
    for (int i = 1; i < int(str.size()); i++) {
        while (k && str[i] != str[k])
            k = pi[k - 1];
        if (str[i] == str[k])
            k++;
        pi[i] = k;
    }
    return pi;
}

vector<int> kmp(const string& str, const string& pat) {
    string concat = pat + '#' + str;
    auto pi = getPi(concat);
    vector<int> occ;
    for (int i = pat.size() + 1; i < int(concat.size()); i++)
        if (pi[i] == int(pat.size()))
            occ.push_back(i - 2 * int(pat.size()));
    return occ;
}

pair<vector<int>, vector<int>> manacher(const string& str) {
    auto fun = [&](int x) {
        vector<int> len(str.size());
        for (int i = 0, l = 0, r = -1; i < int(str.size()); i++) {
            int k = i > r ? 1 - x : min(len[l + r - i + x], r - i + 1);
            while (0 <= i - k - x && i + k < int(str.size()) && str[i - k - x] == str[i + k])
                k++;
            len[i] = k--;
            if (i + k > r) {
                l = i - k - x;
                r = i + k;
            }
        }
        return len;
    };
    return make_pair(fun(0), fun(1));
}
