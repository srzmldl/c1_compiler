#include <bits/stdc++.h>

using namespace std;

const int esp = 1e-5;

int main() {
    system("java -jar ../../../../../jplag/jplag-2.11.8-SNAPSHOT-jar-with-dependencies.jar -l c/c++ -s ../codes >out.txt");
    freopen("out.txt", "r", stdin);
    freopen("jplag.txt", "w", stdout);
    char st1[100], st2[100];
    for (; scanf("%s", st1); ) {
        if (string(st1) == ("Comparing")) {
            break;
        }
    }
    double sim;
    for (;scanf("%s%lf%s", st2, &sim, st1) != EOF;) {
        if (sim > esp) {
            printf("%s %lf\n", st2, sim);
        }
        if (string(st1) != ("Comparing")) break;
    }
    return 0;
}