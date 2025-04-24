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
    std::string s;
    std::cin >> s;
    std::string ss;
    for(int i = 0; i < s.size(); i++) {
        ss += "#";
        ss += s[i];
    }

    ss.push_back('#');

    auto manacher = [&](std::string s) {
        std::vector<int> p(s.size());
        int max = -1, c = 0, r = 0;
        for(int i = 0; i < s.size(); i++) {
            int len = (r > i) ? std::min(p[2 * c - i], r - i) : 1;
            while(i + len < s.size() and i - len >= 0 and s[i + len] == s[i - len]) {
                len++;
            }
            if(i + len > r) {
                r = i + len;
                c = i;
            }
            p[i] = len;
            max = std::max(max, p[i]);
        }
        return max - 1;
    };
    std::cout << manacher(ss) << '\n';
}