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
    //std::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<int> fa(n + 1);
    std::vector<ll> dis(n + 1);
    std::iota(fa.begin(), fa.end(), 0);

    auto find = [&](auto&& self, int x) {
        if(x == fa[x]) return x;
        int t = fa[x];
        fa[x] = self(self, t);
        dis[x] += dis[t];
        return fa[x];
    };

    auto join = [&](int l, int r, ll v = 0LL) {
        int lf = find(find, l);
        int rf = find(find, r);
        if(lf == rf) return;
        fa[lf] = rf;
        dis[lf] = dis[r] - dis[l] + v;
    };

    auto query = [&](int l, int r) {
        int lf = find(find, l);
        int rf = find(find, r);
        if(lf != rf) return Inf;
        return dis[l] - dis[r];
    };

    while(m--) {
        int l, r;
        ll sum = 0LL;
        std::cin >> l >> r >> sum;
        --l;
        join(l, r, sum);
    }
    while(q--) {
        int l, r;
        std::cin >> l >> r;
        --l;
        ll sum = query(l, r);
        if(sum == Inf) std::cout << "UNKNOWN\n";
        else std::cout << sum << '\n';
    }
}