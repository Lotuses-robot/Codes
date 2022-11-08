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
int len = 1, len2 = 0;
struct Trie {
    char ch;
    int sons[27], id;
}tr[100005];

void init(int id, char ch) {
    tr[id].ch = ch;
    tr[id].id = -1;
    memset(tr[id].sons, -1, sizeof(tr[id].sons));
}

void insert(string s, string s2) {
    int nid = 0, i = 0;
    while (i < s.length()) {
        if (tr[nid].sons[s[i] - 'a'] < 0) {
            tr[nid].sons[s[i] - 'a'] = len;
            init(len, s[i]);
            len++;
        }
        nid = tr[nid].sons[s[i] - 'a'];
        i++;
    }
    tr[nid].id = len2; map[len2++] = s2;
}

int query(string s) {
    int nid = 0, i = 0;
    while (i < s.length()) {
        if (tr[nid].sons[s[i] - 'a'] < 0) {
            return -1;
        }
        nid = tr[nid].sons[s[i] - 'a'];
        i++;
    }
    return tr[nid].id;
}

int main() {
    std::ios::sync_with_stdio(0);
    string line;
    init(0, '\0');
    getline(cin, line);
    while (line != "") {
        string enc = line.substr(0, line.find_first_of(' '));
        string dec = line.substr(line.find_first_of(' ') + 1);
        insert(dec, enc);
        getline(cin, line);
    }

    getline(cin, line);
    while (line != "") {
        int res = query(line);
        if (res == -1) {
            cout << "eh\n";
        } else {
            cout << map[res] << "\n";
        }
        getline(cin, line);
    }
    return 0;
}