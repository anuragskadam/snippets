#include <bits/stdc++.h>
using namespace std;

int Log2(long long num) {
    // Floor of log2 | same and bin_len - 1 (10101 -> 4)
    assert(num > 0);
    int res = -1;
    while (num) {
        res++;
        num >>= 1;
    }
    return res;
}

int Log(long long num, int base) {
    assert(num > 0 && base > 1);
    int res = -1;
    while (num) {
        res++;
        num /= base;
    }
    return res;
}

long long Sqrt(long long num) {
    assert(num >= 0);
    long long sq = sqrt(num);
    while(sq * sq > num) sq--;
    while ((sq + 1) * (sq + 1) <= num) sq++;
    return sq;
}

