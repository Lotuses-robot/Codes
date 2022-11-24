#include<bits/stdc++.h>

using namespace std;

bool vis[31];
int T,n,m;

int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		if(m>=30){puts("Yes");continue;}
		memset(vis,0,sizeof(vis));
		bool bk=0;
		for(int i=1;i<=m;i++)
		{
			if(vis[n%i]){bk=1;break;}
			vis[n%i]=1;
		}
		if(bk)puts("Yes");
		else puts("No");
	}
}