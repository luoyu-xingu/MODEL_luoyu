#include<bits/stdc++.h>

using ll = long long;

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    //std::cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}
void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n + 1), b(m + 1);
    for(int i = 0; i <= n; i++) {
      std::cin >> a[i];
    }
    for(int i = 0; i <= m; i++) {
      std::cin >> b[i];
    }

    auto convolution=[&](std::vector<int> x, std::vector<int> y) {
        const double pi = acos(-1);
        int m = x.size() + y.size() - 2;
        int n = 1;
        while(n <= m)  n <<= 1;
        auto change=[&](std::vector<std::complex<double>> &v) {
            std::vector<int> r(n);
            for(int i = 0;i < n;i++) {
              r[i]=r[i / 2] / 2 + (i & 1) * n / 2;
            }
            for(int i = 0; i < n; i++) {
              if(i > r[i]) std::swap(v[i], v[r[i]]);
            }
        };
        std::vector<std::complex<double>> a(n + 1), b(n + 1);
        std::vector<int> c(m + 1);
        for(int i = 0 ;i < x.size(); i++) {
          a[i] = x[i];
        }
        for(int i = 0; i < y.size(); i++) {
          b[i] = y[i];
        }
        auto fft=[&](std::vector<std::complex<double>> &v, int op) {
            change(v);
            for(int i = 2;i <= n;i <<= 1){
                std::complex<double> wi({cos(2 * pi / i), sin(2 * pi / i) * op});
                for(int j = 0;j < n;j += i) {
                  std::complex<double> wj({1, 0});
                  for(int k = 0; k < i / 2; k++){
                    std::complex<double> x = v[j + k],y = v[j + k + i / 2] * wj;
                    v[j + k] = x + y;
                    v[j + k + i / 2] = x - y;
                    wj = wi * wj;
                  }
                }
            }
        };
        fft(a, 1), fft(b, 1);
        for(int i = 0; i < n; i++) {
          a[i] = a[i] * b[i];
        }
        fft(a, -1);
        for(int i = 0; i <= m; i++) {
          c[i] = (int)(a[i].real() / n + 0.5);
        }
        return c;
    };

    
    auto c = convolution(a, b);
    for(auto x : c) {
      std::cout << x << " ";
    }
}
