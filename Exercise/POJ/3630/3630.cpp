#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>

using std::cin;
using std::string;
using std::cout;

int len = 1;
struct Trie {
    char ch;
    int sons[27];
    bool vis, vis2;
}tr[100005];

void init(int id, char ch) {
    tr[id].ch = ch; tr[id].vis = tr[id].vis2 = false;
    memset(tr[id].sons, -1, sizeof(tr[id].sons));
}

bool insert(string s) {
    int nid = 0, i = 0;
    while (i < s.length()) {
        if (tr[nid].sons[s[i] - '0'] < 0) {
            tr[nid].sons[s[i] - '0'] = len;
            init(len, s[i]);
            len++;
        }
        nid = tr[nid].sons[s[i] - '0'];
        if (tr[nid].vis) {
            return false;
        }
        i++;
        if (i < s.length()) {
            tr[nid].vis2 = true;
        }
    }
    tr[nid].vis = true;
    if (tr[nid].vis2 == true) {
        return false;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        string line;
        bool flag = true;
        int n;

        init(0, '\0');
        len = 1;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> line;
            flag &= insert(line);
        }
        if (flag) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}