#include "testlib.h"
#include <cstring>
#include <cstdio>

const int maxn = 10004;
char x[maxn], y[maxn];
std::string s;
int k, xp, yp;

int readLineInt() {
    std::string s = inf.readLine(); static int r;
    sscanf(s.c_str(), "%d", &r);
    return r;
}

int getX(int u) {
    if (u < 1) {
        return 0;
    } else {
        return x[u] - '0';
    }
}
int getY(int u) {
    if (u < 1) {
        return 0;
    } else {
        return y[u] - '0';
    }
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    
    int T = readLineInt(); int t = T;
    while (T--) {
        s = inf.readLine();
        xp = s.length();
        strcpy(x + 1, s.c_str());
        k = readLineInt();
        s = ans.readLine();
        yp = s.length();
        strcpy(y + 1, s.c_str());

        int cnt = 0, nxt = 0;
        while (xp >= 1) {
            static int t; t = getX(xp) + getY(yp) + nxt;
            
            nxt = t / 10; t %= 10;
            cnt += nxt;
            // printf("%d %d\n", x[xp], y[yp]);
            xp--; yp--;
        }
    
        if (cnt != k) {
            quitf(_wa, "%d %d %d.", t - T, cnt, k);
        }
    }
    quit(_ok, "Accepted.");
}