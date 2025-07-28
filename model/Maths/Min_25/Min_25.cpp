#include<bits/stdc++.h>
using ll = long long;
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
    Mint &operator= (const T &_x) {
        x = _to(_x);
        return *this;
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

//int Mint::mod = 998244353;
int Mint::mod = 1e9 + 7;
using Z = Mint;

const int N = 1e6 + 7; // N = std::sqrt(n);

std::vector<int> minp;
int id1[N], id2[N], pris[N], cnt = 0;
ll w[2 * N];
Z h1[2 * N], sh1[2 * N], g1[2 * N];
Z h2[2 * N], sh2[2 * N], g2[2 * N];
ll n = 0, tot = 0;
void sieve(int n) {
    minp.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            minp[i] = i;
            pris[++cnt] = i;
        }
        for (int j = 1; j <= cnt; j++) {
            int x = pris[j];
            if (1LL * x * i > n) {
                break;
            }
            minp[x * i] = x;
            if (i % x == 0) {
                break;
            }
        }
    }
}

ll B = 0; // B = std::sqrt(n);
int &id(ll x) {
    if (x <= B) {
        return id1[x];
    } else {
        return id2[n / x];
    }
}


void init(ll _n) {
    n = _n;
    B = std::sqrt(n);
    for (ll l = 1; l <= n;) {
        ll r = n / (n / l);
        w[++tot] = n / l;
        id(n / l) = tot;
        l = r + 1;
    }
    for (int i = 1; i <= cnt; i++) {
        /*处理出h数组信息*/
        h1[i] = 1LL * pris[i] * pris[i];
        sh1[i] = sh1[i - 1] + h1[i];

        h2[i] = pris[i];
        sh2[i] = sh2[i - 1] + h2[i];
    }

    for (int i = 1; i <= tot; i++) {
        /*处理出g(w[i], 0),需要-1*/
        g2[i] = (Z)w[i] * (w[i] + 1) / 2 - 1;
        g1[i] = (Z)w[i] * (w[i] + 1) * (2 * w[i] + 1) / 6 - 1;
    }

    for (int i = 1; i <= cnt and 1LL * pris[i] * pris[i] <= n; i++) {
        for (int j = 1; j <= tot and 1LL * pris[i] * pris[i] <= w[j]; j++) {
            g1[j] = g1[j] - h1[i] * (g1[id(w[j] / pris[i])] - sh1[i - 1]); 
            g2[j] = g2[j] - h2[i] * (g2[id(w[j] / pris[i])] - sh2[i - 1]); 
        }
    }
}

Z S(ll m, int j) {
    if (pris[j] >= m) {
        return 0;
    }
    Z res = g1[id(m)] - sh1[j] - (g2[id(m)] - sh2[j]);

    for (int i = j + 1; i <= cnt and 1LL * pris[i] * pris[i] <=m; i++) {
        ll t = pris[i];
        for (int k = 1; t <= m; ++k, t *= pris[i]) {
            Z q = t;
            q *= t - 1;
            res += q * (S(m / t, i) + (k > 1));
        }
    }
    return res;
}

Z solve(ll r) {
    tot = 0;
    init(r);
    return S(r, 0) + 1;
}
// p^2 - p;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); 
    sieve(N);
    ll r;
    std::cin >> r;
    std::cout << solve(r) << "\n";
/*     for (int i = 1; i <= r; i++) {
        std::cout << solve(i) << " \n"[i == r];
    } */
    return 0;
}