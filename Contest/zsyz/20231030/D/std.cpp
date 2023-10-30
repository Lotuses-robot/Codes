#include<bits/stdc++.h>
#define Max 100010
#define Maxn 10000100
#define dg(a) ((a)<'0'||(a)>'9')
using namespace std;

int n,m,tot;
int lst[Max],len;
int dp[Max],siz[Max],rt;

int ans;
bool vis[Max];
int pd[Maxn],qst[Max];

struct node{int x,y,res;}a[Max],val[Max];
struct edge{int x,y,nxt;}p[Max<<1];
char s[Max];
node operator +(node _a,node _b)
{
    return (node){_a.x+_b.x,_a.y+_b.y,_a.res};
}
bool operator <(node _a,node _b)
{
    if(_a.x!=_b.x)return _a.x<_b.x;
    else if(_a.y!=_b.y)return _a.y<_b.y;
    else return _a.res<_b.res;
}

void read(int &r)
{
	r=0;char ch,f='t';ch=getchar();
	while(dg(ch)){f=ch;ch=getchar();}
	while(!dg(ch)){r=(r<<3)+(r<<1)+ch-'0';ch=getchar();}
	if(f=='-')r=-r;
}

void find(int x,int fa,int res)
{
	dp[x]=0;siz[x]=0; 
	for(int k=lst[x];k;k=p[k].nxt)
	{
		int y=p[k].y;
		if(y==fa||vis[y])continue;
		find(y,x,res);
		siz[x]+=siz[y];
		dp[x]=max(dp[x],siz[y]);
	}
	siz[x]++;
	dp[x]=max(dp[x],res-siz[x]);
	if(dp[x]<dp[rt])rt=x;
}//find siz and dp

void road(int x,int fa,node dis)
{
	val[++tot]=dis;
	for(int k=lst[x];k;k=p[k].nxt)
	{
		int y=p[k].y;
		if(y==fa||vis[y])continue;
		road(y,x,dis+a[y]);
	}
}

void solve(int x)
{
	vis[x]=1;tot=0;
	val[++tot]={0,0,0};
	for(int k=lst[x];k;k=p[k].nxt)
	{
		int y=p[k].y;
		if(vis[y])continue;
		road(y,0,(node){a[y].x,a[y].y,y});
	}
    sort(val+1,val+tot+1);
    for(int i=1;i<=tot;i++)
    {
        int t=0;node p;
        p.x=-val[i].x-a[x].x;
        p.y=-val[i].y-a[x].y;
        t=upper_bound(val+1,val+tot+1,(node){p.x,p.y,Max})-lower_bound(val+1,val+tot+1,(node){p.x,p.y,val[i].res+1});
        // t-=upper_bound(val+1,val+tot+1,(node){p.x,p.y,val[i].res})-lower_bound(val+1,val+tot+1,(node){p.x,p.y,val[i].res});
        ans+=t;
    }
	for(int k=lst[x];k;k=p[k].nxt)
	{
		int y=p[k].y;
		if(vis[y])continue;
		rt=0;find(y,x,siz[y]);solve(rt);
	}
}

void ins(int x,int y)
{
	len++;
	p[len].x=x;p[len].y=y;
	p[len].nxt=lst[x];lst[x]=len;
}

signed main()
{
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
	dp[0]=1e9;
	read(n);
    scanf("%s",s+1);
    int ls=strlen(s+1);
    for(int i=1;i<=ls;i++)
    {
        if(s[i]=='a')a[i].x=a[i].y=-1;
        else if(s[i]=='b')a[i].x=1;
        else a[i].y=1;
    }
	for(int i=1;i<n;i++)
	{
		int x,y;
		read(x);read(y);
		ins(x,y);ins(y,x);
	}
	find(1,0,n);
	solve(rt);
    printf("%lld\n",ans);
	return 0;
}
