#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,T,x,y,b[100005],r;
char ch1[10005],ch2[200005];
int f[105][10005];//第i个箱子，已经装了 j,这个箱子装 k 的最大收益 
signed main()
{
    freopen("data.in", "r", stdin);
    freopen("data.ans", "w", stdout);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld",&n,&x,&y,&r);
		int sum=0;
		for(int i=1;i<=n;i++)
		scanf("%lld",&b[i]),sum+=b[i];
		for(int i=0;i<=n;i++)
		for(int j=0;j<=sum;j++)
		f[i][j]=-1e9;
		f[0][0]=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=sum;j++)
			{
//				f[i][j]=f[i-1][j];
				for(int k=0;k<=b[i];k+=x)
				if(j>=k)
				f[i][j]=max(f[i][j],f[i-1][j-k]+(b[i]-k)*(b[i]-k));
				for(int k=0;k<=b[i];k+=y)
				if(j>=k)
				f[i][j]=max(f[i][j],f[i-1][j-k]+(b[i]-k)*(b[i]-k));
			}
			for(int j=0;j<=sum;j++)
			{
				for(int k=0;k<=b[i];k++)
				if(j>=k&&f[i][j-k]>=0&&((k>=x&&f[i-1][k-x]>=0)||(k>=y&&f[i-1][k-y]>=0)))f[i][j]=max(f[i][j],f[i-1][j-k]+(b[i]-k)*(b[i]-k));
			}
		}
		int maxx=-1e9;
		for(int i=1;i<=n;i++)
		for(int j=0;j<=sum;j++)
		printf("%d %d %d\n",i,j,f[i][j]);
		for(int i=r;i<=sum;i++)
		maxx=max(maxx,f[n][i]);
		printf("%lld\n",maxx<0?-1:maxx);
	}
	return 0;
}