#include<bits/stdc++.h>
#define maxn 200005
#define INF 0x7fffffff
using namespace std;
struct node{int to,next,v,g;};
node t[maxn*2],tc[maxn*2];
int n,m,s;
int tot,totc,cnt,num;
int h[maxn],hc[maxn],dfn[maxn],low[maxn],c[maxn],in[maxn],sum[maxn],rd[maxn],f[maxn];
stack<int> sta;
void add(int x,int y,int z,int l){ //加边
	t[++tot].to=y;
	t[tot].next=h[x];
	t[tot].v=z;
	t[tot].g=l;
	h[x]=tot;
}
void addc(int x,int y,int z){ //新图加边
	tc[++totc].to=y;
	tc[totc].next=hc[x];
	tc[totc].v=z;
	hc[x]=totc;
}
void tarjan(int x){
	dfn[x]=low[x]=++num; //当到达一个新的节点时，将它的追溯值（low）标记为它的时间戳（dfn） 
	sta.push(x),in[x]=1; //将这个点入栈 
	for(int i=h[x];i;i=t[i].next){ //枚举每条出边 
		int y=t[i].to;
		if(!dfn[y]){ //如果这个点没有被访问过，则递归访问 
			tarjan(y);
			low[x]=min(low[x],low[y]); //更新追溯值 
		}else if(in[y]) low[x]=min(low[x],dfn[y]); //如果这个子节点在栈里，则也需要更新追溯值 
	}
	if(dfn[x]==low[x]){ //找到了一个强连通分量 
		cnt++;
		int y;
		do{ //将这个强连通分量中的所有的点出栈，并将它染色 
			y=sta.top(); sta.pop(); in[y]=0;
			c[y]=cnt;
		}while(x!=y);
	}
}
void toposort(){
	//f[i]定义为起点s到i采到的最大的蘑菇数 
	queue<int> q; //用队列来储存入度为0的点 
    for(int i=1;i<=cnt;i++){
       	if(!rd[i]) q.push(i); //将入度为0的强连通分量入队 
    	f[i]=-INF; //DP初始化 
        printf("%d %d %d\n", c[s], i, rd[i]);
    }
    printf("%d\n", sum[c[s]]);
    f[c[s]]=sum[c[s]]; //将起点s所在的强连通分量的DP值赋值为边权总和 
    while(!q.empty()){
        int x=q.front(); q.pop(); //取出队头，并将它出队 
        for(int i=hc[x];i;i=tc[i].next){ //枚举这个强连通分量的每条出边 
            int y=tc[i].to;
            f[y]=max(f[y],f[x]+tc[i].v+sum[y]); //用这个点的父节点的DP值来更新它 
            rd[y]--; //将子节点的入度减1 
            if(!rd[y]) q.push(y); //将入度为0的点入队 
        }
    }
}
int main(){
    freopen(".in", "r", stdin);
	freopen(".ans", "w", stdout);
    int x,y,z;
	double l;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d %lf",&x,&y,&z,&l);
		add(x,y,z,int(l*10)); //将恢复系数乘10，用整型边储存，减少精度损耗
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int x=1;x<=n;x++){ //枚举边的起点 
		for(int i=h[x];i;i=t[i].next){ //枚举每条出边 
			int y=t[i].to;
			if(c[x]!=c[y]){ //如果这两个点不在同一个强连通分量中，则需要将这两个点所在的强连通分量连一条边 
				addc(c[x],c[y],t[i].v); //两个强连通分量之间的边只能被经过一次（DAG），所以边权就是原本两个点的边权 
				rd[c[y]]++; //统计入度 
			}else{
				int s=0,a=t[i].v;
				while(a){ //将这条边所能贡献的最大权值累加起来 
					s+=a;
					a*=t[i].g; //g就是这条边的恢复系数 
					a/=10;
				}
				sum[c[x]]+=s; //sum[i]就是编号为i的强连通分量中的边权和
			}
		}
	}
	scanf("%d",&s);
	toposort();
	int ans=0;
    printf("%d\n", cnt);
	for(int i=1;i<=cnt;i++) {
        ans=max(ans,f[i]);
        printf("%d\n", f[i]);
    }
    printf("%d",ans);
	return 0;
}
