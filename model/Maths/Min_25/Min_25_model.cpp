#include<bits/stdc++.h>

using ll = long long;

namespace Min_25 {
    int N, B, tot = 0, cnt = 0; 
    // N:最大范围开根号， B:std::sqrt(n), tot:值域计数, cnt:质数计数
    ll n = 0;
    std::vector<int> minp, pris, id1, id2;
    std::vector<ll> w;
    std::vector<ll> h1, sh1, g1;
    /*按照需要添加*/

void sieve(int n) {
    minp.assign(n + 1, 0);
    pris.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            minp[i] = i;
            pris[++cnt] = i;
        }
        for (int j = 1; j <= cnt; j++) {
            int x = pris[j];
            if (1LL * x * i > n) {
                break;
            }
            minp[x * i] = x;
            if (i % x == 0) {
                break;
            }
        }
    }
}
int &id(ll x) {
    if (x <= B) {
        return id1[x];
    } else {
        return id2[n / x];
    }
}
void init(ll _N) {
    N = _N;
    id1.assign(2 * N, 0);
    id2.assign(2 * N, 0);
    w.assign(2 * N, 0);
    h1.assign(2 * N, 0);
    sh1.assign(2 * N, 0);
    g1.assign(2 * N, 0);
    sieve(N);
}
void G(ll r) {
    n = r;
    B = std::sqrt(n);
    for (ll l = 1; l <= n;) {
        ll r = n / (n / l);
        w[++tot] = n / l;
        id(n / l) = tot;
        l = r + 1;
    }
    for (int i = 1; i <= cnt; i++) {
        /*处理出h数组信息*/
        h1[i]/**/;
        sh1[i] = sh1[i - 1] + h1[i];
    }

    for (int i = 1; i <= tot; i++) {
        /*处理出g(w[i], 0),需要-1*/
        g1[i] /*w[i]范围内h求和*/;
    }

    for (int i = 1; i <= cnt and 1LL * pris[i] * pris[i] <= n; i++) {
        for (int j = 1; j <= tot and 1LL * pris[i] * pris[i] <= w[j]; j++) {
            g1[j] = g1[j] - h1[i] * (g1[id(w[j] / pris[i])] - sh1[i - 1]);
        }
    }    
}
ll S(ll m, int j) {
    if (pris[j] >= m) {
        return 0;
    }
    /*g数组组合*/
    ll res = g1[id(m)] - sh1[j];

    for (int i = j + 1; i <= cnt and 1LL * pris[i] * pris[i] <=m; i++) {
        ll t = pris[i];
        for (int k = 1; t <= m; ++k, t *= pris[i]) {
            res += /*f(t)*/ (S(m / t, i) + (k > 1));
        }
    }
    return res;
}
ll min_25 (ll r) {
    tot = 0;
    return S(r, 0) + 1;
}
}

int main() {
    return 0;
}