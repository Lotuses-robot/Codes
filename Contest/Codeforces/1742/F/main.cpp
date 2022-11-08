    // Copyright 2022 Lotuses
    #include <cstdio>
    #include <cstring>
    #include <vector>

    #define int long long

    #define gc getchar()
    template<typename T>
    void read(T &r) { // NOLINT
        r = 0; static char ch, last; // NOLINT
        ch = gc, last = 'z';
        while (ch < '0' || ch > '9') last = ch, ch = gc;
        while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
        r = (last == '-') ? -r : r;
    }

    template<typename T, typename...Ts>
    void read(T &arg, Ts&...arg_left) { // NOLINT
        read(arg);
        read(arg_left...);
    }

    int tot[2][114];
    char ch[514514];
    int cnt[114];

    bool add(int d, int k) {
        int len = strlen(ch);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < len; i++) {
            cnt[ch[i] - 'a']++;
        }

        for (int i = 0; i < 26; i++) {
            tot[d][i] += cnt[i] * k;
        }

        int i = 0, j = 25;
        while (tot[0][i] == 0) i++;
        while (tot[1][j] == 0) j--;
        // printf("%d %d\n", i, j);
        if (i > j) {
            return false;
        } else if (i == j) {
            if (tot[0][i] >= tot[1][j]) {
                return false;
            } else {
                bool flag = false;
                for (int j = i + 1; j < 26; j++) {
                    flag |= tot[0][j];
                }
                if (flag) {
                    return false;
                } else {
                    return true;
                }
            }
        } else {
            return true;
        }
    }

    signed main() {
        int T;
        read(T);

        while (T--) {
            memset(tot, 0, sizeof(tot));
            tot[0][0]++;
            tot[1][0]++;
            int q;
            read(q);
            while (q--) {
                int d, k;
                read(d, k);
                scanf("%s", ch);
                puts(add(d - 1, k) ? "YES" : "NO");
            }
        }
        return 0;
    }
