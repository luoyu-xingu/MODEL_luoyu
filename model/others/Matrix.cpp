#include<bits/stdc++.h>

using ll = long long;

template <typename T>
class Matrix {
    int n, m;
    std::vector<std::vector<T>> val;

    public:

    Matrix(int _n = 1, T x = 0) : n(_n), m(_n) {

        val.assign(n, std::vector<T>(m, T()));
        for (int i = 0; i < n; i++) {
            val[i][i] = x;
        }

    }

    Matrix(int _n, int _m, T x) : n(_n), m(_m) {
        val.assign(n, std::vector<T>(m, x));
    }

    template <typename P>
    Matrix(const std::vector<std::vector<P>> &v) : n(v.size()), m(v[0].size()) {
        val.assign(n, std::vector<T>(m, T()));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                val[i][j] = v[i][j];
            }
        }
    }

    std::vector<T> &operator[] (int x) {
        assert(x < n);
        return val[x];
    }
    Matrix operator+ (const Matrix &rhs) const {
        assert(n == rhs.n and m == rhs.m);
        Matrix tmp(n, m, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tmp[i][j] = val[i][j] + rhs.val[i][j]; 
            }
        }
        return tmp;
    }

    Matrix operator- () {
        auto tmp = val;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tmp[i][j] = -tmp[i][j];
            }
        }
        return {tmp};
    }

    Matrix operator- (const Matrix &rhs) const{
        assert(n == rhs.n and m == rhs.m);
        Matrix tmp(n, m, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tmp[i][j] = val[i][j] - rhs.val[i][j]; 
            }
        }
        return tmp;
    }

    Matrix operator* (const Matrix &rhs) const {
        assert(m == rhs.n);

        Matrix tmp(n, rhs.m, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < rhs.m; j++) {
                for (int k = 0; k < m; k++) {
                    tmp[i][j] += val[i][k] * rhs.val[k][j];
                }
            }
        }
        return tmp;
    }


    Matrix &operator+= (const Matrix &rhs) {
        *this = *this + rhs;
        return *this;
    }

    Matrix &operator-= (const Matrix &rhs) {
        *this = *this - rhs;
        return *this;
    }

    Matrix &operator*= (const Matrix &rhs) {
        *this = *this * rhs;
        return *this;
    }

    friend std::istream &operator<< (std::istream &in, Matrix &self) {
        for (int i = 0; i < self.n; i++) {
            for (int j = 0; j < self.m; j++) {
                in >> self.val[i][j];
            }
        }
        return in;
    }

    friend std::ostream &operator>> (std::ostream &out, Matrix self) {
        for (int i = 0; i < self.n; i++) {
            for (int j = 0; j < self.m; j++) {
                out << self.val[i][j] << " \n"[j == self.m - 1];
            }
        }
        return out;
    }


    int row() {
        return n;
    }
    int col() {
        return m;
    }
};