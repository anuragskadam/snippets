// clears contents of inp.txt, out.txt, key.txt and runs clear in terminal
#include <fstream>
#include <cstdlib>

int main() {
    // Open each file in truncation mode to clear its contents
    std::ofstream("inp.txt", std::ios::trunc);
    std::ofstream("out.txt", std::ios::trunc);
    std::ofstream("key.txt", std::ios::trunc);
    system("./gen; clear"); // For Linux/macOS
    return 0;
}
