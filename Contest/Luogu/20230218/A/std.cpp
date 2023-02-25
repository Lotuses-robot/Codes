#include<bits/stdc++.h>
#define int long long

using namespace std;

int T,n,k,a,b;
int len,mod,ans;
bool v[200001];

signed main()
{
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d",&n,&k,&a,&b);
		for(int i=1;i<=n;i++)v[i]=0;
		int t=1;ans=0;
		while(t+k-1<=n)
		{
			int r=min(t+2*k-3,n);
			if(a>b*(r-t-k+2))ans+=b*(r-t-k+2);
			else 
			{
				ans+=a;
				v[t+k-1]=1;
			}
			t=t+k-1;
		}
        int fuck = 1;
		printf("%lld\n",ans);
		for(int i=1;i<=n;i++)
		{
			if(!v[i]) fuck ^= 1;
			printf("%c",fuck+'a');
		}
		puts("");
	}
	return 0;
}