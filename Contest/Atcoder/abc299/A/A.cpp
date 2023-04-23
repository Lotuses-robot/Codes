/*
You are given a string 
S of length 
N consisting of three kinds of characters: ., |, and *. 
S contains exactly two | and exactly one *.

Determine whether the * is between the two |, and if so, print in; otherwise, print out.

More formally, determine whether one of the characters before the * is | and one of the characters after the * is |.


.|..*...|.

 in

*/
#include <cstdio>
#include <cstring>
#include <vector>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

char ch[100];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int len;
    scanf("%d%s", &len, ch + 1);
    int pos = 0, pl = 0, pr = 0;
    for (int i = 1; i <= len; ++i) {
        // putchar(ch[i]);
        if (ch[i] == '*') {
            pos = i;
        }
        if (ch[i] == '|' && pl == 0) {
            pl = i;
        } else if (ch[i] == '|') {
            pr = i;
        }
    }
    if (pl < pos && pos < pr) {
        puts("in");
    } else {
        puts("out");
    }
    return 0;
}
