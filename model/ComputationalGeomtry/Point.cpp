#include<bits/stdc++.h>

using ll = long long;

template <class T>
class Point {
    T x, y;

    public:
    Point() {
        x = y = 0;
    }

    template <class U>
    Point(U x, U y) : x(x), y(y){}

    template<class U>
    Point(const Point<U> &rhs) {
        x = rhs.x;
        y = rhs.y;
    }

    template<class U> 
    Point &operator=(const Point<U> &rhs) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    Point operator-() const {
        auto [a, b] = {-x, -y};
        return {x, y};
    }

    Point &operator-=(const Point &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    friend Point &operator-(Point lhs, const Point &rhs) {
        lhs -= rhs;
        return lhs;
    }

    Point &operator+=(const Point &rhs) {
        return {x + rhs.x, y + rhs.y};
    }

    friend Point operator+(Point lhs, const Point &rhs) {
        lhs += rhs;
        return lhs;
    }

    bool operator== (const Point &rhs) {
        return x == rhs.x and y == rhs.y;
    }

    bool operator<(const Point &rhs) {
        if (x != rhs.x) {
            return x < rhs.x;
        }
        return y < rhs.y;
    }

    friend std::istream &operator>>(std::istream &in, Point &self) {
        in >> self.x >> self.y;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Point &self) {
        out << self.x << " " << self.y;
        return out;
    }

    friend ll abs(const Point a) {
        return 1LL * a.x * a.x + 1LL * a.y * a.y;
    }

    friend double sqrt(const Point a) {
        return std::sqrt(abs(a));
    }

    friend ll cross(const Point &lhs, const Point &rhs) {
        return 1LL * lhs.x * rhs.y - 1LL * lhs.y * rhs.x;
    }

    friend ll dot(const Point &lhs, const Point &rhs) {
        return 1LL * lhs.x * rhs.x + 1LL * lhs.y * rhs.y;
    }
    
    friend double ang(const Point &a) {
        return atan2(a.y, a.x);
    }
};