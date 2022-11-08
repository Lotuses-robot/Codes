#pragma comment(linker,"/STACK:102400000,102400000")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fi first 
#define se second 
using  namespace std;
typedef pair<int,int>P;
const int maxn=1e5+5;
const int mod=1e6+3;
const int M=1e6+10;
int head[maxn],ver[maxn<<1],next1[maxn<<1],sz[maxn],mxson[maxn],S,rt,ans1,ans2,mp[M],inv[M],n,k,tot,a[maxn],cnttmp,d[maxn];
P tmp[maxn];
bool v[maxn];
void add(int x,int y){
    ver[++tot]=y,next1[tot]=head[x],head[x]=tot;
}
void init1(){
    inv[1]=1;
    for(int i=2;i<M;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;  
}
void getRoot(int x,int f){
    sz[x]=1;mxson[x]=0;
    for(int i=head[x];i;i=next1[i]){
        int y=ver[i];
        if(y==f||v[y])continue;
        getRoot(y,x);
        sz[x]+=sz[y];
        mxson[x]=max(mxson[x],sz[y]);
    }
    mxson[x]=max(mxson[x],S-mxson[x]);
    if(mxson[x]<mxson[rt])rt=x;
}
void init(int x){
    S=sz[x];
    mxson[rt=0]=maxn;
    getRoot(x,0);
}
void getQue(int x,int f,int val){
    tmp[++cnttmp]={val,x};
    for(int i=head[x];i;i=next1[i]){
        int y=ver[i];
        if(v[y]||y==f)continue;
        getQue(y,x,1ll*val*a[y]%mod);
    }
}
void update(int x,int y){
    if(x==y)return;
    if(x>y)swap(x,y);
    if(x<ans1||(x==ans1&&y<ans2))ans1=x,ans2=y;
}
void cal(int x){
    mp[1]=x;
    int num=0;
    for(int i=head[x];i;i=next1[i]){
        int y=ver[i];
        if(v[y])continue;
        cnttmp=0;
        getQue(y,x,a[y]);
        for(int i=1;i<=cnttmp;++i){
            int flag=1ll*inv[tmp[i].fi]*inv[a[x]]%mod*k%mod;
            if(mp[flag])update(tmp[i].se,mp[flag]);
        }
        for(int i=1;i<=cnttmp;++i){
            if(!mp[tmp[i].fi]||mp[tmp[i].fi]>tmp[i].se)mp[tmp[i].fi]=tmp[i].se;
            d[++num]=tmp[i].fi;
        }
    }   
    for(int i=num;i;--i)mp[d[i]]=0;
    mp[1]=0;
}
void dfz(int x){
    v[x]=1;
    cal(x);
    for(int i=head[x];i;i=next1[i]){
        int y=ver[i];
        if(v[y])continue;
        init(y);
        dfz(rt);
    }
}
int main(){
    freopen("4812.in", "r", stdin);
    freopen("4812.ans", "w", stdout);
    init1();
    int x,y;
    while(~scanf("%d%d",&n,&k)){
        tot=0;
        ans1=ans2=maxn;
        for(int i=1;i<=n;++i)head[i]=0,v[i]=0;
        for(int i=1;i<=n;++i)scanf("%d",&a[i]);
        for(int i=1;i<n;++i){
            scanf("%d%d",&x,&y);
            add(x,y);add(y,x);
        }
        S=n;
        mxson[rt=0]=maxn;
        getRoot(1,0);
        dfz(rt);
        if(ans1==maxn)puts("No solution");
        else cout<<ans1<<" "<<ans2<<"\n";   
    }
    return 0;
}