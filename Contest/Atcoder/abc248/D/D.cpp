#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<vector>
#include <ctime>
#include<queue>
#include<set>
#include<map>
#include<list>
#include<stack>
#include<iomanip>
#include<cmath>
#include<bitset>
#define mst(ss,b) memset((ss),(b),sizeof(ss))
///#pragma comment(linker, "/STACK:102400000,102400000")
typedef long long ll;
typedef long double ld;
#define INF (1ll<<60)-1
#define Max 30*500000
using namespace std;
int a[500100];
struct node{
    int l,r,sum;
}tr[Max];
int tot=0;
void update(int &root,int l,int r,int last,int x){
    root=++tot;
    tr[root].sum=tr[last].sum+1;
    tr[root].l=tr[last].l;
    tr[root].r=tr[last].r;
    if(l==r) {
        tr[root].l=root;
        tr[root].r=root;
        return ;
    }
    int mid=(l+r)/2;
    if(x<=mid) update(tr[root].l,l,mid,tr[last].l,x);
    else update(tr[root].r,mid+1,r,tr[last].r,x);
}
int query(int root,int l,int r,int last,int k){
    if(l==r) return l;
    int mid=(l+r)/2;
    if(tr[tr[root].l].sum-tr[tr[last].l].sum>k)
        return query(tr[root].l,l,mid,tr[last].l,k);
    if(tr[tr[root].r].sum-tr[tr[last].r].sum>k)
        return query(tr[root].r,mid+1,r,tr[last].r,k);
    return 0;
}
int root[500100];
int n,m;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) update(root[i],1,n,root[i-1],a[i]);
    scanf("%d", &m);
    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        printf("%d\n",query(root[y],1,n,root[x-1],z));
    }
    return 0;
}