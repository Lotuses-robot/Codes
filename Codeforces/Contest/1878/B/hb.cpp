#include <bits/stdc++.h>
using namespace std ;

#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define fi first
#define se second
#define pb push_back
#define pf push_front
#define eb emplace_back
#define mp make_pair
#define lwb lower_bound
#define upb upper_bound
#define bitc(n) __builtin_popcountll(n)
#define gcd __gcd
#define lg __lg

#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()
#define speedy cin.tie(0) ; cout.tie(0)
#define fastio ios_base::sync_with_stdio(0) ; speedy ;

template<class X, class Y> bool maximize(X &x, const Y &y) {return (x < y ? x = y, 1 : 0) ;}
template<class X, class Y> bool minimize(X &x, const Y &y) {return (x > y ? x = y, 1 : 0) ;}

const ll mod = 1e9 + 7 ;
const ll INF = 1e9 ;
const int N = (int)2e5 ;

/* Some Peach Tea Is Great ;-; */
/* Author : Tuandq */

int a[N + 5], t, n ;

int main() {
    fastio
    a[1] = 6 ; a[2] = 8 ;
    for(int i = 3; i <= N; i ++) {
        a[i] = a[i - 1] + 1 ;
        while((a[i] * 3) % (a[i - 1] + a[i - 2]) == 0) ++ a[i] ;
    }
    cin >> t ;
    while(t --) {
        cin >> n ;
        for(int i = 1; i <= n; i ++) cout << a[i] << ' ' ;
        cout << '\n' ;
    }
}
