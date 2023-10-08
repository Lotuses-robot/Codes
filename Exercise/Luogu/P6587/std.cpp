#include<bits/stdc++.h>
#define ls (root<<1) 
#define rs (root<<1|1)
#define mid (l+r>>1)
#define min(a,b) (a<b?a:b)
using namespace std;
const int Maxn=2e6+5;
inline int R()
{
	char c;int sign=1,res=0;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res+=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;	
}
#define int long long 
int a[Maxn],n,m,sum[Maxn*4],N=1,NN=0,ADD[Maxn*4],size[Maxn*4];
void add(int root,int val)
{
	sum[root]+=size[root]*val;
	ADD[root]+=val;
}
void pushdown(int root)
{
	if(ADD[root])
	{
		add(ls,ADD[root]);
		add(rs,ADD[root]);
		ADD[root]=0;
	}
}
void build(int root,int deep,int sur)
{
	if(deep==NN) 
	{
		sum[root]=a[sur];
		size[root]=(sur<=n);
		return;
	}
	build(ls,deep+1,sur);
	build(rs,deep+1,sur+(1<<deep));
	sum[root]=sum[ls]+sum[rs];
	size[root]=size[ls]+size[rs];
}
void modify(int root,int deep,int arr,int sur,int value)
{
	if(deep==arr&&sur!=0) return;
	pushdown(root);
	if(deep==arr) return add(root,value);
	if(sur&1) modify(rs,deep+1,arr,sur>>1,value);
	else  modify(ls,deep+1,arr,sur>>1,value);
	sum[root]=sum[ls]+sum[rs];
}
int query(int root,int deep,int arr,int sur)
{
	if(deep==arr&&sur!=0) return 0;
	pushdown(root);
	if(deep==arr) return sum[root];
	if(sur&1) return query(rs,deep+1,arr,sur>>1);
	else return query(ls,deep+1,arr,sur>>1);
}
signed main()
{
	n=R();m=R();
	while(N<=n) N<<=1,NN++; 
	for(int i=1;i<=n;i++) a[i]=R();
	build(1,0,1);
	int op,p,k,pre=0;
	while(m--)
	{
		op=R();p=R();k=R();
		if(op==1)//修改 
		{
			int v=R();
			if(k!=0)modify(1,0,min(NN,p),k-1,v);
			else modify(1,0,min(NN,p),(1<<(min(NN,p)))-1,v);
		}
		else if(k!=0)printf("%lld\n",pre=query(1,0,min(NN,p),k-1));
		else printf("%lld\n",pre=query(1,0,min(NN,p),(1<<(min(NN,p)))-1));
	}
}