#include<bits/stdc++.h>
#define tsz signed
#define ll long long
#define Max 11000100

using namespace std;

char ch[Max];

int n,ans1=1,ans2;
int base=131,mod=1e9+7;
int hsh1[Max],hsh2[Max],len1=base*base,len2=base;

int calc(ll x)
{
    if(x<=-mod)return x%mod+mod;
    if(x<0)return x+mod;
    if(x>=mod)return x%mod;
    return x;
}

bool check1(int i,int len)
{
    ll t,p;
    // cout<<i<<" "<<len<<endl;
    t=hsh1[i]-1ll*hsh1[i-len]*len1;
    p=hsh2[i]-1ll*hsh2[i+len]*len1;
    return calc(t)==calc(p);
}

bool check2(int i,int len)
{
    ll t,p;
    t=hsh1[i]-1ll*hsh1[i-len]*len2;
    p=hsh2[i+1]-1ll*hsh2[i+1+len]*len2;
    return calc(t)==calc(p);
}

int main()
{
    scanf("%s",ch+1);
    n=strlen(ch+1);
    for(int i=1;i<=n;i++)
    {
        hsh1[i]=(1ll*hsh1[i-1]*base+(ch[i]-'a'+1))%mod;
    }
    for(int i=n;i>=1;i--)
    {
        hsh2[i]=(1ll*hsh2[i+1]*base+(ch[i]-'a'+1))%mod;
    }
    for(int i=1;i<=n;i++)
    {
        while(i>ans1&&i+ans1<=n&&check1(i,ans1+1))
        {
            ans1++;
            len1=1ll*len1*base%mod;
        }
        while(i>ans2&&i+ans2+1<=n&&check2(i,ans2+1))
        {
            ans2++;
            len2=1ll*len2*base%mod;
        }
    }
    // cout<<ans1<<" "<<ans2<<" "<<n<<endl;
    printf("%d\n",max((ans1<<1)-1,ans2<<1));
    return 0;
}   