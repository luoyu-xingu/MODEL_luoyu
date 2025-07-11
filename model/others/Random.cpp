#include<bits\stdc++.h>

using ll = long long;
const int N = 1e2;
const int V = 1e2;

template<const int MAXN, const ll MAXV>
class Random {
    public:
    Random() {}
    template <typename T>
    void rand_n(T &n) {
        if (MAXN < RAND_MAX) {
            n = rand() % (MAXN + 1);
        } else {
            n = (T)(1.0 * rand() / RAND_MAX * MAXN);
        }
    }

    template<typename T>
    void rand_v(T &v) {
        if (MAXV < RAND_MAX) {
            v = (T)(rand() % (MAXV + 1));
        } else {
            v = (T)(1.0 * rand() / RAND_MAX * MAXV);
        }
    }

    template<typename T>
    void rand(std::vector<T> &vec) {
        for (int i = 0; i < vec.size(); i++) {
            rand_v(vec[i]);
        }
    }
      

    template<typename T, typename U>
    void rand(std::pair<T, U> &p) {
        rand_v(p.first);
        rand_v(p.second);
    }


    template<typename T, const int Num>
    void rand(std::array<T, Num> &arr) {
        for (int i = 0; i < Num; i++) {
            rand_v(arr[i]);
        }
    }

    template<typename T>
    void rand(T *a, int n) {
        for (int i = 1; i <= n; i++) {
            rand_v(a[i]);
        }
    }
};

Random<N, V> R;

void solve();
int main() { 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 100;
    while(t--) {
    }

    return 0;
}