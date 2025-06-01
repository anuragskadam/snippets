#include <bits/stdc++.h>
using namespace std;

constexpr long long mod = 1e9 + 7;

// Floor of log2; index of highest 1-bit
inline int Log2(int num) {
    assert(num > 0);
    return bit_width(unsigned(num)) - 1;
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

inline long long Mod(long long num) {
    num %= mod;
    return num < 0 ? num + mod : num;
}

inline long long Pow(long long num, long long p) {
    assert(num >= 0 && p >= 0);
    num %= mod;
    long long res = 1;
    while (p) {
        if (p & 1) {
            res *= num;
            res %= mod;
        }
        num *= num;
        num %= mod;
        p >>= 1;
    }
    return res;
}

inline long long Inv(long long num) {
    assert(num > 0);
    num %= mod;
    long long p = mod - 2;
    long long res = 1;
    while (p) {
        if (p & 1) {
            res *= num;
            res %= mod;
        }
        num *= num;
        num %= mod;
        p >>= 1;
    }
    return res;
}

inline long long Add(long long a, long long b) {
    return Mod(Mod(a) + Mod(b));
}

inline long long Sub(long long a, long long b) {
    return Mod(Mod(a) - Mod(b));
}

inline long long Mul(long long a, long long b) {
    return Mod(Mod(a) * Mod(b));
}

inline long long Div(long long a, long long b) {
    return (Mod(a) * Inv(b)) % mod;
}

inline bool InRange(long long i, long long n) {
    return 0 <= i && i < n;
}

constexpr array<pair<int, int>, 4> dirs = {{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} }};

// Factorials
inline long long Factorial(int num) {
    static const int lim = 1e4;
    static vector<long long> factorials(lim + 1, 1);
    static const bool done = [](vector<long long> &f) {
        for (int i = 2; i <= lim; ++i)
            f[i] = (f[i - 1] * i) % mod;
        return true;
    }(factorials);
    return factorials[num];
}
//

// Factorials (Compile-Time)
constexpr int _lim_factorial = 1e4; // dont have this above 262144
constexpr array<long long, _lim_factorial + 1> _factorials = []() {
    array<long long, _lim_factorial + 1> f = {1};
    for (int i = 1; i <= _lim_factorial; ++i) {
        f[i] = (f[i - 1] * i) % mod;
    }
    return f;
}();
inline long long Factorial(int num) {
    return _factorials[num];
}
//

// Combination
inline long long Comb(int n, int r) {
    return (Factorial(n) * Inv(Factorial(r) * Factorial(n - r))) % mod;
}
//

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
class ordered_multiset {
    template<typename TT>
    using ordered_ms = tree<
    pair<TT, int>,
    null_type,
    less<pair<TT, int>>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

    int id = 0;
    ordered_ms<T> oms;
    map<T, vector<int>> inserted_ids;
    int _size = 0;
    public:
    void insert (const T obj) {
        oms.insert({obj, id});
        inserted_ids[obj].push_back(id++);
        _size++;
    }
    void erase_one(const T obj) {
        auto it = inserted_ids.find(obj);
        if (it == inserted_ids.end()) return;
        _size--;
        oms.erase({obj, it->second.back()});
        it->second.pop_back();
        if (it->second.empty()) {
            inserted_ids.erase(it);
        }
    }
    inline int lower_bound_idx (const T obj) const {
        // returns index as it we ran lower_bound on a sorted array
        // returns how many elements are smaller than obj
        return oms.order_of_key({obj, 0});
    }
    int count(const T obj) const {
        auto it = inserted_ids.find(obj);
        if (it == inserted_ids.end()) return 0;
        return it->second.size();
    }
    inline int size() const {
        return _size;
    }
    inline bool contains(const T obj) const {
        return inserted_ids.contains(obj);
    }
    const T& operator[] (const size_t idx) const {
        assert(idx < size());
        return oms.find_by_order(idx)->first;
    }
};

// For Matrix operations

vector<vector<long long>> MatMul (const vector<vector<long long>> &mat1, const vector<vector<long long>> &mat2) {
    size_t n1 = mat1.size(), m1 = mat1.front().size();
    size_t n2 = mat2.size(), m2 = mat2.front().size();
    assert(m1 == n2);
    vector<vector<long long>> res(n1, vector<long long> (m2));
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            for (int k = 0; k < m1; k++) {
                res[i][j] = (res[i][j] + Mod(Mod(mat1[i][k]) * Mod(mat2[k][j]))) % mod;
            }
        }
    }
    return res;
}

vector<vector<long long>> MatPow(vector<vector<long long>> mat, long long p) {
    assert(mat.size() == mat[0].size());
    const size_t mat_size = mat.size();
    vector<vector<long long>> res(mat_size, vector<long long> (mat_size));
    for (int i = 0; i < mat_size; i++) res[i][i] = 1;
    while (p) {
        if (p & 1) {
            res = MatMul(res, mat);
        }
        mat = MatMul(mat, mat);
        p >>= 1;
    }
    return res;
}

// Matrix End