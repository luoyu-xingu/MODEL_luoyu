#include<bits/stdc++.h>

using ll = long long;

std::array<int, 8> dx = {1, -1, 0, 0, 1, -1, 1, -1};
std::array<int, 8> dy = {0, 0, 1, -1, 1, -1, -1, 1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

const int N = 1e2+7;

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    //std::cin >> t;
    while(t--) solve();
    return 0;
}

void solve(){
    ll n;
    std::cin >> n;
    std::vector<ll> f(N);
    f[0] = f[1] =1;
    for( int i = 2; i < N; i++) {
        //if(f[i - 1] + f[i - 2] > n) break;
        f[i] = f[i - 1] + f[i - 2];
    }

    auto B = [&](ll p) {
        int l =0, r = N;
        int ans = r;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(f[mid] <= p) ans = mid,l = mid + 1;
            else r = mid - 1;
          //  std::cout << l << " " << r << '\n';
        }
        return f[ans];
    };
    auto x = B(n);
    while(x != n) {
        n -= x;
        x = B(n);
    }
    std::cout << n << '\n';
}