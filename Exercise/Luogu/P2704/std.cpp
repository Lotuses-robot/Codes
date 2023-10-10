#include<iostream>
using namespace std;
int n,m,ans,dp[(1<<10)][(1<<10)][3]/*滚动数组*/,a[105],Sum[(1<<10)];
char x;
int getsum(int S)	//当前状态 S 里面包含几个 1
{
	int tot=0;
	while(S) {if(S&1) tot++; S>>=1;}
	return tot;
}
int main()
{
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>x,a[i]<<=1,a[i]+=(x=='H'?1:0);	//转成二进制数
	for(int i=0;i<(1<<m);i++)
		Sum[i]=getsum(i);	//初始化 Sum 数组
	for(int S=0;S<(1<<m);S++)
		if(!(S&a[0] || (S&(S<<1)) || (S&(S<<2))))
			dp[0][S][0]=Sum[S];	//初始化
	for(int L=0;L<(1<<m);L++)
		for(int S=0;S<(1<<m);S++)
			if(!(L&S || L&a[0] || S&a[1] || (L&(L<<1)) || (L&(L<<2)) || (S&(S<<1)) || (S&(S<<2))))	//谜之一长串特判
				dp[L][S][1]=Sum[S]+Sum[L];
	for(int i=2;i<n;i++)
		for(int L=0;L<(1<<m);L++)
		{
			if(L&a[i-1] || (L&(L<<1)) || (L&(L<<2))) continue;	//特判
			for(int S=0;S<(1<<m);S++)
			{
				if(S&a[i] || L&S || (S&(S<<1)) || (S&(S<<2))) continue;
				for(int FL=0;FL<(1<<m);FL++)
				{
					if(FL&L || FL&S || FL&a[i-2] || (FL&(FL<<1)) || (FL&(FL<<2)))	continue;
					dp[L][S][i%3]=max(dp[L][S][i%3],dp[FL][L][(i-1)%3]+Sum[S]);		//滚动数组的实现方法
				}
			}
		}
	for(int L=0;L<(1<<m);L++)
		for(int S=0;S<(1<<m);S++)
			ans=max(ans,dp[L][S][(n-1)%3]);	//结束状态可以是最后一行的任何状态
	cout<<ans;
	return 0;
}
