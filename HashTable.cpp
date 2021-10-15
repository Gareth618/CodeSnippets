#include <bits/stdc++.h>
using namespace std;

template<class K, class V, int MOD = 666013>
class HashTable {
    function<int(K)> hash;
    vector<vector<pair<K, V>>> table;

public:
    HashTable(function<int(K)> hash = [](K key) {
        return abs(key) % MOD;
    }) : hash(hash), table(MOD) { }

    V& operator[](K key) {
        const int h = hash(key);
        for (auto& [itKey, itVal] : table[h])
            if (itKey == key)
                return itVal;
        table[h].emplace_back(key, 0);
        return table[h].back().second;
    }

    void erase(K key) {
        const int h = hash(key);
        for (auto& [itKey, itVal] : table[h])
            if (itKey == key) {
                tie(itKey, itVal) = table[h].back();
                table[h].pop_back();
                return;
            }
    }

    int count(K key) {
        const int h = hash(key);
        for (auto [itKey, itVal] : table[h])
            if (itKey == key)
                return 1;
        return 0;
    }
};
