#include<bits/stdc++.h>

using ll = long long;

std::array<int, 8> dx = {1, -1, 0, 0, 1, -1, 1, -1};
std::array<int, 8> dy = {0, 0, 1, -1, 1, -1, -1, 1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(15);

    int t = 1;
    std::cin >> t;

    while(t--) {
       solve();
    }

    return 0;
}

void solve(){
    // 计算c(n + m, n) % p;
    int n, m, p;
    std::cin >> n >> m >> p;

    auto qpow = [&](auto a, int b) {
        ll res = 1;
        for (;b;b >>= 1, a = 1LL * a * a % p) {
            if (b & 1) {
                res *= a;
                res %= p;
            }
        }
        return res;
    };

    std::vector<ll> fact(p + 1, 1), inv(p + 1, 1);
    for (int i = 1; i <= p; i++) {
        fact[i] = fact[i - 1] * i % p;
        inv[i] = inv[i - 1] * qpow(i, p - 2) % p;
    }

    auto C = [&](int n, int m) {
        if (m > n) {
            return 0LL;
        }
        return fact[n] * inv[n - m] % p * inv[m] % p;
    };

    auto lucas = [&](int n, int m, int p) {
        ll res = 1;
        while (m) {
            res *= C(n % p, m % p);
            res %= p;
            n /= p;
            m /= p;
        }
        return res;
    };

    std::cout << lucas(n + m, n, p) << "\n";
}