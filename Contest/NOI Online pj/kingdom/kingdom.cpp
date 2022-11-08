#include<bits/stdc++.h>
using namespace std;
int tot[1001];

char ch,last;
template<typename T>
#define gc getchar()
#define isd(x) ((x)>='0'&&(x)<='9')
void read(T&r)
{
    r=0;ch=gc;last='z';
    while(!isd(ch)) last=ch,ch=gc;
    while(isd(ch)) r=(r<<1)+(r<<3)+(ch^48),ch=gc;
    if(last=='-') r=-r;
}

int main()
{
    freopen("kingdom.in","r",stdin);
    freopen("kingdom.out","w",stdout);
    int n,m,p,ans=0,ch;
    read(n),read(m);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++) read(p),tot[j]+=p;
    
    for(int j=1;j<=n;j++)
    {
        read(p);
        if(tot[j]>m-tot[j]) ch=1;
        else ch=0;
        if(p==ch) ans++;
    }
    cout<<ans<<endl;
    return 0;
}