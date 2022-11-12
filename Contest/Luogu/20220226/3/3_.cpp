#include<bits/stdc++.h>
#define int long long
using namespace std;

int s(int n)
{
    if(n<0) return 0;
    return n*(n+1)*(2*n+1)/6;
}

int main()
{
    int n,m,t,a,b;
    cin>>n>>m>>t>>a>>b;
    cout<<m*a+b*s(m-1);
    return 0;
}