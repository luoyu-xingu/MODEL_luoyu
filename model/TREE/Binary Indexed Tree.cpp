#include<bits/stdc++.h>

using ll = long long;

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

// 查询逆序对数目;
template<typename P = int>
class BIT {
    std::vector<P> T;
    int _n;

    int lowbit(int i) {
        return i & (-i);
    }

    public:
    BIT() {}
    BIT(int n) :_n(n) {
        T.assign(n + 1, (P)0);
    }
    
    void add(P x, int pos) {
        for (int i = pos; i <= _n; i += lowbit(i)) {
            T[i] += x;
        }
    }

    P query(int l, int r) {
        P ans = 0;
        for (int i = r; i > 0; i -= lowbit(i)) {
            ans += T[i];
        }
        for (int i = l - 1; i > 0; i -= lowbit(i)) {
            ans -= T[i];
        }
        return ans;
    }
};

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
//    std::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    auto b = a;
    std::sort(b.begin(), b.end());
    for (int i = 1; i <= n; i++) {
        a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    BIT<ll> B(n);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += B.query(a[i] + 1, n);
        B.add(1, a[i]);
    }

    std::cout << ans << "\n";
}
