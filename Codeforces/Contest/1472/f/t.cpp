#include<bits/stdc++.h>
#define lot signed
// #define int long long
#define dg(a) ((a)<'0'||(a)>'9')
using namespace std;

void read(int &r)
{
    r=0;char ch,f='t';ch=getchar();
    while(dg(ch)){f=ch;ch=getchar();}
    while(!dg(ch)){r=(r<<3)+(r<<1)+ch-'0';ch=getchar();}
    if(f=='-')r=-r;
}

#define Max 200010

int T,n,m,dp[Max][3];
struct node{int x,y;}a[Max];

bool operator==(node _a,node _b)
{
    if(_a.x!=_b.x)return 0;
    else if(_a.y!=_b.y)return 0;
    return 1;
}

bool cmp(node _a,node _b)
{
    if(_a.y!=_b.y)return _a.y<_b.y;
    else return _a.x<_b.x;
}

lot main()
{
    freopen(".in","r",stdin);
    freopen(".ans","w",stdout);
    read(T);
    dp[0][0]=1;
    while(T--)
    {
        read(n);read(m);
        for(int i=1;i<=m;i++)
        {
            read(a[i].x);read(a[i].y);
        }
        sort(a+1,a+m+1,cmp);
        m=unique(a+1,a+m+1)-a+1;
        for(int i=1;i<=m;i++)dp[i][0]=dp[i][1]=dp[i][2]=0;
        for(int i=1;i<=m;i++)
        {
            if(!((a[i].y-a[i-1].y)&1))swap(dp[i-1][1],dp[i-1][2]);
            if(a[i].y==a[i+1].y)
            {
                i++;
                dp[i][0]|=dp[i-2][0];
            }
            else if(a[i].x==1)
            {
                dp[i][2]|=dp[i-1][0];
                dp[i][0]|=dp[i-1][2];
            }
            else
            {
                dp[i][1]|=dp[i-1][0];
                dp[i][0]|=dp[i-1][1];
            }
        }
        if(dp[m][0])puts("YES");
        else puts("NO");
    }
    return 0;
}