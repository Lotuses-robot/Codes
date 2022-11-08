#include<bits/stdc++.h>
#define LL long long
#define int long long
using namespace std;
LL a[110000],p;
struct node
{
	int l,r,lc,rc;
	LL c,s2,s3,s4,s5;
	vector<LL> lazy;
}tr[210000];
int len=0;
LL read()
{
	LL r=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=r*10+ch-'0';ch=getchar();}
	return r*f;
}
int build(int l,int r)
{
	len++;
	int now=len;
	int lc=-1,rc=-1;
	LL c=(LL)0;
	LL s2=0,s3=0,s4=0,s5=0;
	if(l!=r)
	{
		int mid=(l+r)/2;
		lc=build(l,mid);
		rc=build(mid+1,r);
		c=tr[lc].c+tr[rc].c;
		s2=tr[lc].s2+tr[rc].s2;
		s3=tr[lc].s3+tr[rc].s3;
		s4=tr[lc].s4+tr[rc].s4;
		s5=tr[lc].s5+tr[rc].s5;
	}
	else c=a[l],s2=a[l]%2,s3=a[l]%3,s4=a[l]%4,s5=a[l]%5;
	tr[now]={l,r,lc,rc,c,s2,s3,s4,s5,{}};
	return now;
}
void lazydown(int now)
{ 
	// int lc=tr[now].lc,rc=tr[now].rc;
	// if(lc==-1||rc==-1)return;
	// tr[rc].lazy+=tr[now].lazy;
	// tr[lc].lazy+=tr[now].lazy;
	// tr[lc].lazy%=p;tr[rc].lazy%=p;
	// tr[lc].c+=tr[now].lazy*((LL)tr[lc].r-tr[lc].l+1);
	// tr[rc].c+=tr[now].lazy*((LL)tr[rc].r-tr[rc].l+1);
	// tr[rc].c%=p;tr[lc].c%=p;
	// tr[now].lazy=0;
	int lc=tr[now].lc,rc=tr[now].rc;
	if(lc==-1||rc==-1||tr[now].lazy.empty()) return;
	for(auto lazy:tr[now].lazy)
	{
		tr[lc].lazy.push_back(lazy);
		tr[rc].lazy.push_back(lazy);

		int zz;
		if(lazy==2) zz=tr[lc].s2;
		if(lazy==3) zz=tr[lc].s3;
		if(lazy==4) zz=tr[lc].s4;
		if(lazy==5) zz=tr[lc].s5;

		tr[lc].c-=zz;
		tr[lc].s2-=zz;
		tr[lc].s3-=zz;
		tr[lc].s4-=zz;
		tr[lc].s5-=zz;

		if(lazy==2) zz=tr[rc].s2;
		if(lazy==3) zz=tr[rc].s3;
		if(lazy==4) zz=tr[rc].s4;
		if(lazy==5) zz=tr[rc].s5;

		tr[rc].c-=zz;
		tr[rc].s2-=zz;
		tr[rc].s3-=zz;
		tr[rc].s4-=zz;
		tr[rc].s5-=zz;
	}
	tr[now].lazy.clear();
}
void change1(int now,int x,int y,LL z)
{
	int l=tr[now].l,r=tr[now].r,lc=tr[now].lc,rc=tr[now].rc;
	if(l==x&&r==y)
	{
		int zz;
		if(z==2) zz=tr[now].s2;
		if(z==3) zz=tr[now].s3;
		if(z==4) zz=tr[now].s4;
		if(z==5) zz=tr[now].s5;
		tr[now].c-=zz;
		tr[now].lazy.push_back(z);
		tr[now].c%=p;
		return;
	}
	lazydown(now);
	int mid=(l+r)>>1;
	if(y<=mid)change1(lc,x,y,z);
	else if(x>mid)change1(rc,x,y,z);
	else {change1(lc,x,mid,z);change1(rc,mid+1,y,z);}
	tr[now].c=tr[lc].c+tr[rc].c;
	tr[now].s2=tr[lc].s2+tr[rc].s2;
	tr[now].s3=tr[lc].s3+tr[rc].s3;
	tr[now].s4=tr[lc].s4+tr[rc].s4;
	tr[now].s5=tr[lc].s5+tr[rc].s5;
	
	tr[now].c%=p;
}
LL find(int now,int x,int y)
{
	lazydown(now);
	int l=tr[now].l,r=tr[now].r,lc=tr[now].lc,rc=tr[now].rc;
	if(l==x&&r==y)return tr[now].c;
	int mid=(l+r)>>1;
	if(y<=mid)return find(lc,x,y)%p;
	else if(x>mid)return find(rc,x,y)%p;
	else {return (find(lc,x,mid)+find(rc,mid+1,y))%p;}
}
signed main()
{
	int n,m;
	n=read();m=read();p=19260817;
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,n);
	for(int i=1;i<=m;i++)
	{
		int k,x,y;
		k=read();x=read();y=read();
		if(x>y)swap(x,y);
		if(k==1)
		{
			LL z;
			z=read();
			change1(1,x,y,z);
		}
		else printf("%lld\n",find(1,x,y)%p);
	}
	return 0;
}