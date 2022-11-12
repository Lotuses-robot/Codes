#include<bits/stdc++.h>
#define maxn 1000000
using namespace std;
bool ss[maxn+1];
int ys[maxn+1];
bool pf[maxn+1];

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
    // cout<<x<<endl;
    for(int j=2;x*j<=maxn;j++)
    {
        if(ys[j*x]||ss[j]) {continue;}
        if(pf[x*j]) ys[x*j]=ys[x]+1;
        // else if(x%j==0) ys[x*j]=ys[x]+2;
        // else ys[x*j]=ys[x]*2;
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
            // cout<<i<<endl;
        }
}

int main()
{
    init_ss();
    init_ys();
}