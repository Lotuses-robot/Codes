#include"testlib.h"
#include<bits/stdc++.h>
#ifdef xay5421
#define D(...) fprintf(stderr,__VA_ARGS__)
#define DD(...) D(#__VA_ARGS__ "="),debug_helper::debug(__VA_ARGS__),D("\n")
#include"/home/xay5421/debug.hpp"
#else
#define D(...) ((void)0)
#define DD(...) ((void)0)
#endif
#define pb push_back
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define each(x,v) for(auto&x:v)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
using LL=long long;
using ULL=unsigned long long;

class dsu{
public:
	int n;
	vector<int>fa;
	vector<int>sz;
	dsu(){}
	dsu(int n_):n(n_),fa(n_),sz(n_,1){
		iota(fa.begin(),fa.end(),0);
	}
	void assign(int n_){
		*this=dsu(n_);
	}
	int find(int u){
		return fa[u]==u?u:fa[u]=find(fa[u]);
	}
	bool check(int u,int v){
		return find(u)==find(v);
	}
	bool unite(int u,int v){
		int u_=find(u);
		int v_=find(v);
		if(u_!=v_){
			if(sz[v_]<sz[u_]){
				int tmp=u_;
				u_=v_;
				v_=tmp;
			}
			sz[v_]+=sz[u_];
			fa[u_]=v_;
			return 1;
		}
		return 0;
	}
};
class dsu_cycle:public dsu{
public:
	vector<int>vis;
	dsu_cycle(){}
	dsu_cycle(int n):dsu(n),vis(n){}
	void assign(int n_){
		*this=dsu_cycle(n_);
	}
	bool unite(int u,int v){
		int u_=find(u);
		int v_=find(v);
		if(u_!=v_){
			if(vis[u_]&&vis[v_]){
				return 0;
			}
			if(sz[v_]<sz[u_]){
				int tmp=u_;
				u_=v_;
				v_=tmp;
			}
			vis[v_]|=vis[u_];
			sz[v_]+=sz[u_];
			fa[u_]=v_;
			return 1;
		}else{
			if(vis[u_]){
				return 0;
			}else{
				vis[u_]=1;
				return 1;
			}
		}
	}
};
const int N=200005,K=20;
int n;
vector<int>e[N];
int Q,x[N],y[N],z[N];
int fa[N][K],dep[N];
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int dt=dep[x]-dep[y];
	per(i,K-1,0)if(dt>>i&1)x=fa[x][i];
	if(x==y)return x;
	per(i,K-1,0)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}
void readIn() {
    n=inf.readInt(1,200000);
    dsu o(n+1);
    rep(i,2,n){
    	int u,v;
    	u=inf.readInt(1,n);
    	v=inf.readInt(1,n);
    	o.unite(u,v);
    	e[u].pb(v),e[v].pb(u);
    }
    rep(i,1,n){
	    ensuref(o.find(i)==o.find(1),"Input is not a tree");
    }
    Q=inf.readInt(1,200000);
    rep(i,1,Q){
    	x[i]=inf.readInt(0,200000);
    	y[i]=inf.readInt(0,200000);
    	z[i]=inf.readInt(0,200000);
    }
    queue<int>que;
    que.push(1);
    dep[1]=1;
    while(!que.empty()){
    	int u=que.front();
    	que.pop();
    	rep(i,1,K-1)fa[u][i]=fa[fa[u][i-1]][i-1];
    	for(auto&x:e[u]){
    		if(!dep[x]){
    			dep[x]=dep[u]+1;
    			fa[x][0]=u;
    			que.push(x);
    		}
    	}
    }
}

void readOut() {
    rep(i,1,Q){
    	int u=ouf.readInt(1,n);
    	int v=ouf.readInt(1,n);
    	int w=ouf.readInt(1,n);
    	if(dis(u,v)!=x[i]){
    		quitf(_wa,"Wrong answer on test %d",i);
    	}
    	if(dis(u,w)!=y[i]){
    		quitf(_wa,"Wrong answer on test %d",i);
    	}
    	if(dis(v,w)!=z[i]){
    		quitf(_wa,"Wrong answer on test %d",i);
    	}
    }
    quitf(_ok,"Accepted!");
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // registerLemonChecker(argc, argv);
    readIn();
    readOut();
    return 0;
}

