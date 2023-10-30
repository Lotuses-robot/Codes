#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[300001],b[300001];
int c[300001],p[300001];
int fib[300001];
int n,q,mod,tot=0;

void init()
{
    fib[1]=1;fib[2]=1;
    for(int i=3;i<=300001;i++) fib[i]=fib[i-1]+fib[i-2],fib[i]%=mod;
}

void plus_m(int pos,int pl)
{
    pl=(pl%mod+mod)%mod;
    if(pos>n||pl==0) return;


    if(p[pos]==0) tot++;
    p[pos]+=pl;p[pos]%=mod;
    if(p[pos]==0) tot--;
}

signed main()
{
    cin>>n>>q>>mod;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i],c[i]=b[i]-a[i];
    p[1]=c[1];p[1]=(p[1]%mod+mod)%mod;p[2]=c[2]-c[1];p[2]=(p[2]%mod+mod)%mod;
    for(int i=3;i<=n;i++) p[i]=c[i]-c[i-1]-c[i-2],p[i]=(p[i]%mod+mod)%mod,tot+=(p[i]!=0);
    // puts("ok");
    init();
    while(q--)
    {
        char c;int l,r;
        cin>>c>>l>>r;
        if(c=='A')
        {
            plus_m(l,fib[1]);
            plus_m(r+1,-fib[r-l+2]);
            plus_m(r+2,-fib[r-l+1]);
            if(tot==0) cout<<"YES\n";
            else cout<<"NO\n";
        }
        else
        {
            plus_m(l,-fib[1]);
            plus_m(r+1,fib[r-l+2]);
            plus_m(r+2,fib[r-l+1]);
            if(tot==0) cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}