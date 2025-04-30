#include<bits/stdc++.h>

using ll = long long;

std::array<int, 8> dx = {1, -1, 0, 0, 1, -1, 1, -1};
std::array<int, 8> dy = {0, 0, 1, -1, 1, -1, -1, 1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;
class Trie {
    class node {
        public:
        std::array<int, 26> nxt;
        int passed, endw;
        node() {
            passed = endw = 0;
            for (int i = 0; i < 26; i++) {
                nxt[i] = 0;
            }
        }
    };

    std::vector<node> T;

    int newnode() {
        T.emplace_back();
        return T.size() - 1;
    }
    public:
    Trie() {
        T.assign(2, node());
    }

    void add(std::string s, int t = 1) {
        assert(t > 0);
        int o = 1;
        for (auto c : s) {
            int q = c - 'a';
            if (!T[T[o].nxt[q]].passed) {
                T[o].nxt[q] = newnode();
            }
            T[o].passed += t;
            o = T[o].nxt[q];
        }
        T[o].passed += t;
        T[o].endw += t;
    }

    void query() {
        // 变动参数
    }
};
void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(15);

    int t = 1;
//    std::cin >> t;

    while(t--) {
       solve();
    }

    return 0;
}

void solve(){

}
