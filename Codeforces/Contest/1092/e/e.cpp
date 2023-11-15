#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e3+10;
int maxx1[N],maxx2[N],dep[N],vs[N],cnt,flag[N],pre[N],vis[N];
vector<int>a[N];vector< pair<int,int> >answer;
inline void dfs(int x,int fa){
    vis[x]=1;
    for (auto v:a[x]){
        if (v==fa) continue;
        pre[v]=x;dep[v]=dep[x]+1;
        dfs(v,x);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    int nowm=-1,nowmi;
    while (m--){
        int u,v;cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for (int i=1;i<=n;++i){
        if (vis[i]) continue;
        for (int j=1;j<=n;++j) dep[j]=pre[j]=0;
        dfs(i,-1);vector<int>now,now1;
        int maxn=0,maxni=i;
        for (int j=1;j<=n;++j) if (dep[j]>maxn) maxn=dep[j],maxni=j;
        int x=maxni;
        for (int j=1;j<=n;++j) dep[j]=pre[j]=0;
        dfs(maxni,-1);
        maxn=0,maxni=i;
        for (int j=1;j<=n;++j) if (dep[j]>maxn) maxn=dep[j],maxni=j;
        x=maxni;
        while (x) now1.push_back(x),x=pre[x];
        reverse(now1.begin(),now1.end());
        for (auto i:now1) now.push_back(i);
        maxx1[++cnt]=(now.size()-1)/2;
        maxx2[cnt]=(now.size()-1)-((now.size()-1)/2);
        flag[cnt]=now[(ceil(now.size()/2.0))-1];
        if (max(maxx1[cnt],maxx2[cnt])>nowm) nowm=max(maxx1[cnt],maxx2[cnt]),nowmi=cnt;
    }
    for (int i=1;i<=cnt;++i){
        if (i==nowmi) continue;
        a[flag[nowmi]].push_back(flag[i]);
        a[flag[i]].push_back(flag[nowmi]);
        answer.push_back({flag[nowmi],flag[i]});
    }
    for (int j=1;j<=n;++j) dep[j]=pre[j]=0;
    dfs(1,-1);vector<int>now,now1;
    int maxn=0,maxni=1;
    for (int j=1;j<=n;++j) if (dep[j]>maxn) maxn=dep[j],maxni=j;
    int x=maxni;
    for (int j=1;j<=n;++j) dep[j]=pre[j]=0;
    dfs(maxni,-1);
    maxn=0,maxni=1;
    for (int j=1;j<=n;++j) if (dep[j]>maxn) maxn=dep[j],maxni=j;
    cout<<maxn<<'\n';
    for (auto i:answer) cout<<i.first<<' '<<i.second<<'\n';
    return 0;
}
