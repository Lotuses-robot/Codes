#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        if(n%3==0) for(int i=1;i<=n/3;i++) cout<<"21";
        else if(n%3==1) {cout<<1;for(int i=1;i<=n/3;i++) cout<<"21";}
        else {for(int i=1;i<=n/3;i++) cout<<"21";cout<<2;}
        cout<<endl;
    }
    return 0;
}