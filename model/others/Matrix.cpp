#include<bits/stdc++.h>

using ll = long long;
const int mod = 1e9 + 7;
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

    std::vector<T>& operator[] (int x) {
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

    template <typename U>
    friend Matrix Mmul(const Matrix &x, const Matrix &y, U mod) {
        assert(x.m == y.n);
        Matrix tmp(x.n, y.m, 0);
        for (int i = 0; i < x.n; i++) {
            for (int j = 0; j < y.m; j++) {
                for (int k = 0; k < y.m; k++) {
                    tmp[i][j] += x.val[i][k] * y.val[k][j];
                    tmp[i][j] %= mod;
                }
            }
        }
        return tmp;
    }

    template<typename U>
    Matrix operator% (const U mod) const{
        auto tmp = val;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (tmp[i][j] < 0) {
                    tmp[i][j] += mod;
                } else if (tmp[i][j] >= mod) {
                    tmp[i][j] -= mod;
                }
            }
        }
        return {tmp};
    }

    template<typename U>
    Matrix operator%= (const U mod) {
         for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (val[i][j] < 0) {
                    val[i][j] += mod;
                } else if (val[i][j] >= mod) {
                    val[i][j] -= mod;
                }
            }
        }
        return *this;
    }

    Matrix operator+= (const Matrix &rhs) {
        *this = *this + rhs;
        return *this;
    }

    Matrix operator-= (const Matrix &rhs) {
        *this = *this - rhs;
        return *this;
    }

    Matrix operator*= (const Matrix &rhs) {
        *this = *this * rhs;
        return *this;
    }

    template<typename P>
    friend Matrix pow(Matrix a, P b) {
        assert(a.n == a.m);
        Matrix res(a.n, 1);
        for (;b; b >>= 1, a = a * a) {
            if (b & 1) {
                res = res * a;
            }
        }
        return res;
    }

    template<typename P, typename U>
    friend Matrix Mpow(Matrix a, P b, U mod) {
        assert(a.n == a.m);
        Matrix res(a.n, 1);
        for (;b; b >>= 1, a = Mmul(a, a, mod)) {
            if (b & 1) {
                res = Mmul(res, a, mod);
            }
        }
        return res;
    }

    int row() {
        return n;
    }
    int col() {
        return m;
    }
};


int main() {
    int n;
    ll k;
    std::cin >> n >> k;

    Matrix<ll> a(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    } 

    auto res = Mpow(a, k, mod);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << res[i][j] << " \n"[j == n - 1];
        }
    }
}