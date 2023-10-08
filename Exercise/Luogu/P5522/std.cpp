#include<bits/stdc++.h>
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
struct Node{
	int l,r,x,y,have_ans;
}T[400010];
int x[100010],y[100010];
inline void pushup(int p){
	T[p].x=T[lc].x|T[rc].x;
	T[p].y=T[lc].y|T[rc].y;
	if((T[lc].x&T[rc].x)&(T[lc].y^T[rc].y)||(!T[lc].have_ans)||(!T[rc].have_ans))
		T[p].have_ans=0;
	else T[p].have_ans=1;
}
void build(int p,int l,int r){
	T[p].l=l;T[p].r=r;
	if(l==r){
		T[p].x=x[l];
		T[p].y=y[l];
		T[p].have_ans=1;
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(p);
	//printf("%d %d %d %d %d\n",T[p].l,T[p].r,T[p].x,T[p].y,T[p].have_ans);
}
int have_ans;
Node query(int p,int ql,int qr){
	//printf("%d %d %d %d %d\n",T[p].l,T[p].r,T[p].x,T[p].y,T[p].have_ans);
	if(ql<=T[p].l&&T[p].r<=qr)
		return T[p];
	int mid=(T[p].l+T[p].r)>>1;
	if(ql<=mid&&mid<qr){
		Node l=query(lc,ql,qr),r=query(rc,ql,qr),ans;
		ans.x=l.x|r.x;ans.y=l.y|r.y;
		if((l.x&r.x)&(l.y^r.y)||(!l.have_ans)||(!r.have_ans))
			ans.have_ans=0;
		else ans.have_ans=1;
		return ans;
	}
	if(ql<=mid)return query(lc,ql,qr);
	if(qr>mid)return query(rc,ql,qr);
}
void update(int p,int q,int x,int y){
	if(T[p].l==T[p].r){
		T[p].x=x;T[p].y=y;
		T[p].have_ans=1;
		return;
	}
	int mid=(T[p].l+T[p].r)>>1;
	if(q<=mid)update(lc,q,x,y);
	else update(rc,q,x,y);
	pushup(p);
}
int main(){
	freopen(".in", "r", stdin);
	freopen(".ans", "w", stdout);
	ios::sync_with_stdio(false);
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=1;i<=m;++i){
		string s;cin>>s;
		int xx=0,yy=0;
		for(int j=0;j<s.size();++j){
			xx<<=1;yy<<=1;
			if(s[j]=='?'){
				xx|=0;yy|=0;
			}
			else{
				xx|=1;yy|=s[j]-'0';
			}
		}
		x[i]=xx;y[i]=yy;
	}
	build(1,1,m);
	int ans=0;
	for(int i=1;i<=q;++i){
		int t;cin>>t;
		if(t==0){
			int x,y;
			cin>>x>>y;
			have_ans=0;
			Node now=query(1,x,y);
			if(!now.have_ans){
				// ans^=0;
				cout<<"0\n";
				continue;
			}
			int k=1;
			for(int i=1;i<=n;++i){
				if(!(now.x&1))k<<=1;
				now.x>>=1;
			}
			// ans^=k;
			cout<<k<<'\n';
		}
		if(t==1){
			int place;cin>>place;
			string s;cin>>s;
			int xx=0,yy=0;
			for(int j=0;j<s.size();++j){
				xx<<=1;yy<<=1;
				if(s[j]=='?'){
					xx|=0;yy|=0;
				}
				else{
					xx|=1;yy|=s[j]-'0';
				}
			}
			update(1,place,xx,yy);
		} 
	}
	// cout<<ans;
	return 0;
}