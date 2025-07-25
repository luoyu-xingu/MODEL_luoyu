#include<bits/stdc++.h>

using ll = long long;

template<class T>
struct Point {
    T x = 0, y = 0;

    friend std::istream &operator>>(std::istream &in, Point &self) {
        in >> self.x >> self.y;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, Point self) {
        out << self.x << " " << self.y;
        return out;
    }

    friend bool operator< (const Point &x, const Point &y) {
        if (x.x != y.x) {
            return x.x < y.x;
        }
        return x.y < y.y;
    }

};

template<class T>
class Line {
    Point<T> a;

    public:

    Line() {}
    Line(const Point<T> &x) {
        a.x = x.x;
        a.y = x.y;
    }

    Line(const Point<T> &x, const Point<T> &y) {
        a.x = y.x - x.x;
        a.y = y.y - x.y;
    }

    Line(const Line &_a) {
        a = _a.a;
    }

    friend double abs(const Line & p) {
        return std::sqrt(1LL * p.a.x * p.a.x + 1LL * p.a.y * p.a.y);
    }

    template<class U>
    friend U cross(const Line<U> &x, const Line<U> &y) {
        return (x.a.x * y.a.y - 1LL * y.a.x * x.a.y);
    }

    template<class U>
    friend U dot(const Line<U> &x, const Line<U> &y) {
        return (1LL * x.a.x * y.a.x + 1LL * x.a.y * y.a.y);
    }
};

template<class T>
ll cross(Point<T> &a, Point<T> &b, Point<T> &c) {
    Line x(a, b);
    Line y(a, c);
    return cross(x, y);
}

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cout << std::fixed << std::setprecision(15);
    int t = 1;
//    std::cin >> t;

    while(t--) {
       solve();
    }

    return 0;
}

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<Point<double>> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    } 

    std::sort(a.begin(), a.end());

    std::vector<Point<double>> stk;

    for (int i = 0; i < n; i++) {
        while (stk.size() > 1 and cross(stk[stk.size() - 2], stk[stk.size() - 1], a[i]) <= 0) {
            stk.pop_back();
        }
        stk.push_back(a[i]);
    }

    int o = stk.size();

    for (int i = n - 2; i >= 0; i--) {
        while(stk.size() > o and cross(stk[stk.size() - 2], stk[stk.size() - 1], a[i]) <= 0) {
            stk.pop_back();
        }
        stk.push_back(a[i]);
    }

    double res = 0;
    for (int i = 0; i < stk.size() - 1; i++) {
        res += abs(Line<double>(stk[i], stk[i + 1]));
    }

    std::cout << res << '\n';
}