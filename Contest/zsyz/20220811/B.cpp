#include <cstdio>
#include <cstring>

char s[1000006];
char t[100];

int tot[114];

void print(int ch) {
    while (tot[ch] > 0) {
        putchar(ch + 'a');
        tot[ch]--;
    }
}

void print_behind() {
    if (t[0] == 'a' && t[1] == 'b') {
        print(0); // a
        print(2); // c
        print(1); // b
    } else {
        print(0); // a 
        print(1); // b
        print(2); // c
    }
}

void print_other() {
    for (int ch = 0; ch < 26; ch++) {
        print(ch);
    }
}

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    scanf("%s", s);
    scanf("%s", t);
    int n = strlen(s);
    
    for (int i = 0; i < n; i++) {
        tot[s[i] - 'a']++;
    }

    print_behind();
    print_other();
    
    return 0;
}