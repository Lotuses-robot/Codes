首先考虑给定一个长度为 $n$ 的括号序列，我们将它变成一个合法括号序列的最优策略是什么样的。

首先有两个性质：

1. 我们只会做最多一次变换操作。

证明：显然，多次变换操作可以合为一次。

2. 设这个序列有 $A$ 个左括号，$B$ 个右括号，那么必然存在一种变换方案，使得变换后有 $\min(A,B)$ 组括号被匹配。换句话说，就是左括号和右括号中个数较少的全部被匹配到。

证明：不妨设 $A \ge B$，把左括号看作 $1$，右括号看作 $-1$，然后再得到一个前缀和数组 $c$。然后选择数组中最小值所在位置 $x$，通过变换使得 $x$ 这个位置移到新序列的末尾。

如果有右括号没匹配上左括号，就说明存在一个位置 $i$ 使得 $c_i<0$。

对于 $x$ 之后的任意位置 $y$ 都有 $c_x<c_y$，那么把 $[x+1,n]$ 变换到序列开头，这部分必然使得整体的 $c$ 数组增加。

而变换前 $[1,x]$ 这部分在变换后的 $c$ 值增加量是完全一致的（也就是变换前的 $c_n-c_x$）。因此 $c_x$（相当于变换后的 $c_n$）依然是这部分的最小值。又因为 $A \ge B$，我们可以知道 $c_x$ 此时就是 $A-B \ge 0$。

因此结论得证。$A < B$ 的情况是类似的，不再赘述。有了这两个性质，这题就可做了。因为我们发现如果一个序列的匹配数没有达到上界 $\min(A,B)$ 的话，我们把它循环移位一下必然不劣。因此最后的答案就是 $\sum_{l=1}^{n} \sum_{r=l}^{n} \lvert A[l, r] - B[l, r]\rvert+g(l,r)$，其中 $A,B$ 意义同上，$g(l,r)$ 表示序列的匹配数是否达到上界（是为 $0$，不是为 $1$）。

- $n \leq 400$，$\sum n \leq 800$

暴力枚举 $l,r$，再暴力计算，时间复杂度 $O(n^3)$。

- $n \leq 2\times 10^3$，$\sum n \leq 4\times 10^3$

暴力枚举 $l$，$r$ 从 $l$ 开始向后拓展，在拓展的过程中维护括号匹配情况以及 $A,B$，计算 $[l,r]$ 的贡献。时间复杂度 $O(n^2)$。

- 特殊性质：所有括号都是左括号

此时容易发现就是求 $\sum_{l=1}^{n} \sum_{r=l}^{n} r-l+1$。这就是 $\sum_{i=1}^n (n-i+1) \times i$ 啊。如果您是数学带师的话还可以直接看出这个东西就是 $n+2 \choose 3$（考虑组合意义）。

- 特殊性质：对于所有整数 $1\le i < n$，有 $s_i \neq s_{i+1}$

所有可能的子串只有四种形态：$\texttt{()()} \cdots \texttt{()}$，$\texttt{)()} \cdots \texttt{()}$，$\texttt{)()} \cdots \texttt{()(}$ 和 $\texttt{()()} \cdots \texttt{()(}$。其中只有第三种 $g(l,r)=1$，容易做到线性计算。

- $n \leq 2\times 10^5$，$\sum n \leq 5\times 10^5$


此时我们再整理整理式子，让它变成 $\sum_{l=1}^{n} \sum_{r=l}^{n}   |c_r-c_{l-1}| + \sum_{l=1}^{n} \sum_{r=l}^{n} g(l,r)$。

前面那个部分可以直接把 $c$ 排序后快速计算 $\sum_{r=0}^{n} \sum_{l=0}^{r}   c_r-c_l$ 即可。对于后面那个，我们考虑把 $g(l,r)$ 转化成更优秀的条件。

关键性质：$g(l,r)=1$ 等价于：$\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < \min(c_{l-1},c_r)$。

证明：

$\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < c_{l-1}$ 可以看作至少一个右括号失配。

$\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < c_{r}$ 可以看作至少一个左括号失配。

由之前得到的性质 2，容易知道这是 $g(l,r)=1$ 的充要条件。

直接硬莽 $\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < \min(c_{l-1},c_r)$ 有点困难，我们将其转化为 $\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < c_{l-1} < c_r$ 和 $\min\{c_l,c_{l+1},\cdots,c_{r-1}\} < c_r \le c_{l-1}$ 两种情况的方案数之和。

一般化地，我们枚举 $l$，找到最小的 $pos_{l}$ 满足 $\min\{c_{l+1},c_{l+2},\cdots,c_{pos_l}\} < c_{l}$，再查询满足 $x>pos_l$ 且 $c_x>c_{l}$ 的 $x$ 个数，就可以算出满足 $\min\{c_{l+1},c_{l+2},\cdots,c_{r-1}\} < c_{l} < c_r$ 的方案数了。另一种情况同理。

使用单调栈求出 $pos_i$，后面的部分本质上是二维偏序，可以离线树状数组，总时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4000005;
int n,m,sum[N],tmp[N],a[N],top,stc[N];
ll ts,ans; char str[N];
struct BIT{
	int c[N];
	#define lowbit(x) (x&(-x))
	inline void clr(){ for(int i=1;i<=n*2+1;i++) c[i]=0; }
	inline void update(int x){ while(x<=n*2+1) c[x]++,x+=lowbit(x); }
	inline int query(int x){ int res=0; while(x) res+=c[x],x-=lowbit(x); return res; }
}T;
struct Q{
	int x,val;
	bool operator < (const Q &a) const { return x<a.x; }
}q[N];
inline void calc(int op){ // op=0:a[l]<=a[r],op=1:a[l]<a[r] 满足 min(a[l+1],...,a[r-1])<a[l]
	top=m=0;
	for(int i=n;i;i--){
		while(top && a[i]<=a[stc[top]]) top--;
		if(top) q[++m]={stc[top],a[i]};
		stc[++top]=i;
	}
	sort(q+1,q+m+1);
	for(int i=m,j=n;i;i--){
		while(j>=q[i].x) T.update(a[j]+n+1),j--;
		ans+=n-j-T.query(q[i].val+n+op);
	}
	T.clr();
}
inline void solve(){
	scanf("%d%s",&n,str+1);
	for(int i=1;i<=n;i++)
		sum[i+1]=sum[i]+(str[i]=='('?1:-1);
  	// 为了方便，我在这里直接把 c[0] 放在前面，后面统计贡献就全部是 1 下标了
	ans=ts=0; n++;
	for(int i=1;i<=n;i++) tmp[i]=sum[i];
	sort(tmp+1,tmp+n+1);
	for(int i=1;i<=n;i++) ans+=1ll*(i-1)*tmp[i]-ts,ts+=tmp[i]; // 求第一部分的贡献
	for(int i=1;i<=n;i++) a[i]=sum[i]; calc(0);
	for(int i=1;i<=n;i++) a[i]=sum[n-i+1]; calc(1);
	printf("%lld\n",ans);
}
int main(){
	int tc; scanf("%d",&tc);
	while(tc--) solve();
	return 0;
}
```

- $1 \leq n \leq 2 \times 10^6$，$1 \leq \sum n \leq 2 \times 10^7$

$g(l,r)=1$ 的统计稍显麻烦，我们正难则反。

考虑 $g(l,r)=0$ 等价于 $\min\{c_l,c_{l+1},\cdots,c_{r-1}\} \ge \min(c_{l-1},c_r)$，我们不妨对 $g(l,r)=0$ 的情况计数。

那么这个式子等价于 $c_{l-1}\le \min\{c_l,c_{l+1},\cdots,c_{r}\}$ 或  $c_{r}\le \min\{c_{l-1},c_l,\cdots,c_{r-1}\}$。

发现一个重要的事实：在 $c_{l-1} \neq c_r$ 时，我们上面的这个或式不可能同时满足！且 $c_{l-1} = c_r$ 时，这两个式子必然同时满足或不满足。

另外我们还注意到：$c_{i+1}=c_i \pm 1$。

于是 $c_l \le \min\{c_{l+1},c_{l+2},\cdots,c_{r}\}$ 可以直接等价于 $(c_l-1) \notin \{c_{l+1},c_{l+2},\cdots,c_{r}\}$！

那么容易发现对于一个 $c_i$，其向左和向右延伸的贡献为一段连续的区间，那么这个区间我们都不需要单调栈了（上面实际上也不用），用一个桶就可以轻松求出，且在 $c_{l-1} \neq c_r$ 时，其贡献必然被 $c_{l-1}$ 向右的区间和 $c_r$ 向左的区间中的**恰好一个**统计到！

那么我们直接将所有贡献区间统计起来，就统计好了所有 $c_{l-1} \neq c_r$ 的贡献，而 $c_{l-1}=c_r$ 的贡献则被我们计算了两遍。

于是我们现在需要再减掉所有 $c_{l-1}=c_r$ 的贡献。依旧是注意到 $c_{i+1}=c_i \pm 1$，于是我们发现 $c_{l-1}=c_r$ 有贡献当且仅当不存在 $i$ 满足 $l \le i \le r$ 且 $c_i=c_{l-1}-1$。那么我们发现对于每一种 $c_i$ 其出现的位置又可以依此划为一段一段，而每一段出现次数为 $cnt$ 的贡献即为 $ cnt \choose 2$。这个部分线性扫一遍即可完成，具体实现也可以参照代码。（代码比题解清楚.jpg）

至于前面的部分 $\sum_{r=0}^{n} \sum_{l=0}^{r}   c_r-c_l$ 中计算怎么做到线性？$c_i$ 的值域是 $[-n,n]$ 的，于是直接桶排序即可。
$$
\sum_{i = 0} ^ n (c_i \cdot (i + 1) - \sum_{j = 0} ^ i c_j)
$$


于是我们做到了时间复杂度 $O(n)$，且实现非常简洁。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4000005;
int n,m,sum[N],tmp[N],cnt[N],lst[N];
ll ts,ans; char str[N];
inline void solve(){
    scanf("%d%s",&n,str+1);
    for(int i=1;i<=n;i++)
        sum[i+1]=sum[i]+(str[i]=='('?1:-1);
    // 为了方便，我在这里直接把 c[0] 放在前面，后面统计贡献就全部是 1 下标了
    ans=ts=0; n++;
    for(int i=1;i<=n;i++) tmp[i]=sum[i];
	for(int i=1;i<=n+n;i++) cnt[i]=0;
    for(int i=1;i<=n;i++) cnt[tmp[i]+n]++;
    for(int i=1,j=0;i<=n+n;i++)
		for(int t=1;t<=cnt[i];t++) ans+=1ll*j*(i-n)-ts,ts+=i-n,j++;
	// 求第一部分的贡献
	ans+=1ll*n*(n-1)/2;
	for(int i=0;i<=n+n;i++) lst[i]=n+1;
    for(int i=n;i;i--){
    	int r=lst[sum[i]+n-1]-1;
    	ans-=r-i;
    	lst[sum[i]+n]=i;
	}
	for(int i=0;i<=n+n;i++) lst[i]=0;
	for(int i=1;i<=n;i++){
		int l=lst[sum[i]+n-1]+1;
		ans-=i-l;
		lst[sum[i]+n]=i;
	}
	// 求第二部分的贡献
	for(int i=1;i<=n+n;i++) cnt[i]=0;
	for(int i=1;i<=n;i++){
		cnt[sum[i]+n]++;
		if(i==n||sum[i]>sum[i+1]){
			ans+=1ll*cnt[sum[i]+n]*(cnt[sum[i]+n]-1)/2;
			cnt[sum[i]+n]=0;
		}
	}
	for(int i=1;i<=n+n;i++) if(cnt[i]) ans+=1ll*cnt[i]*(cnt[i]-1)/2; 
	// 第二部分在 c[l]=c[r] 时会算重 
    printf("%lld\n",ans);
}
int main(){
    int tc; scanf("%d",&tc);
    while(tc--) solve();
    return 0;
}
```

顺带一提，这题的做法真的很多很多。