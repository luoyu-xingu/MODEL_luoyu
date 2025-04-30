#include<bits/stdc++.h>

using ll = long long;

std::array<int, 8> dx = {1, -1, 0, 0, 1, -1, 1, -1};
std::array<int, 8> dy = {0, 0, 1, -1, 1, -1, -1, 1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;
const int N = 1e6 + 7;
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
    int n, m;
    std::cin >> n >> m;

    int B = 2157;
    std::vector<int> a(n + 1), K(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        K[i] = (i - 1) / B + 1;
    }

    std::vector<std::array<int, 4>> query{{}};
    std::vector<std::array<int, 2>> modify{{}};
    for (int i = 1; i <= m; i++) {
        char op;
        std::cin >> op;
-----------------
    }

    std::sort(query.begin(), query.end(), [&](auto x, auto y) {
        if (K[x[0]] != K[y[0]]) {
            return x[0] < y[0];
        } else if (K[x[1]] != K[y[1]]) {
            return x[1] < y[1];
        } else {
            return x[2] < y[2];
        }
    });

    std::vector<int> ans(query.size());
    std::vector<int> cnt(N);
    int l = 1, r = 0, t = 0, val = 0;

    auto add = [&](int x) {
-------------------
    };
    auto del = [&](int x) {
-----------------
    };
    auto time = [&](int t) {
-----------------
    };
    for (int i = 1; i < query.size(); i++) {
        auto [ql, qr, ti,id] = query[i];
        while (l < ql) {
            del(l++);
        }
        while (l > ql) {
            add(--l);
        }
        while (r < qr) {
            add(++r);
        }
        while (r > qr) {
            del(r--);
        }
        while (t < ti) {
            time(++t);
        }
        while (t > ti) {
            time(t--);
        }
        ans[id] = val;
    }

    for (int i = 1; i < ans.size(); i++) {
        std::cout << ans[i] << "\n";
    }
}
