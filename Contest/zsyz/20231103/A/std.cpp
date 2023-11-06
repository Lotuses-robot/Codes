#include "bits/stdc++.h"
using namespace std;
#define ll long long
const __int128 ONE = 1;
ll qpow(ll a,ll b,ll mod)
{
	ll res = 1;
	while(b)
	{
		if(b & 1) res = ONE * res * a % mod;
		a = ONE * a * a % mod;
		b = b >> 1;
	}
	return res;
}
int Suk[25]={0,2,3,5,7,11,13,17,19,23,29,31,37};
inline bool chk(ll n,ll a,ll b,ll x) 
{
    printf("%lld %lld %lld\n", x, a, n);
    ll v = qpow(x , a , n);
        printf("%lld\n", v);
    if (v == 1) return 1;
    int j = 1;
    while(j <= b)
    {
    	if(v == n - 1) break;
		v = ONE * v * v % n;
        printf("%lld\n", v);
		j ++;
	}
    if (j > b) return 0;
    return 1;
}
inline bool mr(ll n)
{
	if(n < 3 || n % 2 == 0) return n == 2;
	if(n > 37)
	{
		ll a = n - 1 , b = 0;
		while(a % 2 == 0) a >>= 1 , b ++;
		for(int i = 1 ; i <= 12 ; i ++) if(!chk(n , a ,  b , Suk[i])) return 0;
		return 1;
	}
	else
	{
		for(int i = 1 ; i <= 12 ; i ++) if(n == Suk[i]) return 1;
		return 0;
	}
}
static std::mt19937 MoBaiXHR;
inline ll F(ll x,ll c,ll MOD){return (ONE * x * x % MOD + c) % MOD;}
inline ll ABS(ll x){if(x < 0) return -x;return x;}
ll gcd(ll a,ll b)
{
	if(!b) return a;
	return gcd(b , a % b);
}
inline ll pr(ll n)
{
	if(n == 4) return 2;
	std::uniform_int_distribution<ll> Rand(3 , n - 1);
	ll x = Rand(MoBaiXHR) , y = x , c = Rand(MoBaiXHR);
	x = F(x , c , n) , y = F(F(y , c , n) , c , n);
	for(int lim = 1 ; x != y ; lim = min(lim << 1 , 128))
	{	
		ll cnt = 1;
		for(int i = 0 ; i < lim ; i ++) 
		{
			cnt = ONE * cnt * ABS(x - y) % n;
			if(!cnt) break;
			x = F(x , c , n) , y = F(F(y , c , n) , c , n);
		}
		ll d = gcd(cnt , n);
		if(d != 1) return d;
	}
	return n;
}
ll ans;
inline void MAX(ll z){if(z > ans) ans = z;}
void dfs(ll n)//非质数 
{
	ll d = pr(n);
	while(d == n) d = pr(n);
	ll d2 = n / d;
	if(mr(d)) MAX(d);
	else dfs(d);
	if(mr(d2)) MAX(d2);
	else dfs(d2);
}
ll getans(ll x)
{
	if(mr(x)) return x;
	ans = 0;
	dfs(x);
	return ans;
}
int main()
{
	// srand(time(0));
	// int T;scanf("%d",&T);
	// while(T --)
	// {
	// 	ll x;scanf("%lld",&x);
	// 	ll res = getans(x);
	// 	if(x == res) puts("Prime");
	// 	else printf("%lld\n",res);
	// }
    int t; long long n;
    scanf("%d%lld", &t, &n);
    mr(n);
	return 0;
}