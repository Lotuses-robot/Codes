#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>

using std::cin;
using std::getline;
using std::string;
using std::cout;

string map[100005];
int len = 1;
struct Trie {
    char ch;
    int sons[27], tot;
}tr[100005];

void init(int id, char ch) {
    tr[id].ch = ch;
    tr[id].tot = 0;
    memset(tr[id].sons, -1, sizeof(tr[id].sons));
}

void insert(string s) {
    int nid = 0, i = 0;
    while (i < s.length()) {
        if (tr[nid].sons[s[i] - 'a'] < 0) {
            tr[nid].sons[s[i] - 'a'] = len;
            init(len, s[i]);
            len++;
        }
        nid = tr[nid].sons[s[i] - 'a'];
        tr[nid].tot++;
        i++;
    }
}

int query(string s) {
    int nid = 0, i = 0;
    while (i < s.length()) {
        if (tr[nid].sons[s[i] - 'a'] < 0) {
            return 0;
        }
        nid = tr[nid].sons[s[i] - 'a'];
        i++;
    }
    return tr[nid].tot;
}

int main() {
    std::ios::sync_with_stdio(0);
    string line;
    init(0, '\0');
    getline(cin, line);
    while (line != "") {
        insert(line);
        getline(cin, line);
    }

    getline(cin, line);
    while (line != "") {
        cout << query(line) << "\n";
        getline(cin, line);
    }
    return 0;
}