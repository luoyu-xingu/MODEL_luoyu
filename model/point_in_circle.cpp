#include<bits/stdc++.h>

using ll = long long;

std::array<int,8> dx={1,-1,0,0,1,-1,1,-1};
std::array<int,8> dy={0,0,1,-1,1,-1,-1,1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

void solve();
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t=1;
    std::cin>>t;
    while(t--) solve();
    return 0;
}
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n),r(n);
    for(int i = 0; i < n; i++)
       std::cin >> a[i];
    for(int i = 0; i < n; i++)
       std::cin >> r[i];
    std::map<int, int> mp;
    ll ans = 0;
    
    auto lfsqrt = [&](ll x) {
        ll a = std::sqrt(x);
        while (a * a > x) a--;
        while((a + 1) * (a + 1) <= x) x++;
        return a;
    };

    for(int i = 0; i < n; i++){
        for (int j = -r[i]; j <= r[i]; j++) {
            if(!mp[a[i] + j]){
              ans += lfsqrt(1LL * r[i] * r[i] - 1LL * j * j) * 2 + 1;
              mp[a[i] + j] = lfsqrt(1LL * r[i] * r[i] - 1LL * j * j) * 2 + 1;
            }
            else if(mp[a[i] + j] >= lfsqrt(1LL * r[i] * r[i] - 1LL * j * j) * 2 + 1) continue;
            else{
                ans += lfsqrt(1LL * r[i] * r[i] - 1LL * j * j) * 2 + 1;
                ans -= mp[a[i] + j];
                mp[a[i] + j] = lfsqrt(1LL * r[i] * r[i] - 1LL * j * j) * 2 + 1;
            }
       }
    }
    std::cout << ans << "\n";
}