#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[501],b[501];
int f[501][2001];

int s(int n)
{
    if(n<0) return 0;
    return n*(n+1)*(2*n+1)/6;
}

main()
{
    int n,m,t;
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    memset(f,127,sizeof(f));
    // memset(f[1],0,sizeof(f[1]));
    f[1][0]=0;
    for(int i=2;i<=n+1;i++)
        for(int j=0;j<=m;j++)
            for(int l=0;l<=j;l++)
            {
                // cout<<i<<" "<<j<<" "<<l<<" "<<f[i-1][j-l]<<" "<<a[i-1]*l<<" "<<b[i-1]<<" "<<s(l-1)<<" "<<(l==0||i==n+1? 0:t)<<" "<<f[i-1][j-l]+a[i-1]*l+b[i-1]*s(l-1)+(l==0||i==n+1? 0:t)<<endl;
                f[i][j]=min(f[i][j],f[i-1][j-l]+a[i-1]*l+b[i-1]*s(l-1)+(j==10||l==0||i==n+1? 0:t));
            }
    
    cout<<f[n+1][m]<<endl;
    return 0;
}