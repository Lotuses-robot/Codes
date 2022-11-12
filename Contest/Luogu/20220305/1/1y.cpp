#include<bits/stdc++.h>
#define maxn 1000000
using namespace std;
bool ss[maxn+1];
int ys[maxn+1];
bool pf[maxn+1];
int it[maxn+1];

long long dcp(long long x){
    long long i,ans = 1;
    for(i = 2; i * i <= x; i++){
        if(x % i == 0){
            long long temp = 0;
            while(x % i == 0){
                x /= i;
                temp++;
            }
            ans *= (temp+1);
        }
    }
    if(x > 1) ans *= 2;
    return ans;
}

void init()
{
    it[1]=1;
    for(int i=2;i<=maxn;i++)
        if(it[i]==0) it[i]=dcp(i);
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
    ys[1]=1;
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
    init();
    init_ss();
    init_ys();
    // puts("???");
    for(int i=1;i<=maxn;i++)
        if(it[i]!=ys[i]) cout<<i<<" "<<it[i]<<" "<<ys[i]<<endl;
}