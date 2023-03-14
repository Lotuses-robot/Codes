（除了 D2T1 与 D2T3 均对 $998244353$ 取模）

D1T1：给定 $n\times n$ 矩阵 $A,B,C$ 判断 $A\times B=C$。

$\sum n=3000$

D1T2：给定 $T$ 组询问 $n,m$，计数排列 $p$ 满足 $\forall i\le m,a_i,m$ 与 $\forall i,a_i\ne i$。

$T,n,m\le 2\times10^5$，三秒（是 $O((T+n)\sqrt{n\log n})$ 的）

D1T3：给定长度为 $n$ 序列的 $a$ 与 $m$ 条边与常数 $C$，计数长度为 $n$ 的序列 $b$ 满足 $0\le b_i \le a_i$，且每条边 $(u_i,v_i)$ 满足 $b_{u_i}\ne b_{v_i}$，且 $b$ 的异或和等于 $C$.

$n\le 15;m\le n(n+1)/2;a_i,b_i,C\le 10^{18}$

D2T1：给定 $n$ 个点的树，$q$ 组询问 $x,y,z$，求<strong>任意一个</strong>三元组 $(a,b,c)$ 满足 $\operatorname{dis}(a,b)=x,\operatorname{dis}(a,c)=y,\operatorname{dis}(b,c)=z$，保证有解。

$n,q\le 2\times10^5$

D2T2：给定 $n,K,p,x0$ 与长度为 $2^n$ 的序列 $C_{0\dots 2^n-1}$。

定义第 $i$ 次操作生成一个 $[0,2^n)$ 随机数 $x$，然后 $x_i$ 有 $p$ 的概率为 $x_{i-1} \operatorname{or} x$，$1-p$ 的概率为 $x_{i-1}\operatorname{and} x$。

定义 $K$ 次操作后，序列 $x$ 的权值为 $\sum C_{x_i}$，求对于每一个 $i$，满足 $x_K=i$ 的序列 $x$ 的权值的期望。

$n\le 17;K\le 10^9$

D2T3：给定 $n$ 个点以 $1$ 为根的树，点 $i$ 的权值为 $i$。

$q$ 组询问 $x,k$，求 $\sum v_i \operatorname{xor} \operatorname{dis}(x,i)$，满足所有结点 $i$ 在 $x$ 的子树中且 $\operatorname{dis}(x,i)\le k$。

$n,q\le 2\times10^5$