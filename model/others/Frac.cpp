#include<bits/stdc++.h>

using ll = long long;

template<class T> 
class Frac {
    T f, g;
    void _to(T x, T y) {
        T gcd = std::gcd(std::abs(x), std::abs(y));
        if (y < 0) {
            y = -y;
            x = -x;
        }
        f = x / gcd, g = y / gcd;
    }

    public:

    Frac() {
        f = 0, g = 1;
    }

    Frac(T _f, T _g) {
        _to(_f, _g);
    }

    Frac(T _num) : Frac(_num, 1) {}
    
    Frac(const Frac &rhs) {
        f = rhs.f;
        g = rhs.g;
    }

    explicit operator double() const {
        return 1.0 * f / g;
    }
    Frac operator-() {
        return {-f, g};
    }

    Frac &operator+=(const Frac &rhs) {
        f = f * rhs.g + rhs.f * g;
        g *= rhs.g;
        _to(f, g);
        return *this;
    }

    Frac &operator-=(const Frac &rhs) {
        f = f * rhs.g - rhs.f * g;
        g *= rhs.g;
        _to(f, g);
        return *this;
    }

    Frac &operator*=(const Frac &rhs) {
        f *= rhs.f;
        g *= rhs.g;
        _to(f, g);
        return *this;
    }

    Frac &operator/=(const Frac &rhs) {
        f *= rhs.g;
        g *= rhs.f;
        _to(f, g);
        return *this;
    }

    friend Frac operator+(Frac lhs, const Frac &rhs) {
        return lhs += rhs;
    }
    friend Frac operator-(Frac lhs, const Frac &rhs) {
        return lhs -= rhs;
    }
    friend Frac operator*(Frac lhs, const Frac &rhs) {
        return lhs *= rhs;
    }
    friend Frac operator/(Frac lhs, const Frac &rhs) {
        return lhs /= rhs;
    }

    friend bool operator==(const Frac &lhs, const Frac &rhs) {
        return lhs.f * rhs.g == rhs.f * lhs.g;
    }
    friend bool operator!=(const Frac &lhs, const Frac &rhs) {
        return lhs.f * rhs.g != rhs.f * lhs.g;
    }
    friend bool operator<(const Frac &lhs, const Frac &rhs) {
        return lhs.f * rhs.g < rhs.f * lhs.g;
    }
    friend bool operator>(const Frac &lhs, const Frac &rhs) {
        return lhs.f * rhs.g > rhs.f * lhs.g;
    }
    friend bool operator<=(const Frac &lhs, const Frac &rhs) {
        return lhs.f * rhs.g <= rhs.f * lhs.g;
    }
    friend bool operator>=(const Frac &lhs, const Frac &rhs) {
        return lhs.f * rhs.g >= rhs.f * lhs.g;
    }

    friend std::ostream &operator<<(std::ostream &os, Frac x) {
        if (x.g == 1) {
            return os << x.f;
        } else {
            return os << x.f << "/" << x.g;
        }
    }

    std::pair<T, T> val() {
        return {f, g};
    }
};


int main() {
    return 0;
}