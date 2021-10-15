#include <bits/stdc++.h>
using namespace std;

class InParser {
    vector<char> str;
    int ptr;
    istream *fin;

    char getChar() {
        if (ptr == int(str.size())) {
            fin->read(str.data(), str.size());
            ptr = 0;
        }
        return str[ptr++];
    }

    template<class T>
    T getInt() {
        char chr = getChar();
        while (!isdigit(chr) && chr != '-')
            chr = getChar();
        int sgn = +1;
        if (chr == '-') {
            sgn = -1;
            chr = getChar();
        }
        T num = 0;
        while (isdigit(chr)) {
            num = num * 10 + chr - '0';
            chr = getChar();
        }
        return sgn * num;
    }

public:
    InParser() : str(1e5), ptr(str.size()), fin(&cin) { }
    InParser(const char* name) : str(1e5), ptr(str.size()), fin(&(*(new ifstream(name)))) { }

    template<class T>
    friend InParser& operator>>(InParser& in, T& num) {
        num = in.getInt<T>();
        return in;
    }
};

class OutParser {
    vector<char> str;
    int ptr;
    ostream *fout;

    void putChar(char chr) {
        if (ptr == int(str.size())) {
            fout->write(str.data(), str.size());
            ptr = 0;
        }
        str[ptr++] = chr;
    }

    template<class T>
    void putInt(T num) {
        if (num < 0) {
            putChar('-');
            num *= -1;
        }
        if (num > 9)
            putInt(num / 10);
        putChar(num % 10 + '0');
    }

public:
    OutParser() : str(1e5), ptr(0), fout(&cout) { }
    OutParser(const char* name) : str(1e5), ptr(0), fout(&(*(new ofstream(name)))) { }
    ~OutParser() { fout->write(str.data(), ptr); }

    template<class T>
    friend OutParser& operator<<(OutParser& out, const T num) {
        out.putInt(num);
        return out;
    }

    friend OutParser& operator<<(OutParser& out, const char chr) {
        out.putChar(chr);
        return out;
    }

    friend OutParser& operator<<(OutParser& out, const char* str) {
        for (int i = 0; str[i]; i++)
            out.putChar(str[i]);
        return out;
    }
};
