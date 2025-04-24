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
    std::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for(int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int eor = 0;
    for(int i = 0; i < n; i++) {
        eor ^= a[i];
    }
    int max = *std::max_element(a.begin(), a.end());
    if(max == 1 ) {
        if(n % 2 == 0) {
            std::cout << "John\n";
        }
        else {
            std::cout << "Brother\n";
        }
    }
    else {
        if(eor == 0) {
            std::cout << "Brother\n";
        }
        else {
            std::cout << "John\n";
        }
    }
}