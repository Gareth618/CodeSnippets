# CodeSnippets

Hi! I am Gareth618 and I've been into competitive programming since ~2017, so I think I have a word to say in this domain. Therefore, I decided to create this repo to showcase THE best templates for competitive programming in the world. But this means to rewrite all of them, in order to follow the C++17 standards and just make them as flexible as possible. So I've started with `SegTree`. Just look how beautiful it works:

## Code for the _Dynamic Range Minimum Query_ problem

```cpp
int main() {
    int n; cin >> n;
    SegTree<int> st(n + 1, [](int x, int y) { return min(x, y); });

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1)
            st.update(x, y, [](int& x, int y) { x += y; });
        else
            cout << st.query(x, y) << '\n';
    }
    return 0;
}
```

## Code for the _Range Maximum-Sum Subsequence Query_ problem

```cpp
int main() {
    int n; cin >> n;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    vector<tuple<int, int, int, int>> init(n + 1);
    for (int i = 1; i <= n; i++)
        init[i] = make_tuple(v[i], v[i], v[i], v[i]);
    SegTree<tuple<int, int, int, int>> st(init, [](auto l, auto r) {
        auto [lSumAll, lMaxSum, lMaxLft, lMaxRgh] = l;
        auto [rSumAll, rMaxSum, rMaxLft, rMaxRgh] = r;
        return make_tuple(
            lSumAll + rSumAll,
            max({lMaxSum, lMaxRgh + rMaxLft, rMaxSum}),
            max(lMaxLft, lSumAll + rMaxLft),
            max(rMaxRgh, rSumAll + lMaxRgh)
        );
    });

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        cout << get<1>(st.query(x, y)) << '\n';
    }
    return 0;
}
```
