#include <cstdio>

const int maxn = 100000;

int n = 1000;

struct fw {
    int arr[maxn * 4];
    int lowbit(int x) {
        return x & (-x);
    }
    void add(int x, int a) {
        while (x <= n) {
            arr[x] += a;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ans = 0;
        while (x > 0) {
            ans += arr[x];
            x -= lowbit(x);
        }
        return ans;
    }
} fenw;

int main() {
    fenw.add( 2, 7);
    fenw.add( 6, 6566);
    fenw.add(7, 123);
    fenw.add(8, 127);
    printf("%d\n", fenw.query(7) - fenw.query(2));
}