#include<bits/stdc++.h>

using ll = long long;

std::array<int, 8> dx = {1, -1, 0, 0, 1, -1, 1, -1};
std::array<int, 8> dy = {0, 0, 1, -1, 1, -1, -1, 1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

namespace FAST_GCD {
    const int N = 1e6 + 3;
    const int M = 1e3 + 7;
    std::vector _gcd(M + 1, std::vector<int>(M + 1));
    std::vector<int> minp(N + 1);
    std::vector<int> p;
    std::vector<std::array<int, 3>> sep(N + 1);   
    void init() {
        for(int i = 1; i <= M; i++) {
            _gcd[i][0] = _gcd[0][i] = i;
        }
        for(int i = 1; i <= M ; i++) {
            for(int j = 1; j <= i; j++) {
                _gcd[i][j] = _gcd[j][i] = _gcd[i - j][j];
            }
        }
        sep[1][0] = sep[1][1] = sep[2][0] = 1;
        for(int i = 2; i <= N; i++) {
            if(!minp[i]) {
                minp[i] = i;
                p.push_back(i);
                sep[i][0] = 1, sep[i][1] = 1, sep[i][2] = i;
            }
            for(auto x : p) {
                if(1LL * x * i > N) {
                    break;
                }
                auto y = sep[i][0] * x;
                if(y <= sep[i][1]) {
                    sep[i * x][0] = y;
                    sep[i * x][1] = sep[i][1];
                    sep[i * x][2] = sep[i][2];  
                }
                else if(y <= sep[i][2]) {
                    sep[i * x][0] = sep[i][1];
                    sep[i * x][1] = y;
                    sep[i * x][2] = sep[i][2];
                } 
                else {
                    sep[i * x][0] = sep[i][1];
                    sep[i * x][1] = sep[i][2];
                    sep[i * x][2] = y;
                }
                minp[i * x] = x;
                if(i % x == 0) {
                    break;
                } 
            }
        }
    }

    int query(int x, int y) {
        assert(x <= N and y <= N);
        if(x <= M and y <= M) {
            return _gcd[x][y];
        }
        auto q = sep[x];
        auto p = y;
        int g = 1;
        int d = 0;
        for(int i = 0; i < 3; i++) {
            if(q[i] <= M) {
                d = _gcd[q[i]][y % q[i]];
            }
            else {
                if(d % q[i] == 0) {
                    d = q[i];
                }
                else {
                    d = 1;
                }
            }
            g *= d;
            y /= d;
        }
        return g;
    }
}
void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    FAST_GCD::init();
    int t = 1;
    std::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    int x, y;
    std::cin >> x >> y;
    std::cout << FAST_GCD::query(x, y) << '\n';
}