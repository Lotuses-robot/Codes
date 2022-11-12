#include<bits/stdc++.h>
using namespace std;

int main()
{
    long long n,a,b,c;
    cin>>n>>a>>b>>c;
    if(c<n) cout<<2*n-1<<endl;
    else
    {
        long long fw=b-a+1;
        long long ans1=n-1+fw*2+(n-fw);
        long long ans2=c+1+(c+1-n)+n-1;
        cout<<min(ans1,ans2)<<endl;
    }
    return 0;
}