#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
    struct Node {
        int ends, link, next[26];
        int fath, code, tran[26];
        Node(int fath, int code) :
            ends(0), link(-1), fath(fath), code(code) {
                fill(begin(next), end(next), -1);
                fill(begin(tran), end(tran), -1);
            }
    };
    vector<int> where;
    vector<Node> trie{1, Node(-1, -1)};

    int getLink(int node) {
        if (trie[node].link == -1)
            trie[node].link
                = !node || !trie[node].fath
                ? 0
                : getTran(getLink(trie[node].fath), trie[node].code);
        return trie[node].link;
    }

    int getTran(int node, int code) {
        if (trie[node].tran[code] == -1)
            trie[node].tran[code]
                = trie[node].next[code] != -1
                ? trie[node].next[code]
                : node
                    ? getTran(getLink(node), code)
                    : 0;
        return trie[node].tran[code];
    }

public:
    void insert(const string& str) {
        int node = 0;
        for (char chr : str) {
            const int code = chr - 'a';
            if (trie[node].next[code] == -1) {
                trie[node].next[code] = trie.size();
                trie.emplace_back(node, code);
            }
            node = trie[node].next[code];
        }
        where.push_back(node);
    }

    void build() {
        for (int node = 0; node < int(trie.size()); node++) {
            getLink(node);
            for (int code = 0; code < 26; code++)
                getTran(node, code);
        }
    }

    vector<int> solve(const string& str) {
        int node = 0;
        for (char chr : str) {
            node = trie[node].tran[chr - 'a'];
            trie[node].ends++;
        }
        vector<int> order(1, 0);
        for (int i = 0; i < int(order.size()); i++) {
            const int node = order[i];
            for (int code = 0; code < 26; code++)
                if (trie[node].next[code] != -1)
                    order.push_back(trie[node].next[code]);
        }
        reverse(order.begin(), order.end());
        for (int node : order)
            trie[trie[node].link].ends += trie[node].ends;
        vector<int> ans(where.size());
        for (int i = 0; i < int(where.size()); i++)
            ans[i] = trie[where[i]].ends;
        return ans;
    }
};
