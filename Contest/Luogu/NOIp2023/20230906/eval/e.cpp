// Copyright 2023 Lotuses
#include<bits/stdc++.h>

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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define Max 5100
// #define mod 100000007
#define int long long
using namespace std;

const int mod = 1e9 + 7;
char a[Max * 5];
int ans[Max * 5],ct;
int s[Max * 5],n,cnt,tot;
int f[Max][Max],dp[Max][Max];
int lst[Max * 5],rgt[Max * 5],fac[Max * 5];

signed main()
{
	scanf("%s",a+1);
	n=strlen(a+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='(')s[++cnt]=i;
		else if(a[i]==')')rgt[s[cnt--]]=i;
		else if(a[i]=='x')rgt[i]=i,ct++;
	}
	f[0][ct+1]=1;fac[0]=1;
	for(int i=1;i<=10005;i++)fac[i]=(fac[i-1]*i)%mod;
	for(int i=1;i<=ct;i++)
	{
		int t=0;
		for(int j=ct;j>=1;j--)
		{
			t=(f[i-1][j+1]+t)%mod;
			f[i][j]=t*j%mod;
			ans[i]=(ans[i]+f[i][j])%mod;
		}
        ans[i] = ans[i] * fac[i] % mod * fac[ct - i] % mod;
        // writeln(ans[i]);
    }
	cnt=0;rgt[0]=n+1;
    int sum = 0, cntx = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 'x') {
            cntx++;
        } else if (a[i] == '+') {
            (sum += ans[cntx]) %= mod;
            cntx = 0;
        }
    }
    if (cntx) (sum += ans[cntx]) %= mod;
    printf("%lld\n", sum);
	// for(int i=1;i<=n;i++)
	// {
	// 	tot=(tot+dp[n+1][i]*ans[i]%mod)%mod;
	// }
	// printf("%lld",tot);
	return 0;
}
