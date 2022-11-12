#include <cstdio>
#include <string>
#include <iostream>

int main() {
    std::string s;
    int n, a, b, tot = 0;
    scanf("%d%d%d", &n, &a, &b);
    std::getline(std::cin, s);

    while (n--) {
        std::getline(std::cin, s);
        // printf("here: %s\n", s.c_str());
        if (s == "/oh") {
            tot += a;
        } else if (s == "/hsh") {
            tot += b;
        }
        std::getline(std::cin, s);
        if (s == "/oh") {
            tot += a;
        } else if (s == "/hsh") {
            tot += b;
        }
    }
    printf("%d\n", tot);
    return 0;
}