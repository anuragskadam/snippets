#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    string filename;
    if (argc != 2) {
        filename = "a.cpp";
    }
    else {
        filename = argv[1] + string(".cpp");
    }

    std::ifstream src("./snippets/automation/1gen.txt", std::ios::binary);
    std::ofstream dest(filename, std::ios::binary);

    if (!src || !dest) {
        std::cerr << "Error opening files!\n";
        return 1;
    }

    dest << src.rdbuf();  // Copy contents
    return 0;
}
