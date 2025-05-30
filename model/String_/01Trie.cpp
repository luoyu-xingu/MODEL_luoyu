#include<bits/stdc++.h>

using ll = long long;

// 01Trie 维护 x 和一堆数字里的最大异或
template<const int BIT = 30, typename P = int>
class Trie {
    class Node {
        public:

        std::array<int, 2> nxt;
        int passed,endw;

        Node () {
            nxt[0] = nxt[1] = passed = endw = 0;
        }
    };

    std::vector<Node> T;

    int newnode() {
        T.emplace_back(Node());
        return T.size() - 1;
    }

    public:

    Trie () {
        T.assign(2, Node());
    }

    void add(P x, int t = 1) {
        int o = 1;
        T[o].passed += t;

        for(int i = BIT; i >= 0; i--) {
            assert(T[o].passed >= 0);
            int b = x >> i & 1;
            if(!T[o].nxt[b]) {
                T[o].nxt[b] = newnode();
            }
            o = T[o].nxt[b];
            T[o].passed += t;
        }
        assert(T[o].endw + t >= 0);
        T[o].endw += t;
    }

    P query(P x) {
        P ans = 0;
        int o = 1;
        for(int i = BIT; i >= 0; i--) {
            int b = x >> i & 1;
            // 用下一个节点的passed信息，因为涉及删除操作，如果删除，节点会复用
            // 由于每个数都添加了BIT + 1 个节点， 因此路一定存在
            if(T[T[o].nxt[b ^ 1]].passed) {
                b ^= 1;
                ans |= (P)1 << i;
            }
            o = T[o].nxt[b];
        }
        return ans;
    }
};

int main() {
    Trie<60, ll> tr;
    ll x = 1e12, y = 9e10;
    std::cout << x << " " << y << "\n"; 
    std::cout << (x ^ y) << "\n";
    tr.add(x);
    std::cout << tr.query(9e10) << '\n';
    return 0;
}













反正很神奇，/*第八届广西大学生程序设计大赛暨2025邀请赛-G*/
/*
#include<bits/stdc++.h>

using ll = long long;

// 01Trie 维护 x 和一堆数字里的最大异或
template<const int BIT = 30, typename P = int>
class Trie {
    class Node {
        public:

        std::array<int, 2> nxt;
        std::array<std::array<int, 2>, 2> passed;

        Node () {
            nxt[0] = nxt[1] = 0;
            passed[0][0] = passed[0][1] = passed[1][0] = passed[1][1]  = 0;
        }
    };

    std::vector<Node> T;

    int newnode() {
        T.emplace_back(Node());
        return T.size() - 1;
    }

    public:

    Trie () {
        T.assign(2, Node());
    }

    void add(P x, P y, int t = 1) {
        int o = 1;
        for (int i = BIT; i >= 0; i--) {
            int b1 = x >> i & 1;
            int b2 = y >> i & 1;
            int c = b1 ^ b2;
            if (!T[o].nxt[c]) {
                T[o].nxt[c] = newnode();
            }
            o = T[o].nxt[c];
            T[o].passed[b1][b2] += t;
        }
    }

    template <class U>
    U query(P x, P y) {
        int o = 1;
        U ans = 0;
        for (int i = BIT; i >= 0; i--) {
            int b1 = x >> i & 1;
            int b2 = y >> i & 1;
            int c = b1 ^ b2;
            ans += T[T[o].nxt[c ^ 1]].passed[b1][b2 ^ 1];
            o = T[o].nxt[c];
        }
        return ans;
    }
};
    
void solve();
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}

void solve() {
    int n, k1, k2;
    std::cin >> n >> k1 >> k2;
    
    std::vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
    }
    
    Trie<29, int> tr;
    for (int i = 1; i <= n; i++) {
        tr.add(a[i], b[i]);
    }
    
    ll ans = 0;
    for (int i = 1; i <=n ; i++) {
        tr.add(a[i], b[i], -1);
        int t1 = k1 ^ a[i];
        int t2 = k2 ^ b[i];
        ans += tr.query(t1, t2);
    }

    std::cout << ans << "\n";

} */

