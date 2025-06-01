#include <bits/stdc++.h>
using namespace std;

class dsu {
    // zero_indexed
    vector<int> _pars;
    int _size;
    int _connected_compnents;
    vector<int> _size_of_par; // initialised with each value 1
    public:
    dsu (int size) {
        _pars = vector<int>(size);
        _size_of_par = vector<int>(size, 1);
        _size = size;
        for (int i = 0; i < _size; i++) {
            _pars[i] = i;
        }
        _connected_compnents = size;
    }
    inline int size() {
        return _size;
    }
    int par(int node) {
        if (_pars[node] != node) {
            _pars[node] = par(_pars[node]);
        }
        return _pars[node];
    }
    bool unite(int n1, int n2) {
        // returns true if n1 and n2 belong to diff grps
        int p1 = par(n1), p2 = par(n2);
        if (p1 != p2) {
            if (_size_of_par[p1] < _size_of_par[p2]) {
                swap(p1, p2);
                swap(n1, n2);
            }
            _pars[p2] = p1;
            _size_of_par[p1] += _size_of_par[p2];
            _connected_compnents--;
            return true;
        }
        return false;
    }
    inline int size_of_grp(int node) {
        // returns size of group of `node`
        return _size_of_par[par(node)];
    }
    inline int connected_comps() {
        // returns number of connected components
        return _connected_compnents;
    }
};