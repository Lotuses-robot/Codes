/*
N players with ID numbers 
1,2,…,N are playing a card game.
Each player plays one card.

Each card has two parameters: color and rank, both of which are represented by positive integers.
For 
i=1,2,…,N, the card played by player 
i has a color 
C 
i
​
  and a rank 
R 
i
​
 . All of 
R 
1
​
 ,R 
2
​
 ,…,R 
N
​
  are different.

Among the 
N players, one winner is decided as follows.

If one or more cards with the color 
T are played, the player who has played the card with the greatest rank among those cards is the winner.
If no card with the color 
T is played, the player who has played the card with the greatest rank among the cards with the color of the card played by player 
1 is the winner. (Note that player 
1 may win.)
Print the ID number of the winner.

Constraints
2≤N≤2×10 
5
 
1≤T≤10 
9
 
1≤C 
i
​
 ≤10 
9
 
1≤R 
i
​
 ≤10 
9
 
i

=j⟹R 
i
​
 

=R 
j
​
 
```input
4 2
1 2 1 2
6 3 4 5

```

```output
4
```

All values in the input are integers.
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

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

int c[200005], r[200005];
struct Node {
    int r, id;
};
std::map<int, std::vector<Node> > v; 
std::vector<int> allc;
std::vector<Node> all;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, t;
    read(n, t);
    for (int i = 1; i <= n; i++) {
        read(c[i]);
        allc.push_back(c[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(r[i]);
        v[c[i]].push_back({r[i], i});
        all.push_back({r[i], i});
    }
    

    if (v[t].size() != 0) {
        std::sort(v[t].begin(), v[t].end(), [](const Node &a, const Node &b) { return a.r > b.r; });
        writeln(v[t][0].id);
        return 0;
    } else {
        t = c[1];
        std::sort(v[t].begin(), v[t].end(), [](const Node &a, const Node &b) { return a.r > b.r; });
        writeln(v[t][0].id);
        // std::sort(all.begin(), all.end(), [](const Node &a, const Node &b) { return a.r > b.r; });
        // writeln(v[t][0].id);
        return 0;
    }

    
    return 0;
}
