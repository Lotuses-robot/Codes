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
vector<int> pro[1000005];
bool pd[1000005];
int main()
{
	freopen("discuss.in","r",stdin);
	freopen("discuss.out","w",stdout);
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=1;i<=n;i++)
		{
			int k=read();
			for(int j=1;j<=k;j++) pro[j].emplace_back(read());
		}
		bool solve=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				memset(pd,0,sizeof(pd));
				for(int k=0;k<pro[i].size();k++) pd[pro[i][k]]=1;
				bool flag=0;
				for(int k=0;k<pro[j].size();k++)
					if(pd[pro[j][k]])
					{
						flag=1;
						break;
					}
				if(!flag) continue;
				flag=0;
				for(int k=0;k<pro[j].size();k++)
					if(!pd[pro[j][k]])
					{
						flag=1;
						break;
					}
				if(!flag) continue;
				memset(pd,0,sizeof(pd));
				for(int k=0;k<pro[j].size();k++) pd[pro[j][k]]=1;
				flag=0;
				for(int k=0;k<pro[i].size();k++)
					if(!pd[pro[i][k]])
					{
						flag=1;
						break;
					}
				if(!flag) continue;
				puts("YES");
				write(i);putchar(' ');write(j);putchar('\n');
				solve=1;
				break;
			}
			if(solve) break;
		}
		if(!solve) puts("NO");
	}
	return 0;
}
