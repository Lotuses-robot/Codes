#include <cstdio>
#include <random>
#include <fstream>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(1, 8);
    std::uniform_int_distribution<> dis2(0, 25);
    std::uniform_int_distribution<> dis3(25, 40000);
    std::ofstream fout("4080.in");

    int T = 100;
    while (T--) {
        fout << dis1(gen) << "\n";
        int Len = dis3(gen);
        for (int i = 0; i < Len; i++) {
            fout << char('a');
        }
        fout << "\n";
    }
    fout << "0";
}