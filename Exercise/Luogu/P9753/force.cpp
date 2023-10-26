#include <bits/stdc++.h>

#define gc getchar()
template<typename T>
void read(T &r) {
	char ch = gc, last = 'z'; r = 0;
	while (ch < '0' || ch > '9') last = ch, ch = gc;
	while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
	if (last == '-') r = -r;
}

#define int long long

std::string s, nul = "";
char ch[100005];
bool check() {
//	printf("%s\n", s.c_str());
	while (s != "") {
		bool flag = false;
		for (int i = 0; i < s.length() - 1; i++) {
			if (s[i] == s[i + 1]) {
				s = (i > 0 ? s.substr(0, i) : nul) + s.substr(i + 2);
				flag = true;
				break;
			}
		}
		if (!flag && s != "") {
			return false;
		}
	}
	return true;
}

signed main() {
	freopen(".in", "r", stdin);
	freopen(".ans", "w", stdout);
	int n, ans = 0;
	read(n);
	if (n > 800) {
		puts("0");
		return 0;
	}
	scanf("%s", ch + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			s = "";
			for (int k = i; k <= j; k++) {
				s += ch[k];
			}
            if (check()) { 
                printf("%d %d\n", i, j);
                ans++;
            }
		}
	}
	printf("%lld\n", ans);
	return 0;
}