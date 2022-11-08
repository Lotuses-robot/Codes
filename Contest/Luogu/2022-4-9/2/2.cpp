#include<bits/stdc++.h>
using namespace std;
int a[2000001];

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;

        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);

        if(n==1) puts("YES");
        else if(n==2)
        {
            if(a[1]==0) puts("YES");
            else puts("NO");
        }
        else if(n>=4) puts("YES");
        else
        {
            a[2]-=a[1];
            a[3]+=a[1]*2;
            a[1]=0;
            int copy2=a[2],copy3=a[3];
            bool flag=false;
            for(int ty=1;ty<=10000;ty++)
            {
                if(a[n-1]%3==0 || a[n]%3==0 && a[n-1]>=a[n]/3*2) {puts("YES");flag=true;break;}
                a[3]-=a[2];
                a[2]=2*a[2];
                if(a[2]>a[3]) swap(a[2],a[3]);
            }
            if(!flag)
            {
                if(n<=10) puts("NO");
                else puts("NO");
            }
        }
    }
}