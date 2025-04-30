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
