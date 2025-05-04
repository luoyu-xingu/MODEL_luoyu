#include<bits/stdc++.h>

using ll = long long;
int mod;
template<class Info, class Tag>
class LazySegment_tree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;

    void pull_up(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    template<class T>
    void build(int p, int l, int r, const std::vector<T> &a) {
        info[p].l = l, info[p].r = r;
        if (l == r) {
            info[p] = {l, r, a[l]};
            return;
        }
        int mid = l + r >> 1;
        build(2 * p, l, mid, a);
        build(2 * p + 1, mid + 1, r, a);
        pull_up(p);
    }

    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push_down(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void rangeApply(int p, int l, int r, int x, int y, Tag v) {
        if (x <= l and y >= r) {
            apply(p, v);
            return;
        }
        int mid = l + r >> 1;
        push_down(p);
        if (x <= mid) {
            rangeApply(2 * p, l, mid, x, y, v);
        } 
        if (y > mid) {
            rangeApply(2 * p + 1, mid + 1, r, x, y, v);
        }
        pull_up(p);
    }

    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (x <= l and y >= r) {
            return info[p];
        }

        int mid = l + r >> 1;
        push_down(p);
        if (x > mid) {
            return rangeQuery(2 * p + 1, mid + 1, r, x, y);
        } else if (y <= mid) {
            return rangeQuery(2 * p, l, mid, x, y);
        }

        return rangeQuery(2 * p + 1, mid + 1, r, x, y) + rangeQuery(2 * p, l, mid, x, y);
    }

    public:
    template<class T>
    LazySegment_tree(int _n, const std::vector<T> &a) {
        n = _n;
        info.assign(4 * n + 7, Info());
        tag.assign(4 * n + 7, Tag());
        build(1, 1, n, a);
    }

    void Rapply(int x, int y, Tag v) {
        rangeApply(1, 1, n, x, y, v);
    }

    Info Rquery(int x, int y) {
        return rangeQuery(1, 1, n, x, y); 
    }
};

// 以下为带修改部分， 主要为懒更新的使用和维护信息
//下面为区间和版本
struct Tag {
    ll add;

    Tag() {
        add = 0;
    }

    Tag(ll x) {
        add = x;
    }

    void apply(const Tag &v) {
        add += v.add;
        add %= mod;
    }
};
struct Info {
    int l, r;
    ll sum;
    Info() {
        l = r = sum = 0;
    }

    //pull操作所用
    Info(int l, int r, ll x) {
        this -> l = l;
        this -> r = r;
        sum = x % mod;
    }
    
    //懒更新用
    void apply(Tag v) {
        sum += 1LL * (r - l + 1) * v.add;
        sum %= mod;
    }

    ll getinfo() {
        return sum % mod;
    }
};
// pull 用
Info operator + (Info a, Info b) {
    auto [l, r] = std::minmax({a.l, a.r, b.l, b.r});
    return {l, r, (a.sum + b.sum) % mod};
}

void solve();
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
void solve() {
    int n, m, r;
    std::cin >> n >> m >> r >> mod;

    std::vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    std::vector<std::vector<int>> e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    std::vector<int> hson(n + 1), dep(n + 1), top(n + 1), dfn(n + 1), rdfn(n + 1), fa(n + 1), sze(n + 1);
    auto dfs = [&](auto &&self, int u, int f) -> void {
        fa[u] = f;
        dep[u] = dep[f] + 1;
        sze[u] = 1;
        for (auto v : e[u]) {
            if (v == f) {
                continue;
            } 
            self(self, v, u);
            sze[u] += sze[v];
            if (sze[v] > sze[hson[u]]) {
                hson[u] = v;
            }
        }
    };
    dfs(dfs, r, r);

    int cur = 0;
    auto Set = [&](auto &&self, int u, int f) -> void {
        top[u] = f;
        dfn[u] = ++cur;
        rdfn[cur] = u;

        if (hson[u] == 0) {
            return;
        }

        self(self, hson[u], f);
        for (auto v : e[u]) {
            if (v == hson[u] || v == fa[u]) {
                continue;
            }
            self(self, v, v);
        }
    };
    Set(Set, r, r);

    std::vector<ll> c(n + 1);
    for (int i = 1; i <= n; i++) {
        c[i] = a[rdfn[i]];
    }

    LazySegment_tree<Info, Tag> tr(n, c);

    while (m--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int u, v, k;
            std::cin >> u >> v >> k;
            while (top[u] != top[v]) {
                if (dep[top[u]] < dep[top[v]]) {
                    tr.Rapply(dfn[top[v]], dfn[v], (ll)k);
                    v = fa[top[v]];                  
                } else {
                    tr.Rapply(dfn[top[u]], dfn[u], (ll)k);
                    u = fa[top[u]];
                }
            }
            tr.Rapply(std::min(dfn[u], dfn[v]), std::max(dfn[u], dfn[v]), (ll)k);
        } else if (op == 2) {
            int u, v;
            std::cin >> u >> v;
            ll ans = 0;
            while (top[u] != top[v]) {
                if (dep[top[u]] < dep[top[v]]) {
                    ans += tr.Rquery(dfn[top[v]], dfn[v]).getinfo();
                    ans %= mod;
                    v = fa[top[v]];                  
                } else {
                    ans += tr.Rquery(dfn[top[u]], dfn[u]).getinfo();
                    ans %= mod;
                    u = fa[top[u]];
                }
            }
            ans += tr.Rquery(std::min(dfn[u], dfn[v]), std::max(dfn[u], dfn[v])).getinfo();
            ans %= mod;
            std::cout << ans << "\n";
        } else if (op == 3) {
            int x, k;
            std::cin >> x >> k;
            tr.Rapply(dfn[x], dfn[x] + sze[x] - 1, (ll)k);
        } else {
            int x;
            std::cin >> x;
            std::cout << tr.Rquery(dfn[x], dfn[x] + sze[x] - 1).getinfo() << "\n";
        }
    }
}


/*操作1234
    1.
        u, v, k u到v路径上点权加v;
    2.
        u, v u到v的点权和；
    3.
        u, k 以u为根的子树，每个点权加k;
    4.
        u 查询u为根的子树的权值
*/
    
