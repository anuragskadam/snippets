#include <bits/stdc++.h>
using namespace std;

set<int> GetPrimeSet (int lim) {
    // returns a set of prime numbers till `lim` (inclusive)
    vector<bool> composite(lim + 1); composite[0] = composite[1] = true;
    set<int> primes;
    for (long long i = 2; i <= lim; i++) {
        if (!composite[i]) {
            primes.insert(i);
            for (long long j = i * i; j <= lim; j += i) {
                composite[j] = true;
            }
        }
    }
    return primes;
}

// returns set of factors by reference
set<long long>& FactorsRef(long long num) {
    static unordered_map<long long, set<long long>> saved_factors;
    assert(num > 0);
    if (saved_factors.contains(num)) return saved_factors[num];
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
    return saved_factors[num] = res;
}

template<typename T>
inline T Gcd(T a, T b) {
    if (b > a) swap(a, b);
    assert(b >= 0);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
