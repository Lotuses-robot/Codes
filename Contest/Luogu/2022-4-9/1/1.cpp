#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n,k;
        cin>>n>>k;

        if(k<n) {cout<<"Impossible\n";continue;}

        cout<<"5 or more\n";
        for(int i=1;i<=5;i++)
        {
            for(int j=1;j<=n;j++) cout<<i<<" ";
            puts("");
        }
    }
    return 0;
}