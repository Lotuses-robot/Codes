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
int a[100005],b[100005];
stack<int> st;
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	int n=read(),q=read();
	bool flag=1;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++)
	{
		b[i]=read();
		if(b[i]!=n-i+1) flag=0;
	}
	if(flag)
	{
		while(q--)
		{
			int l=read(),r=read();
			write(r-l+1);
			putchar('\n');
		}
		return 0;
	}
	while(q--)
	{
		int l=read(),r=read(),ans=0;
		for(int i=l;i<=r;i++)
		{
			while(!st.empty())
			{
				if(a[i]!=a[st.top()]&&b[i]<b[st.top()]) break;
				st.pop();
			}
			if(st.empty()) ans++;
			st.push(i);
		}
		write(ans);
		putchar('\n');
		while(!st.empty()) st.pop();
	}
	return 0;
}
