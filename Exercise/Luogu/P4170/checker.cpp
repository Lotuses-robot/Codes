#include <cstdio>
#include <cstring>
#include <string>
#include <windows.h>

void check(std::string str) {
    static char my[1001],ans[1001];

    FILE *f = fopen("P4170.in", "w+");
    fprintf(f, "%s", str.c_str());
    fclose(f);

    // get std ans
    system("std.exe");
    f = fopen("P4170.out.std", "r");
    fscanf(f, "%s", ans);
    fclose(f);

    // get my ans
    system("P4170.exe");
    f = fopen("P4170.out", "r");
    fscanf(f, "%s", my);
    fclose(f);

    if (strcmp(my, ans) != 0) {
        printf("%s Not OK!\n", str.c_str());
    } else {
        printf("%s OK\n", str.c_str());
    }
}

const char cg[3] = {'R','G','B'};

void dfs(int len, std::string str)
{
    if (len > 10) return;
    if (len != 0) {
        check(str);
    }

    for (int i = 0; i < 3; i++) {
        dfs(len + 1, str + cg[i]);
    }
}

int main() {
    dfs(0,"");
    return 0;
}