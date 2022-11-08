#include<bits/stdc++.h>

using namespace std;

#define INF 1ll<<30
#define ill long long
#define sto set<node>::iterator
#define ri register int

template<typename _T>
inline void read(_T &x)
{
	x=0;char s=getchar();int f=1;
	while(s<'0'||s>'9') {f=1;if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+s-'0';s=getchar();}
	x*=f;
}

int Get(char ch)
{
    if (ch<='9' && ch>='0') return ch-'0';
    if (ch<='Z' && ch>='A') return ch-'A'+10;
    if (ch<='z' && ch>='a') return ch-'a'+36;
    return ch;
}
const int np = 1e6+5;

namespace Hash{ /* 这里有一个卡常小技巧 ， 链表的访问内存不连续，对Cache极不友好，常数会变得巨大
如果TLE了请试试vector，可能更快
*/
	unsigned head[np * 2];
	unsigned Nxt[np*3];
	unsigned val[np*3];
	unsigned rea[np*3];
	int Tit;
	
	inline unsigned &mk(unsigned x,unsigned y) // 传址函数 ， 在函数外可直接修改该地址上的值
	{
		for(int i=head[x];i;i = Nxt[i])
		{
			if(rea[i] == y)
			{
				return val[i];
			 } 
		}
		Tit++;
		Nxt[Tit] = head[x];
		head[x] = Tit;
		rea[Tit] = y;
		return val[Tit];		
	}
	
	inline void Memcpy(int x,int y)
	{
		for(int i=head[x] ;i ;i=Nxt[i])
		{
			++Tit;
			Nxt[Tit] = head[y];
			head[y] = Tit;
			val[Tit] = val[i];
			rea[Tit] = rea[i];
		}
	}
}

struct SAM{
	int fa;
	int len;
	int pos;
}node[np * 2];

int cnt = 1 , la = 1,n;
int Right[np << 1];
ill g[np << 1];//压缩是否存在

inline void add(int x,int i)
{
	ri k,p,q,now;
	p = la , now = la = ++cnt ;
	Right[now] = node[now].len = node[p].len + 1,node[now].pos = i;
	for( ;p &&!((g[p]>>x)&1ll);g[p] += (1ll<<x),Hash::mk(p,x)=now, p = node[p].fa );
	if(!p) return (void)(node[now].fa = 1);
	if(node[p].len + 1 == node[q = Hash::mk(p,x)].len) return (void)(node[now].fa = q);
	node[k = ++cnt].len = node[p].len + 1, node[k].fa = node[q].fa , node[q].fa = node[now].fa = k ,g[k] = g[q] ;
	Right[k] = Right[q];
	Hash::Memcpy(q,k);
	for(;p && !(Hash::mk(p,x)^q) ;Hash::mk(p,x) = k , p = node[p].fa);	
}

int bac[256 + 10];
int tit;
char c[np];

inline void Add(int a,int b)
{
	Hash::rea[++tit] = b;
	Hash::Nxt[tit] = Hash::head[a];
	Hash::head[a] = tit;
}

inline void solve()
{
	for(int i=1;i<=cnt;i++) g[i] = Get(c[n + 1 - Right[i] + node[node[i].fa].len]) , bac[g[i]]++;
	for(int i=1;i<=256;i++) bac[i]+= bac[i-1];
	for(int i=1;i<=cnt;i++) Right[bac[g[i]]--] = i;
	for(int i=cnt;i>=1;i--) Add(node[Right[i]].fa , Right[i]);
}

inline void dfs(int x)
{
	if(node[x].pos)	printf("%d " , node[x].pos);
	for(int i=Hash::head[x];i;i=Hash::Nxt[i])
	dfs(Hash::rea[i]);
}

signed  main()
{
	scanf("%s",c+1);
	n = strlen(c+1);
	for(int i=n;i>=1;i--) add(Get(c[i]) , i);
	for(int i=1;i<=cnt;i++) Hash::head[i] = 0;
	solve();
	dfs(1);
	
 }
