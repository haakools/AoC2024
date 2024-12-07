
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



std::vector<int> findAllArguments(std::string line) {

    std::vector<int> arguments;

    // find first
    int prevPos = 0;
    int pos = line.find(" ", 0);

    
    while ( pos != std::string::npos ) {
        prevPos = pos;
        pos = line.find(" ", prevPos+1);
        arguments.push_back(
                std::stoi(
                    line.substr(prevPos, pos)
                    )
                );
    };


    return arguments;

}


int solve_puzzle_1(std::vector<std::string> lines) {


    for (int i=0; i< lines.size(); i++) {
        std::cout << "Parsing line: " << std::endl;
        std::cout << lines[i] <<  std::endl;

        // parse into result and then numbers
        int semicolonIdx = lines[i].find(":");
        int result = std::stoi(lines[i].substr(0, semicolonIdx));

        std::cout << "Target result: " << std::endl;
        std::cout << result << std::endl;


        std::string arguemntsString = lines[i].substr(semicolonIdx+1, std::string::npos);
        std::vector<int> arguments = findAllArguments(arguemntsString);

        std::cout << "Arguments: " << std::endl;
        // first find all spaces 
        for (int i = 0; i<arguments.size(); i++) {
            std::cout << arguments[i] << std::endl;

        }

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
