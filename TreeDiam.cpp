#include <bits/stdc++.h>
using namespace std;

vector<int> getDiam(const vector<vector<int>>& tree) {
    function<pair<int, int>(int, int, int)> dfs1 = [&](int node, int fath, int dpth) {
        pair<int, int> bst(dpth, node);
        for (int nghb : tree[node])
            if (nghb != fath)
                bst = max(bst, dfs1(nghb, node, dpth + 1));
        return bst;
    };

    vector<int> father(tree.size());
    function<pair<int, int>(int, int, int)> dfs2 = [&](int node, int fath, int dpth) {
        pair<int, int> bst(dpth, node);
        for (int nghb : tree[node])
            if (nghb != fath) {
                father[nghb] = node;
                bst = max(bst, dfs2(nghb, node, dpth + 1));
            }
        return bst;
    };

    vector<int> diam;
    function<void(int)> ascend = [&](int node) {
        if (!node)
            return;
        diam.push_back(node);
        ascend(father[node]);
    };
    ascend(dfs2(dfs1(1, 0, 0).second, 0, 0).second);
    return diam;
}

template<class T>
vector<pair<int, T>> getDiam(const vector<vector<pair<int, T>>>& tree) {
    function<pair<T, int>(int, int, T)> dfs1 = [&](int node, int fath, T dist) {
        pair<T, int> bst(dist, node);
        for (auto [nghb, cost] : tree[node])
            if (nghb != fath)
                bst = max(bst, dfs1(nghb, node, dist + cost));
        return bst;
    };

    vector<pair<int, T>> father(tree.size());
    function<pair<T, int>(int, int, T)> dfs2 = [&](int node, int fath, T dist) {
        pair<T, int> bst(dist, node);
        for (auto [nghb, cost] : tree[node])
            if (nghb != fath) {
                father[nghb] = make_pair(node, cost);
                bst = max(bst, dfs2(nghb, node, dist + cost));
            }
        return bst;
    };

    vector<pair<int, T>> diam;
    function<void(int)> ascend = [&](int node) {
        if (!node)
            return;
        auto [fath, cost] = father[node];
        diam.emplace_back(node, cost);
        ascend(fath);
    };
    ascend(dfs2(dfs1(1, 0, 0).second, 0, 0).second);
    return diam;
}
//