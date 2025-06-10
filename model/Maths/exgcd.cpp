#include<bits/stdc++.h>

using ll = long long;

std::array<int, 8> dx = {1, -1, 0, 0, 1, -1, 1, -1};
std::array<int, 8> dy = {0, 0, 1, -1, 1, -1, -1, 1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;
void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return ;
    }

    exgcd(b, a % b, x, y);
    auto t = y;
    y = x - a / b * y;
    x = t;
}
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

void solve(){
    ll a, b, c;
    std::cin >> a >> b >> c;

    int d = std::gcd(a, b);
    if (c % d) {
        std::cout << -1 << "\n";
        return ;
    }

    ll x, y;
    exgcd(a, b, x, y);
    x *= c / d;
    y *= c / d;

    b /= d, a /= d;

    ll lo = (1 - x) / b;
    ll hi = (y - 1) / a;
    if (1 - x >= 0) {
        lo = (1 - x + b - 1) / b;
    }
    if (y - 1 <= 0) {
        hi = (y - 1) / a - ((std::abs(y - 1) % a) != 0);
    }

    if (hi - lo + 1<= 0) {
        std::cout << x + lo * b << " " << y - a * hi << "\n";
    } else {
        std::cout << hi - lo + 1 << " ";
        std::cout << x + lo * b << " " << y - a * hi << " ";
        std::cout << x + hi * b << " " << y - a * lo << "\n";
    }
}