#include<bits/stdc++.h>
#define int long long
#define maxn 1000000
using namespace std;
vector<int> ans;
int n,m,k;
bool ss[maxn+1];
int ys[maxn+1];
bool pf[maxn+1];

// char chr[50];
bool check1(int t)
{
    // sprintf(chr,"%d",t);
    // int tot=0;
    // for(int i=0;i<strlen(chr);i++)
        // if((chr[i]-'0')%2==0) tot++;
    // cout<<tot<<endl;
    int tot=0;
    do
    {
        tot+=((t%10)%2)^1;
    }
    while(t/=10);

    return tot==m;
}

bool check2(int t)
{
    return ys[t]==k;
}

void init_ss()
{
    ss[1]=1;
    for(int i=2;i<=maxn;i++)
        if(!ss[i])
            for(int j=i*2;j<=maxn;j+=i)
                ss[j]=1;
}

void dfs(int x)
{
    for(int j=2;x*j<=maxn;j++)
    {
        if(ys[j*x]||ss[j]) {continue;}
        if(pf[x*j]) ys[x*j]=ys[x]+1;
        else
        {
            int tot=2,cx=x;
            while(cx%j==0) cx/=j,tot++;
            ys[x*j]=ys[cx]*tot;
        }
        dfs(x*j);
    }
}

void init_ys()
{
    for(int i=1;i<=maxn;i++)
        if(!ss[i])
        {
            ys[i]=2;
            for(long long j=1ll*i*i,k=3;j<=maxn;j*=i,k++) pf[j]=1;
            dfs(i);
        }
}

const double eps=1e-5;

signed main()
{
    init_ss();
    init_ys();
    int T;
    scanf("%lld",&T);
    while(T--)
    {
        ans.clear();
        scanf("%lld%lld%lld",&n,&m,&k);
        for(int i=(int)(pow(10,n-1)+eps);i<=(int)(pow(10,n)+eps-1);i++)
            if(check1(i)&&check2(i)) ans.push_back(i);
        
        if(ans.size()!=0) cout<<ans.size()<<endl;
        else cout<<-1<<endl;
        for(auto i:ans) cout<<i<<endl;
    }
}