#include<bits/stdc++.h>

using ll = long long;

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
  
    int t = 1;
    //std::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    std::string a, b;
    std::cin >> a >> b;
    std::vector<int> z(b.size());
    auto get_z = [&](std::string s) {
        z[0]=s.size();
        int c=1,r=1;
        for(int i = 1; i < s.size(); i++) {
            int len = (i < r) ? std::min(z[i - c], r - i) : 0;
            while(i + len < s.size() and s[i + len] == s[len]) {
                len++;
            }
          
            if(i + len > r) {
                c = i;
                r = i + len;
            }
            z[i] = len;
        }
    };
  
    get_z(b);
    std::vector<int> e(a.size());
    auto get_e = [&](std::string s, std::string ss){
        int c = 0,r = 0;
        for(int i = 0;i < s.size(); i++){
            int len = (i < r) ? std::min(z[i - c],r - i) : 0;
            while(i + len < s.size() and len < ss.size() and s[i + len] == ss[len]) {
                len++;
            }
            if(i + len > r){
                c = i;
                r = i + len;
            }
            e[i] = len;
        }
    };
  
    get_e(a, b);
  
    ll ans = 0;
    for(int i = 0; i < b.size(); i++)
        ans ^= 1LL* (i + 1) * (z[i] + 1);
    std::cout<<ans<<'\n';
  
    ans=0LL;
    for(int i=0;i<a.size();i++){
        ans^=1LL * (i + 1) * (e[i] + 1);
    }
  
    std::cout<<ans<<'\n';
}
