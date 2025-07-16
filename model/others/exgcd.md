# 二元一次不定方程
$$by\  luoyu\_xingu$$
## 1.解决 $ax$ + $by$ = $gcd($a$, $b$)$问题  
过程如下: 

$$ax + by = gcd(a, b)$$  

$$\ \ \ \ \  \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \Rightarrow bx_2 + (a - \lfloor\frac{a}{b}\rfloor * b)y_2 = gcd(b,a\%b)$$  

$$\ \ \ \ \  \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \  \ \ \Rightarrow ay_2 + b * (x_2 - \lfloor\frac{a}{b}\rfloor * y_2) = gcd(b,a\%b)$$  

$$\ \ \ \Rightarrow x = y_2, y = x_2 - \lfloor\frac{a}{b}\rfloor * y_2$$  

$$\cdots\ \cdots$$  
  
$$\ \ \ \Rightarrow if (b == 0) : x = 1, y = 0$$  


采用**扩展欧几里得算法**$（exgcd）$
`````
void exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }

    exgcd(b, a % b, x, y);
    auto t = y;
    y = x - a / b * y;
    x = t;
} 
``````

## 2.裴蜀定理
$ax + by = c$ 有解，当且仅当$gcd(a, b) | c$

~~凭借直觉可证~~

## 3.计算 $ax$ + $by$ = $c$ $($gcd(a, b)$ | $c$)$
$$\ \ \ \ d = c / gcd(a, b)$$
$$\ \ \ \ \ \ \Rightarrow ax + by = gcd(a, b)$$
$$\Rightarrow exgcd(a, b, x, y)$$
$$\ \ \ \ \ \ \ \ \ \Rightarrow x_0 = d * x, y_0 = d * y$$

## 4. 求$ax + by = c$通解
$$x = x_0 - \lfloor\frac{b}{d}\rfloor * n$$
$$y = y_0 + \lfloor\frac{a}{d}\rfloor * n$$
$其中 n(\cdots, -1, 0, 1, 2, \cdots)$

## 5. 扩展
1. 求乘法逆元  
    $$\ ax \% p = 1$$
    $$\Rightarrow ax + pb = 1$$
$这里要求$a$, $p$互质$  
2. 求符合要求的特解  
这里给出洛谷模板 [https://www.luogu.com.cn/problem/P5656](https://www.luogu.com.cn/problem/P5656)  
下面是本蒟蒻的解答
`````````
#include<bits/stdc++.h>

using ll = long long;


void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return ;
    }

    exgcd(b, a % b, x, y);
    auto t = y;
    y = x - a / b * y;
    x = t;
}
void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;

    while(t--) {
       solve();
    }

    return 0;
}

void solve(){
    ll a, b, c;
    std::cin >> a >> b >> c;

    int d = std::gcd(a, b);
    if (c % d) {
        std::cout << -1 << "\n";
        return ;
    }

    ll x, y;
    exgcd(a, b, x, y);
    x *= c / d;
    y *= c / d;

    b /= d, a /= d;

    ll lo = (1 - x) / b;
    ll hi = (y - 1) / a;
    if (1 - x >= 0) {
        lo = (1 - x + b - 1) / b;
    }
    if (y - 1 <= 0) {
        hi = (y - 1) / a - ((std::abs(y - 1) % a) != 0);
    }

    if (hi - lo + 1<= 0) {
        std::cout << x + lo * b << " " << y - a * hi << "\n";
    } else {
        std::cout << hi - lo + 1 << " ";
        std::cout << x + lo * b << " " << y - a * hi << " ";
        std::cout << x + hi * b << " " << y - a * lo << "\n";
    }
}
`````````
  

plus:  

第一次发博客也是学习记录