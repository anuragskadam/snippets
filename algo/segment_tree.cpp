#include <bits/stdc++.h>

using namespace std;

template<typename T>
class segment_tree {
    int original_arr_size = -1;
    int tree_size = -1;
    int get_next_2pow (int inp) {
        int curr = 1;
        while (curr < inp) {
            curr <<= 1;
        }
        return curr;
    }
    inline int parent(int idx) {
        return idx >> 1;
    }
    inline int left_ch(int idx) {
        return idx << 1;
    }
    inline int right_ch(int idx) {
        return (idx << 1) + 1;
    }

    // configurables
    function<T(T, T)> func;
    T default_value;
    //

    inline T _ask_node(int left_query, int right_query, int node_idx, int node_left, int node_right) {
        if (left_query <= node_left && right_query >= node_right) {
            // complete overlap
            return tree[node_idx];
        }
        if (left_query > node_right || right_query < node_left) {
            // disjoint
            return default_value;
        }
        auto mid = (node_left + node_right) >> 1;
        return func(
            _ask_node(left_query, right_query, left_ch(node_idx), node_left, mid)
            , _ask_node(left_query, right_query, right_ch(node_idx), mid + 1, node_right)
        );
    }
    inline void _update_node (int tree_idx) {
        if (!tree_idx) return;
        tree[tree_idx] = func(tree[left_ch(tree_idx)], tree[right_ch(tree_idx)]);
    }

    public:
    int leaves = -1;
    vector<T> tree;
    segment_tree() {}
    segment_tree(const int size_in, function<T(T, T)> func_in, T default_val_in) {
        func = func_in;
        default_value = default_val_in;
        original_arr_size = size_in;
        leaves = get_next_2pow(original_arr_size);
        tree_size = leaves << 1;
        tree = vector<T>(tree_size, default_value);
    }
    segment_tree(const vector<T> &vec, function<T(T, T)> func_in, T default_val_in) {
        func = func_in;
        default_value = default_val_in;
        original_arr_size = vec.size();
        leaves = get_next_2pow(original_arr_size);
        tree_size = leaves << 1;
        tree = vector<T>(tree_size, default_value);
        for (int i = 0; i < original_arr_size; i++) {
            tree[leaves + i] = vec[i];
        }
        for (int i = leaves - 1; i > 0; i--) {
            _update_node(i);
        }
    }
    void point_update(int idx, T value) {
        assert(0 <= idx && idx < original_arr_size);
        tree[leaves + idx] = value;
        int curr_tree_idx = parent(leaves + idx);
        while (curr_tree_idx) {
            _update_node(curr_tree_idx);
            curr_tree_idx = parent(curr_tree_idx);
        }
    }
    T operator()(int left_idx, int right_idx) {
        // inclusive and 0-indexed
        assert(left_idx >= 0 && right_idx < original_arr_size && left_idx <= right_idx);
        return _ask_node(left_idx, right_idx, 1, 0, leaves - 1);
    }
    const T& operator[](int idx) const {
        assert(0 <= idx && idx < original_arr_size);
        return tree[leaves + idx];
    }
};