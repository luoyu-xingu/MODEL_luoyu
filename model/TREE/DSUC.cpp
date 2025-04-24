#include<bits/stdc++.h>

using ll = long long;

class DSU {
    std::vector<int> fa;
    std::vector<int> sze;

    public:
    DSU(int n = 0) {
        fa.assign(n + 1, 0);
        sze.assign(n + 1, 1);
        std::iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) {
        while(x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }

    bool issame(int l, int r) {
        return find(l) == find(r);
    }

    bool merge(int l, int r) {
        l = find(l);
        r = find(r);

        if(l == r) {
            return false;
        }
        
        sze[l] += sze[r];
        fa[r] = l;

        return true;
    }

    int size(int x) {
        return sze[find(x)];
    }
};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

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
    int n, m, q;
    std::cin >> n >> m >> q;
    DSU dsu(n);

    for(int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        dsu.merge(u, v);
    }

    while(q--) {
        int l, r;
        std::cin >> l >> r;
        if(dsu.issame(l, r)) {
            std::cout << "Yes\n";
        }
        else {
            std::cout << "No\n";
        }
    }

}
