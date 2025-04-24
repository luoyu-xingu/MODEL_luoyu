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
    //std::cin>>t;
    while(t--) solve();
    return 0;
}
void solve(){
    int x;
    std::vector<int> a;
    while(std::cin>>x){
        a.push_back(x);
    }
    int n=a.size();
    for(int i=0;i<n;i++){
        std::cin>>a[i];
    }

    std::vector<int> p;
    for(int i=0;i<n;i++){
        if(p.empty()||-a[i]>=p.back()) p.push_back(-a[i]);
        else{
            auto it = std::upper_bound(p.begin(),p.end(),-a[i]);
            *it = -a[i];
        }
    }

    std::cout<<p.size()<<'\n';
    p.clear();
    for(int i=0;i<n;i++){
        if(p.empty()||a[i]>p.back()) p.push_back(a[i]);
        else{
            auto it = std::lower_bound(p.begin(),p.end(),a[i]);
            *it = a[i];
        }
    }
    std::cout<<p.size()<<'\n';
}

//对偏序集 ⟨A,≤⟩，设 A 中最长链的长度是 n，则将 A 中元素分成不相交的反链，反链个数至少是n。
//最少的不上升子序列的个数就是最长上升子序列的长度。