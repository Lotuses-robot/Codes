#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>

using std::cin;
using std::getline;
using std::string;
using std::cout;

bool iss[100005];
string map[100005];
int len = 1, len2 = 0;
struct Trie {
    char ch;
    int sons[27], tot, id;
}tr[100005];

void init(int id, char ch) {
    tr[id].ch = ch;
    tr[id].tot = 0;
    tr[id].id = -1;
    memset(tr[id].sons, -1, sizeof(tr[id].sons));
}

void insert(string s) {
    int nid = 0, i = 0;
    bool newNode = false;
    while (i < s.length()) {
        if (tr[nid].sons[s[i] - 'a'] < 0) {
            tr[nid].sons[s[i] - 'a'] = len;
            init(len, s[i]);
            newNode = true;
        }
        nid = tr[nid].sons[s[i] - 'a'];
        tr[nid].tot++;
        i++;
    }
    if (newNode) {
        tr[nid].id = len2;
        map[len2] = s;
        len2++;
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
    string line1, line2;
    init(0, '\0');
    cin >> line1 >> line2;
    while (line1 != "" && line2 != "") {
        int leny = len2;
        insert(line1); insert(line2);
        if (line1 == line2 && leny != len2) {
            iss[leny] = true;
        }
        cin >> line1 >> line2;
    }

    int tot = 0;
    for (int i = 0; i < len2; i++) {
        int lin = query(map[i]);
        if (lin % 2 == 1) {
            tot++;
            if (iss[i]) {
                cout << "Impossible\n";
            }
        }
    }
    if (tot > 2) {
        cout << "Impossible\n";
    } else {
        cout << "Possible\n";
    }
    return 0;
}