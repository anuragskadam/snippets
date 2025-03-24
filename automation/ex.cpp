#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string command;
    if (argc > 2) return 1;
    else if (argc == 2) {
        command = "./" + string(argv[1]) + " < inp.txt > out.txt";
    }
    else {
        command = "./a < inp.txt > out.txt";
    }
    return system(command.c_str());
}
