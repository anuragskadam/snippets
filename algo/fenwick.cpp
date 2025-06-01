template<typename T>
class fenwick {
    size_t _size = 0;
    vector<T> fenwick_arr;
public:
    vector<T> nums;
    fenwick() {}
    fenwick(vector<T>& nums_in) {
        _size = nums_in.size();
        nums = vector<T>(_size);
        fenwick_arr = vector<T>(_size + 1);
        for (int i = 0; i < _size; i++) {
            update(i, nums_in[i]);
        }
    }
    fenwick(vector<T>&& nums_in) {
        _size = nums_in.size();
        nums = vector<T>(_size);
        fenwick_arr = vector<T>(_size + 1);
        for (int i = 0; i < _size; i++) {
            update(i, nums_in[i]);
        }
    }
    fenwick(size_t length) {
        // make a blank fenwick tree with `length` entries (all set to ZERO)
        _size = length;
        nums = vector<T>(_size);
        fenwick_arr = vector<T>(_size + 1);
    }

    size_t size() {
        return _size;
    }
    
    // customiseable operators
    T operator_fenwick(T inp1, T inp2) {
        return inp1 + inp2;
    }
    T inverted_operator_fenwick(T inp1, T inp2) {
        return inp1 - inp2;
    }
    //

    void update(size_t index, T val) {
        T prev = nums[index];
        nums[index] = val;
        T diff = inverted_operator_fenwick(nums[index], prev);
        index++;
        while (index <= nums.size()) {
            fenwick_arr[index] = operator_fenwick(fenwick_arr[index], diff);
            index += index & (-index);
        }
    }
    T get_pref(size_t idx) {
        size_t f_idx = idx + 1;
        T ans = 0;
        while (f_idx) {
            ans = operator_fenwick(ans, fenwick_arr[f_idx]);
            f_idx -= f_idx & (-f_idx);
        }
        return ans;
    }
    T get_range_sum(size_t left, size_t right) {
        return inverted_operator_fenwick(get_pref(right), get_pref(left - 1));
    }
};