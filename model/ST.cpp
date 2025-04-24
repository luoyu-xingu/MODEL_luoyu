#include<bits/stdc++.h>

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	int t = 1;
	//std::cin>>t;
	while(t--) solve();
	return 0;
}
void solve() {
	int n, m;
	std::cin >> m >> n;
	std::vector<std::vector<int>>a(m + 1, std::vector<int>((int)log2(m)+1));
	for(int i = 1; i <= m; i++)
		std::cin >> a[i][0];
        
	for(int j = 1; j <= (int)log2(m); j++)
		for(int i = 1; i + (1<<j) - 1 <= m; i++)
			a[i][j] = std::min(a[i][j - 1], a[i + (1 << j - 1)][j - 1]);

	auto query=[&](int l,int r) {
	    int k=log2(r - l + 1);
	    return std::min(a[l][k],a[r - (1 << k) + 1][k]);
	};
     while(n--) {
        int l, r;
		std::cin >> l >> r;
		std::cout << query(l, r) << " ";	
	 }
}
