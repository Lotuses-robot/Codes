#include<cstdio>
#include<cstring>
#define RI register int
#define CI const int&
#define Ms(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=15,multag[2]={-1,1};
const int length[12]={3,4,4,4,5,5,5,5,5,5,5,5}; //length of shapes
const int table[12][5][2]= //direction of shapes
{
    {{0,0},{1,0},{0,1}}, //A
    {{0,0},{0,1},{0,2},{0,3}}, //B
    {{0,0},{1,0},{0,1},{0,2}}, //C
    {{0,0},{1,0},{0,1},{1,1}}, //D
    {{0,0},{1,0},{2,0},{2,1},{2,2}}, //E
    {{0,0},{0,1},{1,1},{0,2},{0,3}}, //F
    {{0,0},{1,0},{0,1},{0,2},{1,2}}, //G
    {{0,0},{1,0},{0,1},{1,1},{0,2}}, //H
    {{0,0},{0,1},{0,2},{1,2},{1,3}}, //I
    {{0,0},{-1,1},{0,1},{1,1},{0,2}}, //J
    {{0,0},{1,0},{1,1},{2,1},{2,2}}, //K
    {{0,0},{1,0},{0,1},{0,2},{0,3}}, //L
};
const int numx[56]={0,1,2,2,3,3,3,4,4,4,4,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10};
const int numy[56]={0,1,1,2,1,2,3,1,2,3,4,1,2,3,4,5,1,2,3,4,5,6,1,2,3,4,5,6,7,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,10};
int tx[2],nx[2],num[N][N],id[2750],numrow,numcol; char puzzle[N][N]; bool vis[N];
class Dancing_Links_AlgorithmX
{
    private:
        static const int N=2750,M=80,ALL=15100;
        int n,m,tot,L[ALL],R[ALL],U[ALL],D[ALL],Row[ALL],Col[ALL],H[N],S[M];
        #define Dance(i,A,s) for (i=A[s];i!=s;i=A[i])
        inline void remove(CI c)
        {
            L[R[c]]=L[c]; R[L[c]]=R[c]; RI i,j;
            Dance(i,D,c) Dance(j,R,i)
            U[D[j]]=U[j],D[U[j]]=D[j],--S[Col[j]];
        }
        inline void resume(CI c)
        {
            RI i,j; Dance(i,U,c) Dance(j,L,i)
            ++S[Col[U[D[j]]=D[U[j]]=j]];
            L[R[c]]=R[L[c]]=c;
        }
    public:
        inline void init(CI N,CI M)
        {
            n=N; m=M; for (RI i=0;i<=m;++i)
            S[i]=0,U[i]=D[i]=i,L[i]=i-1,R[i]=i+1;
            R[m]=0; L[0]=m; tot=m; Ms(H,0);
        }
        inline void link(CI r,CI c)
        {
            ++S[Col[++tot]=c]; Row[tot]=r;
            D[tot]=D[c]; U[D[c]]=tot; U[tot]=c; D[c]=tot;
            if (!H[r]) H[r]=L[tot]=R[tot]=tot; else
            R[tot]=R[H[r]],L[R[H[r]]]=tot,L[tot]=H[r],R[H[r]]=tot;
        }
        inline bool DFS(void)
        {
            if (!R[0]) return 1; RI i,j; int now=R[0];
            Dance(i,R,0) if (S[i]<S[now]) now=i;
            remove(now); Dance(i,D,now)
            {
                if (Col[i]<=55) puzzle[numx[Col[i]]][numy[Col[i]]]=id[Row[i]]+'A';
                Dance(j,R,i) remove(Col[j]),(Col[j]<=55)&&(puzzle[numx[Col[j]]][numy[Col[j]]]=id[Row[j]]+'A');
                if (DFS()) return 1; Dance(j,L,i) resume(Col[j]);
            }
            resume(now); return 0;
        }
        #undef Dance
}DLX;
inline void init(void)
{
    RI i,j; for (i=1;i<=10;++i) for (j=1;j<=i;++j) if (puzzle[i][j]!='.') vis[puzzle[i][j]-'A']=1;
    for (i=1;i<=10;++i) for (j=1;j<=i;++j) num[i][j]=++numcol; DLX.init(2730,numcol+12);
}
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    RI i; for (i=1;i<=10;++i) scanf("%s",puzzle[i]+1);
    //build excat cover model
    init(); for (RI cases=0,mx;cases<12;++cases)
    for (++numcol,mx=0;mx<2;++mx) for (RI dx=0;dx<2;++dx) for (RI dy=0;dy<2;++dy)
    for (tx[0]=1;tx[0]<=10;++tx[0]) for (tx[1]=1;tx[1]<=tx[0];++tx[1])
    {
        RI k; bool flag=1; for (k=0;k<length[cases];++k)
        {
            nx[mx]=tx[mx]+multag[dx]*table[cases][k][0];
            nx[mx^1]=tx[mx^1]+multag[dy]*table[cases][k][1];
            if (vis[cases]) { if (puzzle[nx[0]][nx[1]]!=cases+'A') { flag=0; break; } }
            else if (puzzle[nx[0]][nx[1]]!='.') { flag=0; break; }
        }
        if (!flag) continue; id[++numrow]=cases; DLX.link(numrow,numcol);
        for (k=0;k<length[cases];++k)
        {
            nx[mx]=tx[mx]+multag[dx]*table[cases][k][0];
            nx[mx^1]=tx[mx^1]+multag[dy]*table[cases][k][1];
            DLX.link(numrow,num[nx[0]][nx[1]]);
        }
    }
    //use Dancing Links to find solution
    if (!DLX.DFS()) return puts("No solution"),0;
    for (i=1;i<=10;++i,putchar('\n')) for (RI j=1;j<=i;++j)
    putchar(puzzle[i][j]); return 0;
}
