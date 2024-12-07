
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


int calculateOutput(std::vector<int> argVec, std::string operators ) {

    // Now need to do a tree search if the ops "+" and "*" can solve the solution
    int solution = 0; // working solution to compare with target
    for (int i = 0; i < argVec.size()-1; i++) { 
        char op = operators[i];
        switch (op) {
            case '+':
                solution = argVec[i] + argVec[i+1];
                break;
            case '*':
                solution = argVec[i] * argVec[i+1];
                break;
            default:
                std::cout << "Default statement: " << std::endl;
                std::cout << op << std::endl;
                break;

        };
    }
    return solution;
}


std::vector<std::string> generateOperators(const std::vector<std::string>& operators, size_t length) {
    std::vector<std::string> result;
    
    // Recursive case
    std::vector<std::string> subResults = generateOperators(operators, length - 1);
    
    // For each previous result, append each possible operator
    for (const std::string& subResult : subResults) {
        for (const std::string& op : operators) {
            result.push_back(subResult + op);
        }
    }
    
    return result;
}

/*
std::vector<std::string> generateOperators(const std::vector<std::string> operatorList) {
    std::vector<std::string> result;
    // I am a genius
    for(const std::string val1 : operatorList) {
        for(const std::string val2 : operatorList) {
            for(const std::string val3 : operatorList) {
                for(const std::string val4 : operatorList) {
                    for(const std::string val5 : operatorList) {
                        for(const std::string val6 : operatorList) {
                            for(const std::string val7 : operatorList) {
                                for(const std::string val8 : operatorList) {
                                    for(const std::string val9 : operatorList) {
                                        for(const std::string val10 : operatorList) {
                                            for(const std::string val11 : operatorList) {
                                                for(const std::string val12 : operatorList) {
                                                    for(const std::string val13 : operatorList) {
                                                        std::string combination;
                                                        combination += val1;
                                                        combination += val2;
                                                        combination += val3;
                                                        combination += val4;
                                                        combination += val5;
                                                        combination += val6;
                                                        combination += val7;
                                                        combination += val8;
                                                        combination += val9;
                                                        combination += val10;
                                                        combination += val11;
                                                        combination += val12;
                                                        combination += val13;
                                                        result.push_back(combination);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}
*/




int solve_puzzle_1(std::vector<std::string> lines) {

    int calibrationSum = 0;

    for (int i=0; i< lines.size(); i++) {
        // Parsing inputs
        // std::cout << "Parsing line: " << std::endl;
        // std::cout << lines[i] <<  std::endl;

        // parse into target and then numbers
        int semicolonIdx = lines[i].find(":");
        int target = std::stoi(lines[i].substr(0, semicolonIdx));

        // std::cout << "Target target: " << std::endl;
        // std::cout << target << std::endl;

        std::string arguemntsString = lines[i].substr(semicolonIdx+1, std::string::npos);
        std::vector<int> argVec = findAllArguments(arguemntsString);

        //std::cout << "Arguments: " << std::endl;
        // first find all spaces 
        //for (int i = 0; i<argVec.size(); i++) {
        //    std::cout << argVec[i] << std::endl;
        //}

        // hopefully a vector of all solutions
        std::vector<std::string> operatorSolutions = generateOperators({"*", "+"}, argVec.size());

        for (int i = 0; i < operatorSolutions.size(); i++) {
            std::string operatorSolution = operatorSolutions[i]; //.substr(0, argVec.size());

            std::cout << operatorSolution << std::endl;

            // test solution
            int possibleSolution = calculateOutput(argVec, operatorSolution);
            if (possibleSolution == target) {
                std::cout << "Found solution: " << std::endl;
                std::cout << operatorSolution << std::endl;
                calibrationSum = calibrationSum + target;
                break;
            }
        }
    }

    std::cout << "Calibration Result Sum: " << std::endl;
    std::cout << calibrationSum << std::endl;

    return 0;

};

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
