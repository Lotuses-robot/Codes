// LUOGU_RID: 131905453
#include<bits/stdc++.h>
#define lot signed
#define Max 200100
#define int long long
#define dg(a) ((a)<'0'||(a)>'9')
using namespace std;

void read(int &r)
{
    r=0;char ch,f='t';ch=getchar();
    while(dg(ch)){f=ch;ch=getchar();}
    while(!dg(ch)){r=(r<<3)+(r<<1)+ch-'0';ch=getchar();}
    if(f=='-')r=-r;
}

int n;
struct node{int x,l,r;}p[Max];
bool cmp(node _a,node _b){return _a.l<_b.l;}
bool operator<(node _a,node _b){return _a.r>_b.r;}
priority_queue<node>q;

bool check(int x)
{
    int pos=0;
    while(!q.empty())q.pop();
    for(int i=1;i<=n;i++)
    {
        while(pos<n&&p[pos+1].l<=i)
        {
            pos++;q.push(p[pos]);
        }
        int tot=x;
        while(tot&&!q.empty())
        {
            node u=q.top();q.pop();
            if(tot>=u.x)tot-=u.x;
            else
            {
                u.x-=tot;tot=0;
                q.push(u);
            }
        }
        while(!q.empty()&&!q.top().x)q.pop();
        if(!q.empty()&&q.top().r<=i)return 0;
    }
    if(!q.empty())return 0;
    return 1;
}

lot main()
{
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
    read(n);
    for(int i=1;i<=n;i++)read(p[i].x);
    for(int i=1;i<=n;i++)
    {
        int x;read(x);
        p[i].l=i-x;p[i].r=i+x;
    }
    sort(p+1,p+n+1,cmp);
    int l=0,r=1e9,x=1e9,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(check(mid)){x=mid;r=mid-1;}
        else l=mid+1;
    }
    printf("%lld\n",x);
    return 0;
}