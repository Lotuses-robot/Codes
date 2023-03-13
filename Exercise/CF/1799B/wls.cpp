
#include<bits/stdc++.h>
// #include<bits/extc++.h>
#define double long double
using namespace std;
// using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<typename T>
void read(T &x)
{
    x=0;char last='w',ch=getchar();
    while (ch<'0'  ||  ch>'9') last=ch,ch=getchar();
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    if  (last=='-') x=-x;
}
template<typename T,typename... Args>
void read(T &x,Args &...args) { read(x),read(args...); }
template<typename T>
void write_(T x)
{
    if  (x<0) putchar('-'),x=-x;
    if  (x<10) putchar(x+'0');
    else write_(x/10),putchar(x%10+'0');
}

template<typename T>
void write(T x) { write_(x),putchar(' '); }
template<typename T,typename... Args>
void write(T x,Args ...args) { write(x),write(args...); }
template<typename T>
void writeln(T x) { write_(x),putchar('\n'); }
template<typename T,typename... Args>
void writeln(T x,Args ...args) { write(x),write(args...),putchar('\n'); }

template<typename T>
T Max(T x) { return x; }
template<typename T,typename... Args>
T Max(T x,Args ...args) { T y=Max(args...); return x>y ? x : y; }
template<typename T>
T Min(T x) { return x; }
template<typename T,typename... Args>
T Min(T x,Args ...args) { T y=Min(args...); return x>y ? y : x; }

const int MAXn=1000;
const double INF=1e18;

int n,k,Id[MAXn+10];
double Dis[MAXn+10][MAXn+10],F[MAXn+10][MAXn+10][2];
double Pre[MAXn+10][MAXn+10][2];
struct Node { double x,y; }A[MAXn+10],B[MAXn+10];
double Dist(int q,int p) { return sqrt((B[q].x-B[p].x)*(B[q].x-B[p].x)+(B[q].y-B[p].y)*(B[q].y-B[p].y));}
void write_ans()
{
    int l=1,r=n-1,mode=(F[1][n-1][0]+Dist(1,n)>F[1][n-1][1]+Dist(n-1,n));
    write(k);
    while (1)
    {
        write(Id[(mode==0)?(l):(r)]);
        if (l==r) return;
        l+=(mode^1),r-=mode,mode=Pre[l-(mode^1)][r+mode][mode];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
#endif
    
    read(n);
    for (int i=1;i<=n;i++) scanf("%Lf%Lf",&A[i].x,&A[i].y);
    for (int i=1;i<=n;i++)
        if (!k || A[i].y>A[k].y) k=i;
    for (int i=k+1;i<=n;i++) B[i-k]=A[i],Id[i-k]=i;
    for (int i=1;i<=k-1;i++) B[n-k+i]=A[i],Id[n-k+i]=i;
    B[n]=A[k];
        
    for (int len=2;len<n;++len)
        for (int l=1,r=l+len-1;r<n;++l,++r)
        {
            F[l][r][0]=F[l][r][1]=INF;
            if (F[l][r][0]>F[l+1][r][0]+Dist(l+1,l))
                F[l][r][0]=F[l+1][r][0]+Dist(l+1,l),Pre[l][r][0]=0;
            if (F[l][r][0]>F[l+1][r][1]+Dist(r,l))
                F[l][r][0]=F[l+1][r][1]+Dist(r,l),Pre[l][r][0]=1;
            if (F[l][r][1]>F[l][r-1][0]+Dist(l,r))
                F[l][r][1]=F[l][r-1][0]+Dist(l,r),Pre[l][r][1]=0;
            if (F[l][r][1]>F[l][r-1][1]+Dist(r-1,r))
                F[l][r][1]=F[l][r-1][1]+Dist(r-1,r),Pre[l][r][1]=1;
        }
        
    write_ans();
    
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
