#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,bool> mp;
int p[1000001];
int bf[1000001];

int merge_sort(int l,int r)
{
    if(l==r) return 0;
    int mid=(l+r)>>1,ans=0;
    ans+=merge_sort(l,mid);
    ans+=merge_sort(mid+1,r);

    int i=l,j=mid+1,len=0;
    while(i<=mid&&j<=r)
    {
        if(p[i]<=p[j]) bf[len++]=p[i++];
        else ans+=(mid-i+1),bf[len++]=p[j++];
    }
    while(i<=mid) bf[len++]=p[i++];
    while(j<=r) bf[len++]=p[j++];

    for(int k=l;k<=r;k++) p[k]=bf[k-l];

    return ans;
}

signed main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>p[i];
    }
    cout<<merge_sort(0,n-1);
    // for(int i=1;i<=n;i++) cout<<p[i]<<' ';
    return 0;
}