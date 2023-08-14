#include<bits/stdc++.h>
using namespace std;
#define re register
#define rep( i, s, t ) for( re int i = s; i <= t; ++ i ) 
#define Next( i, x ) for( re int i = head[x]; i; i = e[i].next ) 
int read() {
    char cc = getchar(); int cn = 0, flus = 1;
    while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
    while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
    return cn * flus;
}

const int N = 5e5 + 5;
int head[N], dfn[N], low[N], s[N], cnt, n, m, top, tim, col, color[N];
int stac[N], top2, d, suit[N], ch[N][2];
struct E {
    int to, next;
}e[N * 2];
struct Node{
    int x, hx, y, hy;
}q[N];
char S[N];

void add( int x, int y ) {
    e[++cnt] = (E) { y, head[x] }, head[x] = cnt;
} 
void trajan( int x ) {
    dfn[x] = low[x] = ++tim, s[++ top] = x;
    Next( i, x ) {
        int v = e[i].to;
        if( !dfn[v] )  trajan( v ), low[x] = min( low[x], low[v] );
        else if( !color[v] )  low[x] = min( low[x], dfn[v] );
    }
    if( low[x] == dfn[x] ) {
        ++ col;
        while( s[top + 1] != x ) color[s[top--]] = col;
    }
} 

void doit() {
    memset( head, 0, sizeof(head) ), memset( dfn, 0, sizeof(dfn) );
    memset( low, 0, sizeof(low) ), memset( color, 0, sizeof(color) );
    cnt = tim = top = col = 0;
    rep( i, 1, m ) {
        int x = q[i].x, y = q[i].y, u = x + q[i].hx * n, v = y + q[i].hy * n;
        if( q[i].hx == suit[x] ) continue;
        if( q[i].hy == suit[y] ) {
            add( ch[x][ch[x][1] == u], ch[x][ch[x][1] != u] ); 
        }
        else add( u, v ), add( ch[y][ch[y][1] != v], ch[x][ch[x][1] != u]);
    }
    rep( i, 1, n ) {  if( !dfn[ch[i][0]] ) trajan( ch[i][0] );  if( !dfn[ch[i][1]] ) trajan( ch[i][1] );  }
    rep( i, 1, n ) if( color[ch[i][0]] == color[ch[i][1]] ) return ;
    rep(i, 1, n) {
        if( color[ch[i][0]] > color[ch[i][1]] ) printf("%c", ( ( ch[i][1] - 1 ) / n ) + 'A'  );
        else printf("%c", ( ( ch[i][0] - 1 ) / n ) + 'A' );
    }
    exit(0);
}
void dfs( int x ) {
    if( x > d ) {
        doit();
        return ;
    }
    int now = stac[x];
    suit[now] = 0, ch[now][0] = now + n, ch[now][1] = now + 2 * n,
    dfs( x + 1 );
    suit[now] = 1, ch[now][0] = now, ch[now][1] = now + 2 * n;
    dfs( x + 1 );
}
signed main()
{
    n = read(), d = read();
    scanf( "%s", S );
    int len = strlen(S);
    rep( i, 0, len - 1 ) {
        int now = i + 1;
        if( S[i] == 'x' ) stac[++top2] = now;
        if( S[i] == 'a' ) suit[now] = 0, ch[now][0] = now + n, ch[now][1] = now + 2 * n;
        if( S[i] == 'b' ) suit[now] = 1, ch[now][0] = now, ch[now][1] = now + 2 * n;
        if( S[i] == 'c' ) suit[now] = 2, ch[now][0] = now, ch[now][1] = now + n; 
    }
    m = read();
    rep( i, 1, m )
        q[i].x = read(), q[i].hx = getchar() - 'A', q[i].y = read(), q[i].hy = getchar() - 'A';
    dfs( 1 );
    printf("-1");
    return 0;
} 