#include <bits/stdc++.h>
using namespace std;

set<int> GetPrimeSt (int lim) {
    // returns a set of prime numbers till `lim` (inclusive)
    vector<bool> flag(lim + 1);
    set<int> primes;
    for (int i = 2; i <= lim; i++) {
        long long mul = i;
        if (!flag[i]) {
            primes.insert(i);
            while (mul * i <= lim) {
                flag[mul * i] = true;
                mul++;
            }
        }
    }
    return primes;
}

vector<int> GetPrimeVec (int lim) {
    // returns a vector of prime numbers till `lim` (inclusive)
    vector<bool> flag(lim + 1);
    vector<int> primes;
    for (int i = 2; i <= lim; i++) {
        long long mul = i;
        if (!flag[i]) {
            primes.push_back(i);
            while (mul * i <= lim) {
                flag[mul * i] = true;
                mul++;
            }
        }
    }
    return primes;
}

set<long long> Factors(long long num) {
    assert(num > 0);
    set<long long> res;
    long long sqr = sqrt(num);
    while(sqr * sqr > num) sqr--;
    while ((sqr + 1) * (sqr + 1) <= num) sqr++;
    for (long long i = 1; i <= sqr; i++) {
        if (num % i == 0) {
            res.insert(i);
            res.insert(num / i);
        }
    }
    return res;
}

long long Gcd(long long a, long long b) {
    if (b > a) swap(a, b);
    if (b == 0) return a;
    return (b, a % b);
}
