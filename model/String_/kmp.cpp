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
    std::string s, ss;
    std::cin >> s >> ss;
    ss.push_back('0');
    std::vector<int> ans;
    std::vector<int> nxt(ss.size());
    auto kmp = [&](std::string s, std::string ss) {
        nxt[0] = -1;
        int c = -1;
        for(int i = 1; i < ss.size(); i++) {
            while(c >= 0 and ss[i - 1] != ss[c]) {
                c = nxt[c];
            }
            nxt[i] = ++c;
        }
        int x = 0, y = 0;
        int n = s.size(), m = ss.size();
        while(x < n) {
            if(s[x] == ss[y]) {
                x++;
                y++;
            }
            else {
                y = nxt[y];
            }
            if(y == -1) {
                x++;
                y++;
            }
            if(y == m -1) {
                ans.push_back(x - y + 1);
            }
        }
    };
    kmp(s, ss);
    for(auto x : ans) {
        std::cout << x << "\n";
    }
//    std::cout << ss << '\n';
    for(int i = 0; i < ss.size() - 1; i++) {
        std::cout << nxt[i + 1] << ' ';
    }

}