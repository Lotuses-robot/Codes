#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

#define isdigit(ch) ((ch) >= '0' && (ch) <= '9')

int main(int argc, char *argv[]) {
    char path[1145];
    int i = 0, len = strlen(argv[1]), j;
    for (i = 0; i < len && isdigit(argv[1][i]); i++);

    path[0] = argv[1][i];
    argv[1][i] = 0;
    i++;
    for (j = 1; i < len; i++, j++) path[j] = argv[1][i];

    path[j] = 0;

    char cmd[1145], sw;
    printf("dir D:\\Robot\\C++\\myCode\\Codeforces\\%s\\%s will make, [y]es? ", argv[1], path);
    std::cin >> sw;
    if (sw != 'y') return 0;
    sprintf(cmd, "mkdir D:\\Robot\\C++\\myCode\\Codeforces\\%s\\%s ", argv[1], path);
    system(cmd);

    printf("file sol.md & sol.cpp will make, [y]es? ");
    std::cin >> sw;
    if (sw != 'y') return 0;
    sprintf(cmd, "echo // %s%s > D:\\Robot\\C++\\myCode\\Codeforces\\%s\\%s\\sol.cpp", argv[1], path, argv[1], path);
    system(cmd);
    
    sprintf(cmd, "echo # sol for %s%s > D:\\Robot\\C++\\myCode\\Codeforces\\%s\\%s\\sol.md", argv[1], path, argv[1], path);
    system(cmd);

    sprintf(cmd, "start D:\\Robot\\C++\\myCode\\Codeforces\\%s\\%s\\sol.cpp", argv[1], path);
    system(cmd);
    sprintf(cmd, "start D:\\Robot\\C++\\myCode\\Codeforces\\%s\\%s\\sol.md", argv[1], path);
    system(cmd);
    return 0;
}