// 1713D 
#include <cstdio>
#include <vector>

int query(int a, int b) {
    printf("? %d %d\n", a, b);
    fflush(stdout); int q;
    scanf("%d", &q);
    return q;
}
// 1 means a > b
// 2 means a < b
// 0 means a = b

std::vector<int> v, re;

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 1; i <= (1 << n); i++) {
            v.push_back(i);
        }

        while (v.size() >= 4) {
            for (int i = 0; i < v.size(); i += 4) {
                int r = query(v[i], v[i + 3]);
                if (r == 0) {
                    r = query(v[i + 1], v[i + 2]);
                    if (r == 1) {
                        re.push_back(v[i + 1]);
                    } else {
                        re.push_back(v[i + 2]);
                    }
                } else if (r == 1) { // a > d
                    r = query(v[i], v[i + 2]);
                    if (r == 1) {
                        re.push_back(v[i]);
                    } else {
                        re.push_back(v[i + 2]);
                    }
                } else if (r == 2) { // a < d
                    r = query(v[i + 1], v[i + 3]);
                    if (r == 1) {
                        re.push_back(v[i + 1]);
                    } else {
                        re.push_back(v[i + 3]);
                    }
                }
            }
            v.clear();
            v = re;
            re.clear();
        }
        if (v.size() != 1) {
            int r = query(v[0], v[1]);
            if (r == 2) {
                v[0] = v[1];
            }
        }
        printf("! %d\n", v[0]);
        fflush(stdout);
        v.clear();
    }
    return 0;
}