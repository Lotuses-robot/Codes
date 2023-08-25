/**
 *    Author: yurzhang
 *    Date: 2020/02/16
 *
 *     Summer Pockets
 *  - REFLECTION  BLUE -
 */
%:pragma GCC optimize("Ofast,inline,unroll-loops")
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

const int N(1010);
const int M(50010);
default_random_engine e;

struct edge {
    int x,y;
}st[M];
int n,m,left,right,u,v,tp;
int ll,rr,lr,vis[N][N];

int main() {
    // scanf("%d",&n);
    n = 13;
    left=n>>1; right=n-left; e.seed(time(NULL));
    uniform_int_distribution<int>getL(1,left),getR(left+1,n);
    uniform_int_distribution<int>LL(0,left*(left-1)/2);
    uniform_int_distribution<int>RR(0,right*(right-1)/2);
    uniform_int_distribution<int>LR(0,n<<1);
    ll=LL(e); rr=RR(e); lr=LR(e);
    if(e()&1) {
        ll=0; m=rr+lr;
        if(m>50000) {
            int x(m-50000),y(x>>1);
            x-=y; rr-=x; lr-=y;
            m=50000;
        }
    } else {
        rr=0; m=ll+lr;
        if(m>50000) {
            int x(m-50000),y(x>>1);
            x-=y; ll-=x; lr-=y;
            m=50000;
        }
    } while(ll--) {
        u=getL(e); v=getL(e);
        while(u==v||vis[u][v]) {
            u=getL(e); v=getL(e);
        } vis[u][v]=vis[v][u]=1;
        st[++tp]=(edge){u,v};
    } while(rr--) {
        u=getR(e); v=getR(e);
        while(u==v||vis[u][v]) {
            u=getR(e); v=getR(e);
        } vis[u][v]=vis[v][u]=1;
        st[++tp]=(edge){u,v};
    } while(lr--) {
        u=getL(e); v=getR(e);
        while(vis[u][v]) {
            u=getL(e); v=getR(e);
        } vis[u][v]=vis[v][u]=1;
        st[++tp]=(edge){u,v};
    } freopen("shinku.in","w",stdout);
    printf("%d %d\n",n,m);
    for(int i=1;i<=m;++i)
        printf("%d %d\n",st[i].x,st[i].y);
    fclose(stdout);
    return 0;
}