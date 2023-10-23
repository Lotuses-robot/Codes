// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
// #include <set>
// #include <list>
// #include <queue>
#include <string>
#include <iostream>
// #include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define ins(a, b) (G[a].emplace_back(b))

#define int long long

struct Type {
    struct subType {
        std::string tyname, name;
        int l, r;
    };
    std::string tyname;
    int a, s;
    std::vector<subType> v;
};
std::map<std::string, Type> tp;
std::vector<Type::subType> ram;
int pter = 0;

#define ceil(x, y) ((x) % (y) ? (x) / (y) + 1 : (x) / (y))

void inittype() {
    tp["byte"] = { "byte", 1, 1 };
    tp["short"] = { "short", 2, 2 };
    tp["int"] = { "int", 4, 4 };
    tp["long"] = { "long", 8, 8 };
}

std::vector<std::string> ret;
void split(std::string s) {
    ret.clear(); int i = 0;
    while (i < s.length()) {
        if (s[i] == '.') {
            ret.push_back(s.substr(0, i));
            s = s.substr(i + 1);
            i = 0;
            continue;
        }
        i++;
    }
    ret.push_back(s);
}


tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    inittype();
    std::string s, t1, n1;

    int n, k;
    read(n);
    while (n--) {
        int op;
        read(op);
        if (op == 1) {
            std::cin >> s; read(k);
            Type t;
            t.tyname = s; t.a = 0;
            int end = 0;
            for (int i = 1; i <= k; i++) {
                std::cin >> t1 >> n1;
                const auto &p = tp[t1]; int o = ceil(end, p.a) * p.a;
                Type::subType pt = {t1, n1, o, o + p.s - 1};
                t.v.push_back(pt); t.a = std::max(t.a, p.a);
                end = pt.r + 1;
            }
            t.s = ceil(end, t.a) * t.a;
            tp[s] = t;
            writeln(t.s, t.a);
        } else if (op == 2) {
            std::cin >> t1 >> n1;
            const auto &p = tp[t1]; int o = ceil(pter, p.a) * p.a;
            ram.push_back({t1, n1, o, o + p.s - 1});
            pter = o + p.s;
            writeln(o);
        } else if (op == 3) {
            std::cin >> s;
            // puts("???");
            split(s);
            int addr = 0;
            for (auto x : ram) {
                if (x.name == ret[0]) {
                    addr = x.l;
                    t1 = x.tyname;
                    break;
                }
            }
            for (int i = 1; i < ret.size(); i++) {
                const Type &p = tp[t1];
                for (auto x : p.v) {
                    if (x.name == ret[i]) {
                        addr += x.l;
                        t1 = x.tyname;
                        break;
                    }
                }
            }
            writeln(addr);
        } else if (op == 4) {
            ret.clear();
            int addr;
            read(addr);
            bool ERR = true;
            for (auto x : ram) {
                if (addr >= x.l && addr <= x.r) {
                    t1 = x.tyname;
                    addr -= x.l;
                    ret.emplace_back(x.name);
                    ERR = false;
                    break;
                }
            }
            if (ERR) { puts("ERR"); continue; }
            while (!tp[t1].v.empty()) {
                ERR = true;
                // if (addr <= 0) break;
                // writeln(addr);
                const Type &p = tp[t1];
                for (auto x : p.v) {
                    // writeln(x.l, x.r);
                    if (addr >= x.l && addr <= x.r) {
                        t1 = x.tyname;
                        addr -= x.l;
                        ret.emplace_back(x.name);
                        ERR = false;
                        break;
                    }
                }
                if (ERR) {
                    puts("ERR"); break;
                }
            }
            if (!ERR) {
                for (int i = 0; i < ret.size() - 1; i++) {
                    printf("%s.", ret[i].c_str());
                }
                puts(ret.back().c_str());
            }
        }
    }
    return 0;
}