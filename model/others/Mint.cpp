#include<bits/stdc++.h>

using ll = long long;

constexpr int MAXV = 1e5 + 3;

template <class T, class U>
T qpow(T a, U b) {
    T res = 1;
    for (; b != 0; b /= 2, a *= a) {
        if (b % 2 == 1) {
            res *= a;
        }
    }
    return res;
}


class Mint {
    int x;
    static int mod;

    template<class T>
    static int _to(T _x) {
        _x %= mod;

        if (_x < 0) {
            _x += mod;
        }
        
        return _x;
    }

    friend ll invGcd(ll _x, ll y);
    Mint inv() const {
        return qpow(*this, mod - 2);
    }

    public:
    Mint() : x(0) {}

    template<class T>
    Mint(T _x) : x(_to(_x)) {}

    Mint(const Mint &rhs) {
        x = rhs.x;
    }

    static int Mod() {
        return mod;
    }

    int val() {
        return x;
    }

    template<class T>
    Mint operator= (T _x) {
        x = to(_x);
    }

    Mint operator- () const {
        Mint res;
        if (x == 0) {
            res.x = 0;
        } else {
            res.x = (ll)mod - x;
        }
        return res;
    }

    Mint &operator-= (const Mint &rhs) {
        x = _to(1LL * x - rhs.x);
        return *this;
    }
    friend Mint operator- (Mint lhs, const Mint &rhs) {
        lhs -= rhs;
        return lhs;
    }

    Mint &operator*= (const Mint &rhs) {
        x = _to(1LL * x * rhs.x);
        return *this; 
    }

    friend Mint operator* (Mint lhs, const Mint &rhs) {
        lhs *= rhs;
        return lhs;
    }

    Mint &operator+= (const Mint &rhs) {
        x = _to(1LL * x + rhs.x);
        return *this;
    }

    friend Mint operator+ (Mint lhs, const Mint &rhs) {
        lhs += rhs;
        return lhs;
    }


    Mint &operator/= (const Mint &rhs) {
        x = _to(1LL * x * rhs.inv().x);
        return *this;
    }

    friend Mint operator/ (Mint lhs, const Mint &rhs) {
        lhs /= rhs;
        return lhs;
    }
    
    friend std::istream &operator>>(std::istream &is, Mint &self) {
        ll _x;
        is >> _x;
        self.x = _x;
        return is;
    }

    friend std::ostream &operator<<(std::ostream &out, Mint self) {
        out << self.x;
        return out;
    }

    friend bool operator== (const Mint &lhs, const Mint &rhs) {
        return lhs.x == rhs.x;
    }

    friend std::strong_ordering operator<=> (const Mint &lhs, const Mint &rhs) {
        return lhs.x <=> rhs.x;
    }
};

ll invGcd(ll _x, ll y) {
    //  ax === 1 (mod y);
    _x = Mint::_to(_x);
    assert(_x != 0);
        
    ll s = y, t = _x;
    ll m0 = 0, m1 = 1;
 
    while (t) {
        ll u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        
        std::swap(s, t);
        std::swap(m0, m1);
    }
    
    if (m0 < 0) {
        m0 += y / s;
    }

    return m0;
} 

int Mint::mod = 998244353;
//int Mint::mod = 1e9 + 7;
using Z = Mint;

class Comb {
    int n;
    std::vector<Z> fact;
    std::vector<Z> inv;

    void init(int _n) {
        n = _n;
        assert(_n <= 1e6 and _n >= 0);
        fact.assign(n + 1, 1);
        inv.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }

        inv[n] = 1 / fact[n];
        for (int i = n - 1 ; i >= 1;i--) {
            inv[i] = inv[i + 1] * (i + 1);
        }
    }

    public:
    Comb() {}

    Comb(int _Max) {
        init(_Max);
    }

    Z A(int m, int k) {
        assert(m <= n and k <= n);
        return fact[m] / fact[m - k];
    }

    Z C(int m, int k) {
        assert(m <= n);
        if (k < 0 || k > m) {
            return 0;
        }
        return (fact[m] / fact[k]) / fact[m - k];
    }

} comb(MAXV);

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;

    while(t--) {
       solve();
    }

    return 0;
}

void solve() {

}