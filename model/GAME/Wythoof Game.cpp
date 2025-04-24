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
    int t = 1;
    //::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    int a, b;
    std::cin >> a >> b;
    if(a > b) std::swap(a, b);
    long double P = (sqrtl(5.0) + 1.0) / 2.0;
    int n = (int)((b - a) * P);
    if(a != n) std::cout << 1 << '\n';
    else std::cout << 0 << '\n';  
}