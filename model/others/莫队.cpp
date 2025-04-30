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
//    std::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> a(n + 1);
    std::vector<int> lo(n + 1);
    int B = sqrt(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        lo[i] = (i - 1) / B + 1;
    }

    std::vector<std::array<int, 3>> q(m + 1);
    for (int i = 1; i <= m; i++) {
        std::cin >> q[i][0] >> q[i][1];
        q[i][2] = i;
    }

    std::sort(q.begin(), q.end(), [&](auto x, auto y) {
        if (lo[x[0]] != lo[y[0]]) {
            return lo[x[0]] < lo[y[0]];
        } else {
            if (lo[x[0]] & 1) {
                return x[1] < y[1];
            } else {
                return x[1] > y[1];
            }
        }
    });

    int l = 1, r = 0;
    ll val = 0LL;
    std::vector<ll> ans(n + 1);
    auto add = [&](int x) {
      
    };
    auto del = [&](int x) {

    };
    for (int i = 1; i <= m; i++) {
        auto [ql, qr, id] = q[i];
        while (r < qr) {
            add(a[++r]);
        } 
        while (r > qr) {
            del(a[r--]);
        }
        while (l > ql) {
            add(a[--l]);
        }
        while (l < ql) {
            del(a[l++]);
        }
        ans[id] = val;
    }  

    for (int i = 1; i <= m; i++) {
        std::cout << ans[i] << "\n";
    } 
}
