// Copyright 2023 Lotuses
#include <bits/stdc++.h>

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

// #define __DEBUG
    #ifdef __DEBUG
    #define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
    #define debug(arg, args...) {}
#endif

typedef unsigned long long ull;
const int S=64;
struct integer{
	mutable unsigned a[S];
	integer(int i=0):a(){
		a[0]=i;
	}
	unsigned &operator[](int i)const{
		return a[i];
	}
};
const unsigned mask=(1u<<31)-1;
bool operator<(const integer &a,const integer &b){
	for(int i=S-1;i>=0;--i)
		if(a[i]!=b[i])
			return a[i]<b[i];
	return false;
}
integer operator<<(const integer &a,int b){
	integer r;
	int quo=b/31,rem=b%31;
	r[quo]=((a[0]<<rem)&mask);
	for(int i=quo+1;i<S;++i)
		r[i]=(((a[i-quo]<<rem)|(a[i-quo-1]>>(31-rem)))&mask);
	return r;
}
void operator+=(integer &a,const integer &b){
	unsigned s=0;
	for(int i=0;i<S;++i){
		s+=a[i]+b[i];
		a[i]=(s&mask);
		s>>=31;
	}
}
integer operator+(integer a,const integer &b){
	a+=b;
	return a;
}
void operator-=(integer &a,const integer &b){
	int s=0;
	for(int i=0;i<S;++i){
		s+=a[i]-b[i];
		a[i]=(s&mask);
		s>>=31;
	}
}
integer operator-(integer a,const integer &b){
	a-=b;
	return a;
}
integer operator*(const integer &a,const integer &b){
	integer r;
	for(int i=0;i<S;++i){
		if(a[i]==0)
			continue;
		ull s=0;
		for(int j=i;j<S;++j){
			s+=(ull)a[i]*b[j-i]+r[j];
			r[j]=(s&mask);
			s>>=31;
		}
	}
	return r;
}
integer operator/(integer a,const integer &b){
	integer r;
	int high;
	for(high=S*31-1;high>=0;--high)
		if((b[high/31]>>(high%31))&1)
			break;
	assert(high>=0);
	bool any=false;
	for(int cur=S*31-1-high;cur>=0;--cur){
		if(!any&&((a[(cur+high)/31]>>((cur+high)%31))&1)==0)
			continue;
		any=true;
		integer s=(b<<cur);
		if(!(a<s)){
			a-=s;
			r[cur/31]|=(1u<<(cur%31));
		}
	}
	return r;
}
struct fixed_point{
	bool sign;
	integer i;
	fixed_point(int i=0):fixed_point(i<0,integer(abs(i))<<(S/4*31)){
	}
	fixed_point(bool sign,integer i):sign(sign),i(i){
	}
};
fixed_point operator+(const fixed_point &a,const fixed_point &b){
	if(a.sign!=b.sign){
		if(a.i<b.i)
			return fixed_point(b.sign,b.i-a.i);
		else
			return fixed_point(a.sign,a.i-b.i);
	}
	return fixed_point(a.sign,a.i+b.i);
}
fixed_point operator-(const fixed_point &a,const fixed_point &b){
	return a+fixed_point(!b.sign,b.i);
}
void operator-=(fixed_point &a,const fixed_point &b){
	a=a-b;
}
fixed_point operator-(const fixed_point &a){
	return fixed_point(!a.sign,a.i);
}
void operator/=(fixed_point &a,const fixed_point &b){
	a.sign^=b.sign;
	a.i=(a.i<<(S/4*31))/b.i;
}
fixed_point operator*(const fixed_point &a,const fixed_point &b){
	fixed_point r;
	r.sign=(a.sign^b.sign);
	memcpy(r.i.a, (a.i*b.i).a+S/4, sizeof(unsigned)*(S/2));
	return r;
}
fixed_point operator/(fixed_point a,const fixed_point &b){
	a/=b;
	return a;
}
bool operator<(const fixed_point &a,const fixed_point &b){
	if(a.sign!=b.sign)
		return a.sign;
	if(a.sign)
		return b.i<a.i;
	else
		return a.i<b.i;
}
istream &operator>>(istream &in,fixed_point &val){
	int i;
	in>>i;
	val.sign=(i<0);
	val.i=(integer(abs(i))<<(S/4*31));
	return in;
}
ostream &operator<<(ostream &out,const fixed_point &val){
	long double r=0;
	for(int i=S-1;i>=0;--i)
		r=r*(1u<<31)+val.i[i];
	for(int i=0;i<S/4;++i)
		r/=(1u<<31);
	return out<<((val.sign?-1:1)*r);
}
fixed_point eps=fixed_point(false,integer(1)<<(4*31));

const int maxn = 60;
const fixed_point eps = 1e-8;
fixed_point a[maxn][maxn], b[maxn], cb[maxn], c[maxn], ct[maxn], cz[maxn];
int n, m, t, x[maxn];

int posx;
void check() {
    posx = -1;
    for (int i = 1; i <= n; i++) {
        cz[i] = c[i];
        for (int j = 1; j <= m; j++) {
            cz[i] -= cb[j] * a[j][i];
        }
        if (posx == -1 || cz[posx] < cz[i]) {
            posx = i;
        }
    }
    return cz[posx];
}

int posy;
void find() {
    posy = -1;
    for (int i = 1; i <= m; i++) {
        if (fabs(a[i][posx]) <= eps) { ct[i] = -1; continue; }
        if (a[i][posx] < 0) { ct[i] = -1; continue; }
        ct[i] = b[i] / a[i][posx];
        // write(666); putchar(' '); printf("%.1lf\n", a[i][posx]);
        if (posy == -1 || ct[posy] > ct[i]) {
            posy = i;
        }
    }
}

void upd() {
    fixed_point div = a[posy][posx];
    for (int i = 1; i <= n; i++) {
        a[posy][i] /= div;
    }
    b[posy] /= div;
    cb[posy] = c[posx];
    for (int i = 1; i <= m; i++) {
        if (i == posy) continue;
        fixed_point w = a[i][posx];
        for (int j = 1; j <= n; j++) {
            a[i][j] -= w * a[posy][j];
        }
        b[i] -= b[posy] * w;
    }
    x[posy] = posx;
}

void print() {
    puts("Cj"); for (int i = 1; i <= n; i++) printf("%.1lf", c[i]), putchar(' '); puts("");
    puts("CB"); for (int i = 1; i <= m; i++) printf("%.1lf", cb[i]), putchar(' '); puts("");
    puts("Xid"); for (int i = 1; i <= m; i++) printf("%.1lf", x[i]), putchar(' '); puts("");
    puts("b"); for (int i = 1; i <= m; i++) printf("%.1lf", b[i]), putchar(' '); puts("");
    puts("cz"); for (int i = 1; i <= n; i++) printf("%.1lf", cz[i]), putchar(' '); puts("");
    puts("ct"); for (int i = 1; i <= m; i++) printf("%.1lf", ct[i]), putchar(' '); puts("");
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%.1lf", a[i][j]); putchar(' ');
        }
        puts("");
    }
}

int bg;
bool prepare() {
    while (1) {
        posx = posy = 0;
        for (int i = 1; i <= m; i++) if (b[i] < -eps) { posy = i; }
        if (!posy) break;
        for (int i = 1; i <= n; i++) if (a[posy][i] < -eps) { posx = i; }
        if (!posx) {
            puts("Infeasible");
            return false;
        }
        upd();
        // writeln(posy, posx);
        // print();
    }
    return true;
}

fixed_point ansl[maxn];

int main() {
    #ifdef LOCAL
        freopen("data.in", "r", stdin);
        freopen("data.out", "w", stdout);
    #endif
    
    std::cout << std::fixed << std::setprecision(9);
    srand(time(0));
    int l;
    read(n, m, t);
    for (int i = 1; i <= n; i++) read(l), c[i] = l;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            read(l); a[i][j] = l;
        }
        read(l);
        b[i] = l;
    }
    for (int i = 1; i <= m; i++) {
        a[i][n + i] = 1;
        x[i] = n + i;
    }
    n += m;
    // print();


    if (!prepare()) return 0;

    while (check() > eps) {
        find();
        if (posy == -1) {
            puts("Unbounded");
            return 0;
        }
        upd();
        // print();
        // writeln(posx);
    }
    
    fixed_point ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += b[i] * cb[i];
    }
    // std::cout << ans << std::endl;
    // print();
    if (!t) return 0;

    for (int i = 1; i <= m; i++) {
        ansl[x[i]] = b[i];
    }
    for (int i = 1; i <= n - m; i++) {
        // std::cout << ansl[i] << " ";
    }
    puts("");
    return 0;
}
