#include<cstdio>
#include<algorithm>
// using namespace std;
const int N=110000,M=310000,inf=0x3f3f3f3f;

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

struct bian{int x,y,c;}t[M];int tlen;bool v[M];
inline void ins(int x,int y,int c){t[++tlen]={x,y,c};}
bool Res(bian a,bian b){return a.c<b.c;}
 
struct edge{int x,y,c,pre;}a[M];int alen,last[N];
inline void add(bian b){a[++alen]={b.x,b.y,b.c,last[b.x]};last[b.x]=alen;}
 
int n,m,f[N];
int findfa(int x){return f[x]==x?x:f[x]=findfa(f[x]);}
 
int kruskal(){
    std::sort(t+1,t+1+tlen,Res);
    int p=0,res=0;
    for(int i=1;i<=n;++i)f[i]=i;
    for(int i=1;i<=tlen;++i){
        int x=t[i].x,y=t[i].y;
        int fx=findfa(x),fy=findfa(y);
        if(fx!=fy){
            f[fx]=fy;res+=t[i].c;
            v[i]=1;add(t[i]);
            if(++p==n-1){
                break;
            }
        }
    }
    return res;
}
struct trnode{int dep,par[20],g[20][2];}tr[N];
void prepare(int x,int fa,int c){
    tr[x]={tr[fa].dep+1,fa};
    tr[x].g[0][0]=c;
    tr[x].g[0][1]=-inf;
    for(int i=1;i<=19;++i){
        tr[x].par[i]=tr[tr[x].par[i-1]].par[i-1];
         
        tr[x].g[i][0]=max(tr[x].g[i-1][0],tr[tr[x].par[i-1]].g[i-1][0]);
         
        if(tr[x].g[i-1][0]==tr[tr[x].par[i-1]].g[i-1][0])
            tr[x].g[i][1]=max(tr[x].g[i-1][1],tr[tr[x].par[i-1]].g[i-1][1]);
         
        if(tr[x].g[i-1][0]<tr[tr[x].par[i-1]].g[i-1][0])
            tr[x].g[i][1]=max(tr[x].g[i-1][0],tr[tr[x].par[i-1]].g[i-1][1]);
         
        if(tr[x].g[i-1][0]>tr[tr[x].par[i-1]].g[i-1][0])
            tr[x].g[i][1]=max(tr[x].g[i-1][1],tr[tr[x].par[i-1]].g[i-1][0]);
         
    }
    for(int k=last[x];k;k=a[k].pre){
        int y=a[k].y;
        if(y==fa)continue;
        prepare(y,x,a[k].c);
    }
}
void lca(int x,int y,int &v1,int &v2){
    if(tr[x].dep<tr[y].dep)swap(x,y);
    for(int i=19;i>=0;--i)
        if(tr[x].dep-tr[y].dep>=(1<<i)){
            if(v1>tr[x].g[i][0])v2=max(v2,tr[x].g[i][0]);
            else v1=tr[x].g[i][0],v2=max(v2,tr[x].g[i][1]);
            x=tr[x].par[i];
        }
    if(x==y)return;
    for(int i=19;i>=0;--i)
        if(tr[x].par[i]!=tr[y].par[i]){
            v1=max(v1,tr[x].g[i][0],tr[y].g[i][0]);
            if(tr[x].g[i][0]<v1)v2=max(v2,tr[x].g[i][0]);
            else v2=max(v2,tr[x].g[i][0]);
            if(tr[y].g[i][0]<v1)v2=max(v2,tr[y].g[i][0]);
            else v2=max(v2,tr[y].g[i][0]);
        }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        int x,y,c;scanf("%d%d%d",&x,&y,&c);
        ins(x,y,c);ins(y,x,c);
    }
    int sum=kruskal();
    prepare(a[1].x,-1,0);
    int ans=inf;
    for(int i=1;i<=tlen;++i){
        if(v[i])continue;
        int v1=-inf,v2=-inf;
        lca(a[i].x,a[i].y,v1,v2);
        if(a[i].c>v1)ans=min(ans,sum-v1+a[i].c);
        else if(a[i].c==v1)ans=min(ans,sum-v2+a[i].c);
    }
    printf("%d\n",ans);
    return 0;
}
