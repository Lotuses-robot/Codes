#include <cstdio>
#include <cstring>
#include <vector>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

#define ll long long

#define maxn 500005
int l[maxn], r[maxn];

const ll mod = 998244353;
const int Max = 1e6 + 10;
ll fact[Max],ifact[Max];
ll n,m;
ll A(int n) {
    return fact[n];
}
ll pow_mod(ll n,ll k)
{
    ll res=1;   
    n=n%mod;
    while (k>0)
    {
        if (k&1)
            res=res*n%mod;
        n=n*n%mod;
        k>>=1;
    }
    return res;
}
void init()    
{
    fact[0]=ifact[0]=1;
    for (int i=1;i<Max;i++)
    {
        fact[i]=(fact[i-1]*i)%mod;
        ifact[i]=pow_mod(fact[i],mod-2);
    }
}
ll C(ll n, ll m)
{
    if (n<m||m<0) return 0;
    return (fact[n]*ifact[m]%mod)*ifact[n-m]%mod;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    init();
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(l[i]);
        if (l[i] == n) l[0] = i;
    }
    for (int i = 1; i <= n; i++) {
        read(r[i]);
        if (r[i] == n) r[0] = i;
    }

    if (l[0] == r[0]) {
        printf("%d %lld\n", 2, A(n - 1));
    } else {
        ll ans1 = 0;
        // l == n first
        for (int i = 0; i < r[l[0]]; i++) {
            ans1 += C(r[l[0]] - 1, i) * A(i) % mod * A(n - i - 2) % mod; 
        }
        ll ans2 = 0;
        for (int i = 0; i < l[r[0]]; i++) {
            ans2 += C(l[r[0]] - 1, i) * A(i) % mod * A(n - i - 2) % mod;
        }
        printf("%d %lld\n", 3, (ans1 + ans2) % mod);
    }
}

/*
5 4 1 2 3
4 5 1 2 3
*/