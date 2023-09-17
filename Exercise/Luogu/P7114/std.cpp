#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int MAXN = (1 << 20) + 5;
char s[MAXN];//输入的字符串
int n, z[MAXN];//字符串长度，以及z函数的值
int before[30], after[30];//两个桶，分别统计当前枚举到的位置左侧和右侧每个字符出现的频次
int pre, suf, all;//当前枚举到的位置的前缀、后缀、整个串里面出现奇数次的字符的个数

//树状数组，对于s的某个前缀si，如果它里面出现奇数次的字符有m个，则在树状数组m+1位置+1
int c[30];

inline int lbt(int x) {
    return x & -x;
}

void update(int x) {
    while (x <= 27) {
        c[x]++;
        x += lbt(x);
    }
}

int sum(int x) {
    int r = 0;
    while (x > 0) {
        r += c[x];
        x -= lbt(x);
    }
    return r;
}

//扩展KMP算法，计算z函数的值
//可以参考良心博客 https://www.luogu.com.cn/blog/nitubenben/solution-p5410
void Z() {
    z[0] = n;
    int now = 0;
    while (now + 1 < n && s[now] == s[now + 1]) {
        now++;
    }
    z[1] = now;
    int p0 = 1;
    for (int i = 2; i < n; ++i) {
        if (i + z[i - p0] < p0 + z[p0]) {
            z[i] = z[i - p0];
        } else {
            now = p0 + z[p0] - i;
            now = max(now, 0);
            while (now + i < n && s[now] == s[now + i]) {
                now++;
            }
            z[i] = now;
            p0 = i;
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        n = strlen(s);
        memset(before, 0, sizeof(before));
        memset(after, 0, sizeof(after));
        memset(c, 0, sizeof(c));
        all = pre = suf = 0;
        Z();
        //如果发现循环节可以到结尾，减1，空至少一个位置给C
        for (int i = 0; i < n; ++i) {
            if (i + z[i] == n) z[i]--;
        }
        //先把字符串过一遍，频次统计到after数组里面
        for (int i = 0; i < n; ++i) {
            after[s[i] - 'a']++;
        }
        //扫一下每个字母，计算整个串中出现奇数次的字符的个数
        for (int i = 0; i < 26; ++i) {
            if (after[i] & 1) {
                all++;
            }
        }
        suf = all;//后缀中的值暂时和整个串一致
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            //再扫一次字符串，当循环到i位置的时候，循环节长度是i+1
            //s[i]要从右边去掉，维护after数组和suf变量
            if (after[s[i] - 'a'] & 1) {
                //之前是奇数，现在变成偶数了
                suf--;
            } else {
                suf++;
            }
            after[s[i] - 'a']--;
            //s[i]加到左边，维护before和pre变量
            if (before[s[i] - 'a'] & 1) {
                pre--;
            } else {
                pre++;
            }
            before[s[i] - 'a']++;
            if (i != 0 && i != n - 1) {
                //循环节大于1,才能对答案有贡献，因为题中说ABC都不为空
                int t = z[i + 1] / (i + 1) + 1;
                ans += 1LL * (t / 2) * sum(all + 1) + 1LL * (t - t / 2) * sum(suf + 1);
            }
            update(pre + 1);
        }
        cout << ans << endl;
    }
    return 0;
}
