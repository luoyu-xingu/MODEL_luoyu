#include<bits/stdc++.h>

using ll = long long;

class Point {
    public:
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point &rhs) {
        x = rhs.x;
        y = rhs.y;
    }

    friend bool operator== (const Point &self, const Point &rhs) {
        return self.x == rhs.x and self.y == rhs.y;
    }

    friend std::ostream &operator<< (std::ostream &out, const Point &self) {
        out << self.x << " " << self.y;
        return out;
    }

    friend std::istream &operator>> (std::istream &in, Point &self) {
        in >> self.x >> self.y;
        return in;
    }

    friend std::strong_ordering operator<=> (const Point &self, const Point &rhs) {
        return std::tie(self.x, self.y) <=> std::tie(rhs.x, rhs.y);
    }

    Point operator+ (const Point &rhs) const {
        return {x + rhs.x, y + rhs.y};
    }

    Point operator- (const Point &rhs) const {
        return {x - rhs.x, y - rhs.y};
    }

    Point operator* (int k) const {
        return {x * k, y * k};
    }

    

    Point &operator+= (const Point &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Point &operator-= (const Point &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Point &operator*= (int k) {
        x *= k;
        y *= k;
        return *this;
    }

    Point &operator/= (int k) {
        x /= k;
        y /= k;
        return *this;
    }
};

class Line {
    // 两点定线
    Point a, b;
    public:
    Line() {}
    Line(const Point &x, const Point &y) {
        if (x == y) {
            std::cout << "Same Point!" << "\n";
            assert(false);
        }
        a = x;
        b = y;
    }
    Line(const Line &rhs) {
        a = rhs.a;
        b = rhs.b;
    }

    bool isline(const Point &c) {
        return 1LL * (b.y - a.y) * (c.x - a.x) == 1LL * (c.y - a.y) * (b.x - a.x);
    }
};

int main() {
    return 0;
}