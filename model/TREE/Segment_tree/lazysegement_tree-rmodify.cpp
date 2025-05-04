#include<bits/stdc++.h>

using ll = long long;

const int inf = 0x3f3f3f3f;
const ll Inf = 0x3f3f3f3f3f3f3f3f;

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
    ll ch;

    Tag() {
        add = 0;
        ch = -Inf;
    }

    Tag(int op, ll x) {
        if (op == 1) {
            ch = x;
            add = 0;
        } else {
            add = x;
            ch = -Inf;
        }
    }

    void apply(const Tag &v) {
        if (v.ch != -Inf) {
            ch = v.ch;
            add = v.add;
        } else {
            add += v.add;
        }
    }
};

struct Info {
    int l, r;
    ll max;
    Info() {
        l = r = 0;
        max = -Inf;
    }

    //pull操作所用
    Info(int l, int r, ll x) {
        this -> l = l;
        this -> r = r;
        max = x;
    }
    
    //懒更新用
    void apply(Tag v) {
        if (v.ch != -Inf) {
            max = v.ch;
        }

        max += v.add;
    }

    ll getinfo() {
        return max;
    }
};
// pull 用
Info operator + (Info a, Info b) {
    auto [l, r] = std::minmax({a.l, a.r, b.l, b.r});
    return {l, r, std::max(a.max, b.max)};
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
    std::cin >> n >> m;

    std::vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    LazySegment_tree<Info, Tag> tr(n, a);

    while (m--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int l, r, x;
            std::cin >> l >> r >> x;
            tr.Rapply(l, r, {1, x});
        } else if (op == 2){
            int l, r, x;
            std::cin >> l >> r >> x;
            tr.Rapply(l, r, {2, x});
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << tr.Rquery(l, r).getinfo() << "\n";
        }
    }
}
