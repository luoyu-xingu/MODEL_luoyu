#include<bits/stdc++.h>

using ll = long long;

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;
const int N = 1e7 + 7;

std::vector<int> minp, prime;
void sieve(int n) {
    minp.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            prime.push_back(i);
            minp[i] = i;
        } 
        for (auto x : prime) {
            if (1LL * x * i > n) {
                break;
            }
            minp[i * x] = x;
            if (i % x == 0) {
                break;
            }
        }
    }
}

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    sieve(N);
  
    int t = 1;
    std::cin >> t;

    while(t--) {
       solve();
    }

    return 0;
}

void solve(){
}
