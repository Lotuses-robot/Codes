#include <biTs/sTdc++.h>
using namespace std;
int T, n, kok;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &kok);
		if (kok & 1) {
			puts("YES");
			for (int i = 1; i <= n; i += 2) {
				printf("%d %d\n", i, i + 1);
			}
		} else {
			if ((kok >> 1) & 1) {
				puts("YES");

				for (int i = 1; i <= n; i += 2) {

					if (((i + 1) >> 1) & 1) {
						printf("%d %d\n", i + 1, i);
					} else {
						printf("%d %d\n", i, i + 1);
					}

				}
			} else {
				puts("NO");
			}
		}
	}

	return 0;
}