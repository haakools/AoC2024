
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


std::vector<long long> findAllArguments(std::string line) {

    std::vector<long long> arguments;

    // find first
    long long prevPos = 0;
    long long pos = line.find(" ", 0);

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


long long calculateOutput(std::vector<long long> argVec, std::string operators ) {

    // Now need to do a tree search if the ops "+" and "*" can solve the solution
    long long solution = 0; // working solution to compare with target
    std::string debugString = "";

    // First value because cannot start with 0 when doing a product
    if (operators[0] == '+') {
        debugString += std::to_string(argVec[0]);
        debugString += std::to_string(argVec[0]);
        solution = argVec[0] + argVec[1];
    }
    else if (operators[0] == '*') {
        debugString += std::to_string(argVec[0]);
        solution = argVec[0] * argVec[1];
    }
    else if (operators[0] == '|') {
        solution = std::stoll(
                std::to_string(argVec[0])+std::to_string(argVec[1])
                );
    }

    for (long long i = 1; i < argVec.size()-1; i++) { 

        debugString += std::to_string(argVec[i+1]);

        char op = operators[i];
        switch (op) {
            case '+':
                solution += argVec[i+1];
                debugString += "+";
                break;
            case '*':
                solution = solution * argVec[i+1];
                debugString += "*";
                break;
            case '|':
                solution = std::stoll(
                    std::to_string(solution)+std::to_string(argVec[i+1])
                );

            default:
                std::cout << "Default statement: " << std::endl;
                std::cout << op << std::endl;
                break;

        };
        std::cout << "calculateOutput::Current value: " << solution<<  std::endl;
    }

    debugString += std::to_string(argVec[argVec.size()-1]);

    std::cout << "debug" << std::endl;
    std::cout << debugString << std::endl;
    std::cout << "debug\n" << std::endl;

    return solution;
}


std::vector<std::string> generateOperators(const std::vector<std::string>& operators, size_t length) {
    std::vector<std::string> result;

    // Base case: if length is 0, return empty string
    if (length == 0) {
        result.push_back("");
        return result;
    }

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


long long solve_puzzle_1(std::vector<std::string> lines) {

    long long calibrationSum = 0;

    for (long long i=0; i< lines.size(); i++) {
        // Parsing inputs
        std::cout << "\n\n-------------------" <<  std::endl;
        std::cout << "Parsing line: " << std::endl;
        std::cout << lines[i] <<  std::endl;
        std::cout << "-------------------" <<  std::endl;

        // parse long longo target and then numbers
        long long semicolonIdx = lines[i].find(":");

        std::cout << lines[i].substr(0, semicolonIdx) <<  std::endl;

        try {
            long long large_num = std::stoll(lines[i].substr(0, semicolonIdx));
        } catch (std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        } catch (std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << std::endl;
        }

        long long target = std::stoll(lines[i].substr(0, semicolonIdx));

        // std::cout << "Target target: " << std::endl;
        // std::cout << target << std::endl;

        std::string arguemntsString = lines[i].substr(semicolonIdx+1, std::string::npos);
        std::vector<long long> argVec = findAllArguments(arguemntsString);

        std::cout << "Arguments: " << std::endl;
        // first find all spaces 
        for (long long i = 0; i<argVec.size(); i++) {
            std::cout << argVec[i] << std::endl;
        }

        // hopefully a vector of all solutions
        std::vector<std::string> operatorSolutions = generateOperators({"*", "+", "|"}, argVec.size()-1);

        //std::cout << "starting for loop: " << std::endl;
        for (long long i = 0; i < operatorSolutions.size(); i++) {
            std::string operatorSolution = operatorSolutions[i];

            std::cout << "operatorSolution: " << operatorSolution << std::endl;

            // test solution
            long long possibleSolution = calculateOutput(argVec, operatorSolution);


            std::cout << "Possible solution : " << operatorSolution << std::endl;
            std::cout << "Returns : " << possibleSolution << std::endl;


            // Sanity check
            for (size_t k = 0; k < argVec.size() || k < operatorSolution.length(); k++) {
                if (i < argVec.size())
                    std::cout << argVec[k];
                if (i < operatorSolution.length())
                    std::cout << operatorSolution[k];
            }

            std::cout << " = " << target << std::endl;



            if (possibleSolution == target) {

                std::cout << "FOUND SOLUTION: " << operatorSolution << std::endl;
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
        //std::vector<std::string> lines = readFileLines("test_case1.txt");
        //std::vector<std::string> lines = readFileLines("test_case2.txt");
        std::vector<std::string> lines = readFileLines("input1.txt");
        solve_puzzle_1(lines);

    } catch (const std::exception& e ) {
        std::cerr << "Error: " << e.what() << '\n';
    }


    return 0;
}
