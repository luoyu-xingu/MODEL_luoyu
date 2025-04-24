#include<bits/stdc++.h>

using ll = long long;

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

void solve();
int main() {
     std::ios::sync_with_stdio(false);
     std::cin.tie(nullptr);
     int t=1;
     //std::cin>>t;
     while(t--) solve();
     return 0;
}
void solve(){
    int n,k;
    std::cin>>n>>k;
    std::vector<std::vector<int>> c(n+1,std::vector<int>(n+1));
    for(int i=1;i<=n;i++)
       for(int j=1;j<=n;j++)
          std::cin>>c[i][j];
    std::vector f (n+1,std::vector<ll>(1<<k,Inf));
    for(int i=1;i<=k;i++)  f[i][1<<(i-1)]=0;
    for(int S=1;S<(1<<k);S++){
        for(int i=1;i<=n;i++){
           for(int T=S&(S-1);T;T = (T-1)&S)
              f[i][S] = std::min<ll>(f[i][S],f[i][S^T]+f[i][T]);
        }
        std::vector<bool> st(n+1);
        for(int i=1;i<n;i++){
            int v=-1;
            for(int j=1;j<=n;j++)
               if(!st[j]&&(v==-1||f[j][S]<f[v][S]))  v=j;
            if(v==-1)  break;
            st[v]=1;
            for(int j=1;j<=n;j++)
               f[j][S]=std::min<ll>(f[j][S],f[v][S]+c[v][j]);
        }
    }

    std::vector ans(n+1,std::vector<ll>(n+1));

    for(int s=k+1;s<=n;s++){
        std::vector g(n+1,std::vector<ll>(1<<k,Inf));
        g[s][0]=0;
       // for(int i=1;i<=k;i++)  g[i][1<<(i-1)]=0;
        for(int S=0;S<(1<<k);S++){
            for(int i=1;i<=n;i++){
               for(int T=S;T;T = (T-1)&S)
                  g[i][S] = std::min<ll>(g[i][S],g[i][S^T]+f[i][T]);
            }
            std::vector<bool> st(n+1);
            for(int i=1;i<n;i++){
                int v=-1;
                for(int j=1;j<=n;j++)
                   if(!st[j]&&(v==-1||g[j][S]<g[v][S]))  v=j;
                if(v==-1)  break;
                st[v]=1;
                for(int j=1;j<=n;j++)
                   g[j][S]=std::min<ll>(g[j][S],g[v][S]+c[v][j]);
            }
        }
        for(int j=k+1;j<=n;j++)
        ans[s][j]=g[j][(1<<k)-1];
    }
    int q;
    std::cin>>q;
    while(q--){
        int s,t;
        std::cin>>s>>t;
        std::cout<<ans[s][t]<<'\n';
    }

}