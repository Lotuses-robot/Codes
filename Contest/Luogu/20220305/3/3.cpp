#include<bits/stdc++.h>
#define int long long
#define mod 19260817
using namespace std;
int s[10001];

signed main()
{
    int n,m;
    int l,r,x,op;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=1;i<=m;i++) 
    {
        cin>>op;
        if(op==1)
        {
            cin>>l>>r>>x;
            for(int i=l;i<=r;i++)
                s[i]/=x,s[i]*=x;
        }
        else
        {
            x=0;
            cin>>l>>r;
            for(int i=l;i<=r;i++) x+=s[i],x%=mod;
            cout<<x<<endl;
        }
    }
    return 0;
}