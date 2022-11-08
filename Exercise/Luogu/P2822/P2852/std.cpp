#include <algorithm>
#include <iostream>
#include <cstdio>
#include <deque>
using namespace std;

const int MAXN = 20010;

int n, k, lim, a[MAXN], b[MAXN];
int map[1000010];

int t1[MAXN], t2[MAXN], cnt[MAXN], SA[MAXN];

void Suffix_Array(int sz) { //SA模板 
	int *x = t1, *y = t2, i, t;
	for(i=0; i<sz; i++) cnt[i] = 0;
	for(i=0; i<n; i++) cnt[x[i] = a[i]] ++;
	for(i=1; i<sz; i++) cnt[i] += cnt[i - 1];
	for(i=n-1; ~i; i--) SA[-- cnt[x[i]]] = i;
	for(int k=1; k<=n; k<<=1) {
		t = 0;
		for(i=n-k; i<n; i++) y[t ++] = i;
		for(i=0; i<n; i++)
			if(SA[i] >= k) y[t ++] = SA[i] - k;

		for(i=0; i<sz; i++) cnt[i] = 0;
		for(i=0; i<t; i++) cnt[ x[y[i]] ] ++;
		for(i=1; i<sz; i++) cnt[i] += cnt[i-1];
		for(i=t-1; ~i; i--) SA[-- cnt[ x[y[i]] ] ] = y[i];

		swap(x, y);
		t = 1, x[SA[0]] = 0;
		for(i=1; i<n; i++)
			x[SA[i]] = (y[SA[i-1]] == y[SA[i]] && SA[i-1] + k < n
			            && SA[i] + k < n && y[SA[i-1] + k] == y[SA[i] + k]) ? t-1 : t ++;
		if(t >= n) return ;
		sz = t;
	}
}

int RANK[MAXN], height[MAXN];

void Get_Height() {
	int k = 0;
	for(int i=0; i<n; i++) RANK[SA[i]] = i;
	for(int i=0; i<n; i++) {
		if(RANK[i] == 0) k = 0;
		else {
			if(k) k --;
			int j = SA[RANK[i] - 1];
			while(a[i + k] == a[j + k]) ++ k;
		}
		height[RANK[i]] = k;
	}
}

int main() {
	scanf("%d%d", &n, &k);
	k --;
	for(int i=1; i<=n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	
	sort(b+1, b+n+1);
	for(int i=1; i<=n; i++) { //离散化 
		map[ b[i] ] = map[ b[i-1] ] + (b[i] != b[i-1]);
		lim = max(lim, map[ b[i] ]);
	}
	for(int i=1; i<=n; i++)
		a[i - 1] = map[ a[i] ];
	a[n] = 0;
	
	Suffix_Array(lim + 1); //后缀排序 
	Get_Height();          //计算Height 

    // for (int i = 0; i < n; i++) {
    //     printf("%d ", SA[i]);
    // }
    // puts("");

	int ans = 0;
	deque<int> Q;          //单调队列 
	for(int i=1; i<=n; i++) {
		while(!Q.empty() && Q.front() <= i - k) Q.pop_front(); //不在范围内的 
		while(!Q.empty() && height[Q.back()-1] >= height[i-1]) Q.pop_back(); //不是最小值的 
		Q.push_back(i);
		if(i >= k) ans = max(ans, height[Q.front() - 1]); //更新答案 
	}
	printf("%d\n", ans);
	return 0;
}