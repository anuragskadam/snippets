// debug.h
// Written by Anurag Kadam and ChatGPT

#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

#define debug(...) print_names(#__VA_ARGS__), _debug(__VA_ARGS__)
#define addline "addline"
#define verify "verify"

bool addline_called = false;
bool verify_called = false;

// Trait to check if a type is iterable
template <typename T, typename = void>
struct is_iterable : false_type {};  // Assume not iterable

template <typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};  // Specialize for iterable types


// Trait to check if a type is std::pair
template <typename T>
struct is_pair : std::false_type {};  // Default to false

// Specialization for std::pair
template <typename T1, typename T2>
struct is_pair<std::pair<T1, T2>> : std::true_type {};  // Specialized for std::pair

// Helper variable template
template <typename T>
inline constexpr bool is_pair_v = is_pair<T>::value;



string delimiter = " ";

template<typename T>
void simple_print(const T& inp, string deli=" ") {
	if constexpr (is_iterable<T>::value && !is_same_v<T, string>) {
        // If the type is iterable and not a string, print the elements
        cerr << '{';
        int n = inp.size();
        auto it = inp.begin();
        while (n) {
            simple_print(*it);
            if (++it == inp.end()) break;
			cerr << ',' << deli;
        }
        cerr << '}';
    } 
	else if constexpr (is_pair_v<T>) {
        cerr << "{";
        simple_print(inp.first);
        cerr << ", ";
        simple_print(inp.second);
        cerr << "}";
    }
	else {
        // Otherwise, print the value directly (including strings)
        cerr << inp;
    }
}

void print_names(string names) {
    if (names == addline) {
        // enables "\n" delimiter in next one debug call
        delimiter = "\n";
        addline_called = true;
        return;
    }
    else if (names == verify) {
        cout.flush();
        verify_called = true;
        string command = "python3 \"./snippets/automation/pycheck.py\"";
        system(command.c_str());
        return;
    }
    else if (names.empty()) {
        cerr << "[meow]";
        return;
    }
    cerr << "[" << names << "]:" << delimiter;
}

void _debug() {
    cerr << endl;
    delimiter = " ";
}

// Debug function that prints the object
template <typename... Args>
void _debug(Args&&... args) {
    size_t count = 0;
    auto printWithComma = [&] (const auto& arg) {
        if (addline_called || verify_called) {
            return;
        }
        simple_print(arg, delimiter);
        if (++count < sizeof...(args)) cerr << "," << delimiter;
    };
    (printWithComma(args), ...);

    if (addline_called) {
        addline_called = false;
        return;
    }
    if (verify_called) {
        verify_called = false;
        return;
    }
    cerr << endl;
    delimiter = " ";
}
