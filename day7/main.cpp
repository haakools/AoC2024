
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// returns vector of strings, where the "string" is the entire line in the file
std::vector<std::string> readFileLines(const std::string& filename) {
    std::ifstream file(filename);

    std::vector<std::string> lines;
    std::string line;
    if (!file.is_open()) {
        // this formatting seemformatting seemsng idk
        throw std::runtime_error("Could not open file " + filename);
    }
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}


int solve_puzzle_1(std::vector<std::string> lines) {
    for (int i=0; i< lines.size(); i++) {
        std::cout << lines[i] <<  std::endl;
    };
    return 0;
}

int main() {
    try {
        std::vector<std::string> lines = readFileLines("test_case1.txt");
        //std::vector<std::vector<std::string>> lines = readFileLines("input1.txt");
        solve_puzzle_1(lines);

    } catch (const std::exception& e ) {
        std::cerr << "Error: " << e.what() << '\n';
    }


    return 0;
}
