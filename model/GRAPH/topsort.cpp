#include<bits/stdc++.h>

using ll = long long;

std::array<int,8> dx={1,-1,0,0,1,-1,1,-1};
std::array<int,8> dy={0,0,1,-1,1,-1,-1,1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;
const int N = 1e5+1;
const int mod = 80112002;

void solve();
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //std::cin>>t;
    while(t--) solve();
    return 0;
}
void solve(){
    int n, m;
    std::cin >> n >> m;
    std::vector e(n + 1, std::vector<int>());
    std::vector<int> ind(n + 1), c(n + 1);
    for(int i = 1;i <= m; i++){
        int u, v;
        std::cin >> u >> v;
        ind[v]++;
        e[u].emplace_back(v);
    }
    ll ans=0;
    std::queue<int> q;
    for(int i = 1;i <= n; i++){
        if(ind[i] == 0){ 
            q.push(i);
            c[i]=1;
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(e[u].empty()) ans=(ans + c[u])%mod;
        else{
            for(auto v : e[u]){
                c[v]=(c[v] + c[u])%mod;
                if(--ind[v] == 0) q.push(v);
            }
        }
    }
    std::cout<<ans<<'\n';
}