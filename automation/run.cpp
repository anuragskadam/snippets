// runs in debug mode
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string command;
    if (argc > 2) return 1;
    else if (argc == 2) {
        command = "g++ -std=c++20 -DASK_DEBUG -D_GLIBCXX_DEBUG " + string(argv[1]) + ".cpp -o " + string(argv[1]) + " && ./" + string(argv[1]) + " < inp.txt > out.txt";
    }
    else {
        command = "g++ -std=c++20 -DASK_DEBUG -D_GLIBCXX_DEBUG a.cpp -o a && ./a < inp.txt > out.txt";
    }
    return system(command.c_str());
}
