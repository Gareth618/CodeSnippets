#include <bits/stdc++.h>
using namespace std;

template<int MOD = int(1e9 + 7)>
struct Vector {
    int n;
    vector<int> vec;

    Vector(int n) : n(n), vec(n) { }
    int& operator[](int pos) { return vec[pos]; }
};

template<int MOD = int(1e9 + 7)>
struct Matrix {
    int n;
    vector<vector<int>> mat;

    Matrix(int n) : n(n), mat(n, vector<int>(n)) { }
    vector<int>& operator[](int row) { return mat[row]; }

    static Matrix null(int n) {
        Matrix<MOD> mat(n);
        for (int i = 0; i < n; i++)
            mat[i][i] = 1;
        return mat;
    }
};

template<int MOD>
Vector<MOD> operator*(Matrix<MOD> a, Vector<MOD> b) {
    if (a.n != b.n) throw exception();
    const int n = a.n;
    Vector<MOD> c;
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            c[i] = (c[i] + 1LL * a[i][k] * b[k]) % MOD;
    return c;
}

template<int MOD>
Matrix<MOD> operator*(Matrix<MOD> a, Matrix<MOD> b) {
    if (a.n != b.n) throw exception();
    const int n = a.n;
    Matrix<MOD> c(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % MOD;
    return c;
}

template<int MOD>
Matrix<MOD> pwr(Matrix<MOD> a, int n) {
    if (!n)
        return Matrix<MOD>::null(a.n);
    if (n % 2)
        return a * pwr(a * a, n / 2);
    return pwr(a * a, n / 2);
}
