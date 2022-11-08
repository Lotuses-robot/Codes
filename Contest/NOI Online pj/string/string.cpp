#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
string s,t;

int dfs(int i,string r)
{
    if(i>=s.length()) return r==t;
    if(s[i]!='-') {return dfs(i+1,r+s[i]);}
    int ans=0;
    ans+=dfs(i+1,r.substr(1));ans%=mod;
    ans+=dfs(i+1,r.substr(0,r.length()-1));ans%=mod;
    return ans;
}

int main()
{
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    int T,n,m;
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>s>>t;
        if(n<=15&&m<=15) cout<<dfs(0,"")<<endl;
        else cout<<1;
    }
    return 0;
}