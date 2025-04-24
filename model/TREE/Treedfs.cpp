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
     std::cout<<std::fixed<<std::setprecision(15);
     int t=1;
 //    std::cin>>t;
     while(t--) solve();
     return 0;
}
void solve(){
    int n;
    std::cin>>n;
    std::vector<int> a(n),b(n);
    for(int i=0;i<n;i++)
       std::cin>>a[i];
    for(int i=0;i<n;i++)
       std::cin>>b[i];

    std::map<int,int> ans;
    //后中转层；
    auto dfs =[&](auto &&self, int r, int s, int e, int in){
        if(e<=s)  return;
        int i;
        for(i=s;i<e;i++)
            if(b[i]==a[r-1]) break;
         ans[in]=a[r-1];
         self(self,r+i-e,s,i,2*in+1);
         self(self,r-1,i+1,e,2*in+2);
    };
    //前中转后只要换 r=0 左 r+1,右 r+i-s+1
    //转层序那么用map

    dfs(dfs,n,0,n,0);

    bool ok=true;
    for(auto [x,y]:ans){
        if(y){
            if(ok) 
            std::cout<<y,ok=false;
            else{ 
                std::cout<<" "<<y;
             }
        }
    }
}

/*  前中转层
void solve(){
    int n;
    std::cin>>n;
    std::vector<int> a(n),b(n);
    for(int i=0;i<n;i++)
       std::cin>>b[i];
    for(int i=0;i<n;i++)
       std::cin>>a[i];
    std::map<int,int> ans;

    auto dfs =[&](auto&& self,int r,int s,int e,int in){
        if(e<=s)  return;
        int i;
        for( i=s;i<e;i++)
            if(b[i]==a[r]) break;
        ans[in]=a[r];
         self(self,r+1,s,i,2*in+2);
         self(self,r+i-s+1,i+1,e,2*in+1);
    };

    dfs(dfs,0,0,n,0);
    bool ok=true;
    for(auto [x,y]:ans){
        if(y){
            if(ok) 
            std::cout<<y,ok=false;
            else{ 
                std::cout<<" "<<y;
             }
        }
    }
} */
