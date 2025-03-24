#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string command;
    if (argc > 1) return 1;
    command = "python3 \"./snippets/automation/pycheck.py\"";
    return system(command.c_str());
}
