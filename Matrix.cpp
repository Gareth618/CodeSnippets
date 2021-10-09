#include <bits/stdc++.h>
using namespace std;

template<int N, int MOD = int(1e9 + 7)>
class Vector {
    int vec[N];

public:
    Vector() : vec() { }
    inline int& operator[](int pos) { return vec[pos]; }
};

template<int N, int MOD = int(1e9 + 7)>
class Matrix {
    int mat[N][N];

public:
    Matrix() : mat() { }
    inline int* operator[](int row) { return mat[row]; }

    static Matrix null() {
        Matrix<N, MOD> mat;
        for (int i = 0; i < N; i++)
            mat[i][i] = 1;
        return mat;
    }
};

template<int N, int MOD>
Vector<N, MOD> operator*(Matrix<N, MOD> a, Vector<N, MOD> b) {
    Vector<N, MOD> c;
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            c[i] = (c[i] + 1LL * a[i][k] * b[k]) % MOD;
    return c;
}

template<int N, int MOD>
Matrix<N, MOD> operator*(Matrix<N, MOD> a, Matrix<N, MOD> b) {
    Matrix<N, MOD> c;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % MOD;
    return c;
}

template<int N, int MOD>
Matrix<N, MOD> pwr(Matrix<N, MOD> a, int n) {
    if (!n)
        return Matrix<N, MOD>::null();
    if (n % 2)
        return a * pwr(a * a, n / 2);
    return pwr(a * a, n / 2);
}
