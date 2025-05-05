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
        if (y < x) {
            return;
        }
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
        if (y < x) {
            return Info();
        }
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

        return rangeQuery(2 * p, l, mid, x, y) + rangeQuery(2 * p + 1, mid + 1, r, x, y);
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
    ll mul;
    Tag() {
        add = 0;
        mul = 1;
    }

    Tag(int op, int x) {
        if (op == 1) {
            add = 0;
            mul = x % mod;
        } else {
            add = x % mod;
            mul = 1;
        }
    }

    void apply(const Tag &v) {
        mul *= v.mul;
        mul %= mod;
        add *= v.mul;
        add %= mod;
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
        sum = x;
    }
    
    //懒更新用
    void apply(Tag v) {
        sum *= v.mul;
        sum %= mod;
        sum += (r - l + 1) * v.add % mod;
        sum %= mod;
    }

    ll getinfo() {
        return sum;
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
    int n, m;
    std::cin >> n >> m >> mod;

    std::vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    LazySegment_tree<Info, Tag> tr(n, a);
    //return;
    while (m--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int x, y, k;
            std::cin >> x >> y >> k;
            tr.Rapply(x, y, {op, k});
        } else if (op == 2) {
            int x, y, k;
            std::cin >> x >> y >> k;
            tr.Rapply(x, y, {op, k});
        } else {
            int x, y;
            std::cin >> x >> y;
            std::cout << tr.Rquery(x, y).getinfo() << "\n";
        }
    }
}
