#include<bits/stdc++.h>
using namespace std;
map<int,int>tot;
int v1[1001],v2[1001];

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        tot.clear();
        int n,k,flag=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>k,tot[k]++,v1[i]=k;
        for(int i=1;i<=n;i++) cin>>k,tot[k]--,v2[i]=k;
        for(auto it:tot)
        {
            if(it.second!=0) {cout<<"NO\n";flag=1;break;}
        }
        if(!flag)
        {
            cout<<"YES\n";
            for(int i=1;i<n;i++)
                if(v1[i]!=v2[i])
                {
                    int ans;
                    for(int j=i+1;j<=n;j++)
                        if(v1[j]==v2[i])
                        {
                            ans=j;
                            break;
                        }

                    cout<<ans<<endl;
                    for(int j=ans;j>i;j--) cout<<j<<" "<<j-1<<endl,swap(v1[j],v1[j-1]);
                }
            cout<<"0 0\n";
        }
    }
}