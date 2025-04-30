// legendre 公式和 Kummer定理

// v[p][x] 表示x质因数分解下p的次幂

#include<bits/stdc++.h>

using ll = long long;

std::array<int, 8> dx = {1, -1, 0, 0, 1, -1, 1, -1};
std::array<int, 8> dy = {0, 0, 1, -1, 1, -1, -1, 1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

const int N = 101;
std::vector<int> minp, prime;
void sieve(int n) {
    minp.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            prime.push_back(i);
            minp[i] = i;
        } 
        for (auto x : prime) {
            if (1LL * x * i > n) {
                break;
            }
            minp[i * x] = x;
            if (x == minp[i]) {
                break;
            }
        }
    }
}

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    sieve(N);
  
    int t = 1;
    //std::cin >> t;

    while(t--) {
       solve();
    }

    return 0;
}

void solve(){
    int n;
    std::cin >> n;

    auto legendre = [&](int x) {
        int res = 0;
        for (int i = n; i >= x; i /= x) {
            res += i / x;
        }
        return res;
    };

    ll ans = 1;
    for (auto x : prime) {
        if (x > n) {
            break;
        }
        ans *= legendre(x) + 1;
    }
    std::cout << ans << "\n";
}

// v[p][n!] = (n - S(n)) / (p - 1);
//其中S(n) 表示p进制下各个位数和

//v[p][x * y] = v[p][x] + v[p][y];
//v[p][x / y] = v[p][x] - v[p][y];