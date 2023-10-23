#include<bits/stdc++.h>
using namespace std;
const int mx=2e5+5; 
const int mod=998244353;
int a[mx];
int bl[mx],fl[mx],fr[mx];
int s[mx],tag[mx],mn[mx],os[mx];
int pow2[mx];
int n,b,ks;
void init()
{
	int i,j,k,mx;
	b=sqrt(n);
	for(i=1;i-1+b<=n;i+=b)
		fl[++ks]=i,fr[ks]=i-1+b;
	if(i<=n)
		fl[++ks]=i,fr[ks]=n;
	for(i=1;i<=ks;i++)
		for(j=fl[i];j<=fr[i];j++)
			bl[j]=i;
}
int qpow(int a,int p,int mod)
{
	if(p==0) return 1;
	if(p==1) return a;
	long long t=qpow(a,p/2,mod);
	return t*t%mod*qpow(a,p%2,mod)%mod;
}
int read()
{
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s;
}
void cg(int x)
{
	mn[x]=2e9;
	for(int i=fl[x];i<=fr[x];i++)
		mn[x]=min(mn[x],s[i]+tag[x]);
}
void zk(int x)
{
	for(int i=fl[x];i<=fr[x];i++)
		s[i]+=tag[x];
	tag[x]=0;
}
void add(int l,int r)
{
	if(bl[l]==bl[r])
	{
		zk(bl[l]);
		for(;l<=r;l++)
			s[l]++;
		cg(bl[l-1]);
		return;
	}
	add(l,fr[bl[l]]),add(fl[bl[r]],r);
	int i;
	for(i=bl[l]+1;i<bl[r];i++)
		tag[i]++,mn[i]++;
}
void sqrt(int l,int r)
{
	if(bl[l]==bl[r])
	{
		zk(bl[l]);
		for(;l<=r;l++)
		{
			if(a[l]==1) continue;
			if(s[l]==0) 
			{
				a[l]=sqrt(a[l]);
				os[bl[l]]+=a[l]==1;
			}
			else s[l]--;
		}
		cg(bl[l-1]);	
		return;
	}
	sqrt(l,fr[bl[l]]),sqrt(fl[bl[r]],r);
	for(int i=bl[l]+1;i<bl[r];i++)
	{
		if(os[i]==fr[i]-fl[i]+1) continue;
		if(mn[i]==0)
			sqrt(fl[i],fr[i]);		
		else
			mn[i]--,tag[i]--;	
	}				
}
int main()
{
	freopen(".in", "r", stdin);
	freopen(".ans", "w", stdout);
	int m,i,opt,l,r,sum=0,wz=2e9,qwq;
	n=read(),m=read();
	init();
	pow2[0]=1;
	for(i=1;i<=n;i++)
		a[i]=read();
	for(i=1;i<=m;i++)
	{
		pow2[i]=pow2[i-1]*2;
		if(pow2[i]>=mod-1&&wz==2e9) wz=i;
		pow2[i]%=mod-1;
	}
	while(m--)
	{
		opt=read(),l=read(),r=read();
		if(opt==1) sqrt(l,r);
		else add(l,r);
	}
	for(i=1;i<=ks;i++)
		zk(i);
	for(i=1;i<=n;i++)
	{
		if(a[i]==1)
		{
			sum=(sum+1)%mod;
			continue;
		}
		qwq=pow2[s[i]];
		if(s[i]>=wz) qwq+=mod-1;
		sum=(sum+qpow(a[i],qwq,mod))%mod;	
	}
	cout<<sum%mod;
} 
