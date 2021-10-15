#include <bits/stdc++.h>
using namespace std;

class BigInt {
    int len;
    vector<int> num;

    static const int LOG = 4;
    static const int BASE = 10000;
    static const int LENGTH = 1000;

    inline int operator[](int pos) const {
        return pos < len ? num[pos] : 0;
    }

public:
    template<class T = int> BigInt(T val = 0);
    template<class T> explicit operator T();

    inline bool isZero() const { return len == 1 && !num[0]; }
    inline bool isOne() const { return len == 1 && num[0] == 1; }

    BigInt& operator++(); BigInt operator++(int);
    BigInt& operator--(); BigInt operator--(int);

    friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt& a, const BigInt& b);
    friend BigInt operator*(const BigInt& a, const BigInt& b);
    friend BigInt operator/(const BigInt& a, const BigInt& b);
    friend BigInt operator%(const BigInt& a, const BigInt& b);
    friend BigInt operator/(const BigInt& a, const    int& b);
    friend    int operator%(const BigInt& a, const    int& b);

    friend BigInt& operator+=(BigInt& a, const BigInt& b);
    friend BigInt& operator-=(BigInt& a, const BigInt& b);
    friend BigInt& operator*=(BigInt& a, const BigInt& b);
    friend BigInt& operator/=(BigInt& a, const BigInt& b);
    friend BigInt& operator%=(BigInt& a, const BigInt& b);
    friend BigInt& operator/=(BigInt& a, const    int& b);

    friend bool operator==(const BigInt& a, const BigInt& b);
    friend bool operator!=(const BigInt& a, const BigInt& b);
    friend bool operator< (const BigInt& a, const BigInt& b);
    friend bool operator> (const BigInt& a, const BigInt& b);
    friend bool operator<=(const BigInt& a, const BigInt& b);
    friend bool operator>=(const BigInt& a, const BigInt& b);

    friend istream& operator>>(istream& in, BigInt& x);
    friend ostream& operator<<(ostream& out, const BigInt& x);
};

template<class T>
BigInt::BigInt(T val) : len(0), num(LENGTH) {
    do {
        num[len++] = val % BASE;
        val /= BASE;
    } while (val);
}

template<class T>
BigInt::operator T() {
    T ret = 0;
    for (int i = len - 1; i >= 0; i--)
        ret = ret * BASE + num[i];
    return ret;
}

BigInt& BigInt::operator++() {
    int i;
    for (i = 0; i < len && num[i] == BASE - 1; i++)
        num[i] = 0;
    if (i < len)
        num[i]++;
    else
        num[len++] = 1;
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt ret = *this;
    int i;
    for (i = 0; i < len && num[i] == BASE - 1; i++)
        num[i] = 0;
    if (i < len)
        num[i]++;
    else
        num[len++] = 1;
    return ret;
}

BigInt& BigInt::operator--() {
    if (len == 1 && num[0] == 1) {
        num[0] = 0;
        return *this;
    }
    int i;
    for (i = 0; i < len && num[i] == 0; i++)
        num[i] = BASE - 1;
    if (i == len - 1 && num[i] == 1)
        len--;
    else
        num[i]--;
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt ret = *this;
    if (len == 1 && num[0] == 1) {
        num[0] = 0;
        return ret;
    }
    int i;
    for (i = 0; i < len && num[i] == 0; i++)
        num[i] = BASE - 1;
    if (i == len - 1 && num[i] == 1)
        len--;
    else
        num[i]--;
    return ret;
}

BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt sum;
    sum.len = max(a.len, b.len);
    int t = 0;
    for (int i = 0; i < sum.len; i++) {
        sum.num[i] = a[i] + b[i] + t;
        t = sum.num[i] / BigInt::BASE;
        sum.num[i] %= BigInt::BASE;
    }
    if (t)
        sum.num[sum.len++] = t;
    return sum;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt dif;
    dif.len = a.len;
    bool t = 0;
    for (int i = 0; i < dif.len; i++) {
        dif.num[i] = a[i] - b[i] - t;
        t = (dif.num[i] < 0);
        if (t)
            dif.num[i] += BigInt::BASE;
    }
    while (dif.len > 1 && !dif.num[dif.len - 1])
        dif.len--;
    return dif;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
    if (a.isZero() || b.isZero())
        return 0;
    BigInt prd;
    prd.len = a.len + b.len - 1;
    for (int i = 0; i < a.len; i++)
        for (int j = 0; j < b.len; j++)
            prd.num[i + j] += a[i] * b[j];
    int t = 0;
    for (int i = 0; i < prd.len; i++) {
        prd.num[i] += t;
        t = prd.num[i] / BigInt::BASE;
        prd.num[i] %= BigInt::BASE;
    }
    if (t)
        prd.num[prd.len++] = t;
    return prd;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
    BigInt qnt; qnt.len = a.len;
    BigInt rmd; rmd.len = 1;
    for (int i = a.len - 1; i >= 0; i--) {
        if (rmd) {
            for (int j = rmd.len; j >= 1; j--)
                rmd.num[j] = rmd.num[j - 1];
            rmd.len++;
        }
        rmd.num[0] = a[i];
        qnt.num[i] = 0;
        while (b <= rmd) {
            qnt.num[i]++;
            rmd -= b;
        }
    }
    while (qnt.len > 1 && !qnt.num[qnt.len - 1])
        qnt.len--;
    return qnt;
}

BigInt operator%(const BigInt& a, const BigInt& b) {
    BigInt rmd;
    rmd.len = 1;
    for (int i = a.len - 1; i >= 0; i--) {
        if (rmd) {
            for (int j = rmd.len; j >= 1; j--)
                rmd.num[j] = rmd.num[j - 1];
            rmd.len++;
        }
        rmd.num[0] = a[i];
        while (b <= rmd)
            rmd -= b;
    }
    return rmd;
}

BigInt operator/(const BigInt& a, const int& b) {
    BigInt qnt;
    qnt.len = a.len;
    int64_t rmd = 0;
    for (int i = a.len - 1; i >= 0; i--) {
        rmd = rmd * BigInt::BASE + a[i];
        qnt.num[i] = rmd / b;
        rmd %= b;
    }
    while (qnt.len > 1 && !qnt.num[qnt.len - 1])
        qnt.len--;
    return qnt;
}

int operator%(const BigInt& a, const int& b) {
    int64_t rmd = 0;
    for (int i = a.len - 1; i >= 0; i--) {
        rmd = rmd * BigInt::BASE + a[i];
        rmd %= b;
    }
    return rmd;
}

BigInt& operator+=(BigInt& a, const BigInt& b) {
    if (b.len > a.len)
        a.len = b.len;
    int t = 0;
    for (int i = 0; i < a.len; i++) {
        a.num[i] = a[i] + b[i] + t;
        t = a.num[i] / BigInt::BASE;
        a.num[i] %= BigInt::BASE;
    }
    if (t)
        a.num[a.len++] = t;
    return a;
}

BigInt& operator-=(BigInt& a, const BigInt& b) {
    bool t = 0;
    for (int i = 0; i < a.len; i++) {
        a.num[i] = a[i] - b[i] - t;
        t = (a.num[i] < 0);
        if (t)
            a.num[i] += BigInt::BASE;
    }
    while (a.len > 1 && !a.num[a.len - 1])
        a.len--;
    return a;
}

BigInt& operator*=(BigInt& a, const BigInt& b) { a = a * b; return a; }
BigInt& operator/=(BigInt& a, const BigInt& b) { a = a / b; return a; }
BigInt& operator%=(BigInt& a, const BigInt& b) { a = a % b; return a; }

BigInt& operator/=(BigInt& a, const int& b) {
    int64_t rmd = 0;
    for (int i = a.len - 1; i >= 0; i--) {
        rmd = rmd * BigInt::BASE + a[i];
        a.num[i] = rmd / b;
        rmd %= b;
    }
    while (a.len > 1 && !a.num[a.len - 1])
        a.len--;
    return a;
}

bool operator==(const BigInt& a, const BigInt& b) {
    if (a.len != b.len)
        return false;
    for (int i = 0; i < a.len; i++)
        if (a.num[i] != b.num[i])
            return false;
    return true;
}

bool operator!=(const BigInt& a, const BigInt& b) {
    if (a.len != b.len)
        return true;
    for (int i = 0; i < a.len; i++)
        if (a.num[i] != b.num[i])
            return true;
    return false;
}

bool operator<(const BigInt& a, const BigInt& b) {
    if (a.len < b.len) return true;
    if (a.len > b.len) return false;
    for (int i = a.len - 1; i >= 0; i--) {
        if (a.num[i] < b.num[i])
            return true;
        if (a.num[i] > b.num[i])
            return false;
    }
    return false;
}

bool operator>(const BigInt& a, const BigInt& b) {
    if (a.len > b.len) return true;
    if (a.len < b.len) return false;
    for (int i = a.len - 1; i >= 0; i--) {
        if (a.num[i] > b.num[i])
            return true;
        if (a.num[i] < b.num[i])
            return false;
    }
    return false;
}

bool operator<=(const BigInt& a, const BigInt& b) {
    if (a.len < b.len) return true;
    if (a.len > b.len) return false;
    for (int i = a.len - 1; i >= 0; i--) {
        if (a.num[i] < b.num[i])
            return true;
        if (a.num[i] > b.num[i])
            return false;
    }
    return true;
}

bool operator>=(const BigInt& a, const BigInt& b) {
    if (a.len > b.len) return true;
    if (a.len < b.len) return false;
    for (int i = a.len - 1; i >= 0; i--) {
        if (a.num[i] > b.num[i])
            return true;
        if (a.num[i] < b.num[i])
            return false;
    }
    return true;
}

istream& operator>>(istream& in, BigInt& x) {
    string str; in >> str;
    x.len = 0;
    for (int i = str.size() - 1; i >= 0; i -= BigInt::LOG) {
        x.num[x.len] = 0;
        for (int j = max(0, i - BigInt::LOG + 1); j <= i; j++)
            x.num[x.len] = x.num[x.len] * 10 + str[j] - '0';
        x.len++;
    }
    return in;
}

ostream& operator<<(ostream& out, const BigInt& x) {
    out << x.num[x.len - 1];
    for (int i = x.len - 2; i >= 0; i--) {
        for (int j = 10; j < BigInt::BASE; j *= 10)
            if (x.num[i] < j)
                out << 0;
        out << x.num[i];
    }
    return out;
}
