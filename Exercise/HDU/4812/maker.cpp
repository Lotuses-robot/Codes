#include <cstdio>
#include <random>
#include <fstream>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(1, 100000);
    std::uniform_int_distribution<> dis2(0, 1000003);
    std::ofstream fout("4812.in");

    int T = 2;
    while (T--) {
        int n, k;
        n = dis1(gen);
        k = 0;
        fout << n << " " << k << "\n";
        for (int i = 0; i < n; i++) {
            fout << dis2(gen) << " ";
        }
        fout << "\n";
        for (int i = 0; i < n - 1; i++) {
            std::uniform_int_distribution<> dis3(1, n);
            fout << dis3(gen) << " " << dis3(gen) << "\n";
        }
    }
    fout.close();
    return 0;
}