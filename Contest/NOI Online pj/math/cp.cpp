#include<bits/stdc++.h>
using namespace std;
int ans1[1000001],ans2[1000001];

int main()
{
    int tot1,tot2;tot1=tot2=0;
    freopen("math4.out","r",stdin);
    while(scanf("%d",&ans1[tot1++])==1);
    freopen("math.out","r",stdin);
    while(scanf("%d",&ans2[tot2++])==1);
    
    for(int i=0;i<tot1;i++)
        if(ans1[i]!=ans2[i]) cout<<i<<" "<<ans1[i]<<" "<<ans2[i]<<endl;
}