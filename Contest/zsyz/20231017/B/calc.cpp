#include <iostream>
#include <vector>
#include <stdint.h>
 
using namespace std;
 
void delete_all_multiple(vector<char> & table, int32_t n) {
	for (int32_t i = n * 2; i < table.size(); i += n) {
		table[i] = false;
	}
}
 
int32_t find_next_prime(vector<char> & table, int32_t prime) {
	for (int32_t i = prime + 1; i < table.size(); i++) {
		if (table[i]) { 
			return i;
		}
	}
	return -1;
}
 
int main() {
    vector<char> table(1000000000, true);
    table[0] = table[1] = false;
    int cnt = 0;
    for (int32_t prime = 2; prime != -1; prime = find_next_prime(table, prime)) {
    	// cout << prime << endl;
        cnt++;
    	delete_all_multiple(table, prime);
    }
    printf("%d\n", cnt);
    return 0;
}