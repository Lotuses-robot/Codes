#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar(),last=0;int s=0;
	while(ch<'0'||ch>'9') last=ch,ch=getchar();
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return last=='-'?-s:s;
}
inline void write(int x)
{
	char buf[20];int len=0;
	do buf[len++]=x%10+'0';while(x/=10);
	while(len--) putchar(buf[len]);
}
int a[5][200005];
int main()
{
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	int m=read(),n=read();
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			a[i][j]=read();
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			int maxx=-1,minn=1e9;
			for(int k=1;k<=m;k++)
			{
				maxx=max(maxx,a[k][i]+a[k][j]);
				minn=min(minn,a[k][i]+a[k][j]);
			}
			ans+=maxx+minn<<1;
		}
	for(int i=1;i<=n;i++)
	{
		int maxx=-1,minn=1e9;
		for(int j=1;j<=m;j++)
		{
			maxx=max(maxx,a[j][i]);
			minn=min(minn,a[j][i]);
		}
		ans+=maxx+minn<<1;
	}
	write(ans);
	return 0;
}
