#include<bits/stdc++.h>
#define Max 5010
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
	for(int i=1;i<=n;i++)fac[i]=(fac[i-1]*i)%mod;
	for(int i=1;i<=ct;i++)
	{
		int t=0;
		for(int j=ct;j>=1;j--)
		{
			t=(f[i-1][j+1]+t)%mod;
			f[i][j]=t*j%mod;
			ans[i]=(ans[i]+f[i][j])%mod;
		}
		ans[i]=ans[i]*fac[i]%mod*fac[ct-i]%mod;
	}
	cnt=0;rgt[0]=n+1;
    int sum = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 'x') {
            cnt++;
        } else if (a[i] == '+') {
            sum += ans[cnt] %= mod;
            cnt = 0;
        }
    }
    if (cnt) sum += ans[cnt] %= mod;
    printf("%lld\n", sum);
	// for(int i=1;i<=n;i++)
	// {
	// 	tot=(tot+dp[n+1][i]*ans[i]%mod)%mod;
	// }
	// printf("%lld",tot);
	return 0;
}