#include<bits/stdc++.h>
using namespace std;
bool flag[1000001];
vector<int> ans;
int n,m,k;
int it[1000001];

char chr[50];
bool check1(int t)
{
    sprintf(chr,"%d",t);
    int tot=0;
    for(int i=0;i<strlen(chr);i++)
        if((chr[i]-'0')%2==0) tot++;
    // cout<<tot<<endl;
    return tot==m;
}

bool check2(int t)
{
    return it[t]==k;
}

long long dcp(long long x){
    long long i,ans = 1;
    for(i = 2; i * i <= x; i++){
        if(x % i == 0){
            long long temp = 0;
            while(x % i == 0){
                x /= i;
                temp++;
            }
            ans *= (temp+1);
        }
    }
    if(x > 1) ans *= 2;
    return ans;
}

void init()
{
    it[1]=1;
    for(int i=2;i<=100000;i++)
        if(it[i]==0) it[i]=dcp(i);
}

const double eps=1e-5;

int main()
{
    init();
    // for(int i=1;i<=100;i++) cout<<it[i]<<" ";
    int T;
    cin>>T;
    while(T--)
    {
        memset(flag,0,sizeof(flag));ans.clear();
        cin>>n>>m>>k;
        for(int i=int(pow(10,n-1)+eps);i<=int(pow(10,n)+eps-1);i++)
            if(check1(i)&&check2(i)) ans.push_back(i);
        
        if(ans.size()!=0) cout<<ans.size()<<endl;
        else cout<<-1<<endl;
        for(auto i:ans) cout<<i<<endl;
    }
}