#include<bits/stdc++.h>
using namespace std;
int a[101];

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n,tot=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                for(int k=j;k<=n;k++)
                    if(a[i]+a[j]==a[k]) tot++;
        
        cout<<tot<<endl;
    }
}