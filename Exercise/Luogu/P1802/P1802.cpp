#include<bits/stdc++.h>
using namespace std;
long long f[1001][1001];
struct Node{
    int l,w,u;
}cp[1001];

int main()
{
    int n,x;
    cin>>n>>x;
    for(int i=1;i<=n;i++) cin>>cp[i].l>>cp[i].w>>cp[i].u;

    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=x-cp[i].u;j++) f[i][j]=max(f[i-1][j]+cp[i].l,f[i-1][j+cp[i].u]+cp[i].w);
        for(int j=x-cp[i].u+1;j<=x;j++) f[i][j]=f[i-1][j]+cp[i].l;
    }

    long long ans=-1;
    for(int j=0;j<=x;j++) ans=max(ans,f[n][j]);
    cout<<ans*5<<endl;
    return 0;
}