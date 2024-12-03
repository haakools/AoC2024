
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



int evaluate_substring(std::string substr) {
    // return 0 statements for each error 
    int comma_location = substr.find(",");

    // if not found return
    if ( comma_location == std::string::npos) { return 0; };

    std::string left_substr = substr.substr(0, comma_location);
    std::string right_substr = substr.substr(comma_location+1, std::string::npos);
    std::cout << "Evaluating candidate" << substr << std::endl;
    std::cout << "right_substr" << right_substr << std::endl;

    // check if there are any tricky characters that can pass std::atoi
    //if (left_candidate.find_first_of(" \t\n") == std::string::npos) {
    //      return 0;
    //}

    int firstLeftNonDigit = left_substr.find_first_not_of("0123456789");
    if (firstLeftNonDigit != std::string::npos) {return 0;}
    int first_number = std::atoi(left_substr.c_str());

    // "If no conversion can be performed, ​0​ is returned."
    // https://en.cppreference.com/w/cpp/string/byte/atoi
    if (first_number == 0) {
        return 0; 
    }

    std::cout << "First number: " << first_number << std::endl;


    // second number
    int firstRightNonDigit = right_substr.find_first_not_of("0123456789");
    if (firstRightNonDigit == std::string::npos) {return 0;}
    if (right_substr[firstRightNonDigit] != ')') {return 0;}

    //std::string right_candidate = right_substr.substr(1, r_paren_location-1);
    std::cout << "Second number substring candidate:" << right_substr << std::endl;

    int second_number = std::stoi(right_substr);
    std::cout << "number 1: " << first_number << "\tnumber 2:" << second_number << std::endl;
    return first_number * second_number;
}

/*
mul(667,142);*when
0123456789abcdef <-  substr length

7 is comma, so substr(7+1, 

*/


int solve_puzzle_1(std::vector<std::string> lines) {
    // find occurence of the mul(
    // check if it is followed by a number,number)

    int sum = 0;

    for (int i = 0; i < lines.size(); i++) {

        // for each line, find the places they occur
        std::vector<size_t> mul_lparen_positions;
        size_t mul_lparen_position = lines[i].find("mul(");
        size_t mul_lparen_last_position;


        // loop until the end of the string
        while(mul_lparen_position != std::string::npos) {
            mul_lparen_positions.push_back(mul_lparen_position);
            mul_lparen_last_position = mul_lparen_position;
            mul_lparen_position = lines[i].find("mul(", mul_lparen_position+1);

            std::cout << "\nFound last mul( at index " << mul_lparen_last_position << std::endl;
            std::cout << "Found mul( at index " << mul_lparen_position << std::endl;
            // adding 4 because it is the length of "mul("
            std::string mul_string = lines[i].substr(mul_lparen_last_position+4, (mul_lparen_position-mul_lparen_last_position));

            std::cout << "evaluating string " << mul_string << std::endl;

            int value = evaluate_substring(mul_string);
            std::cout <<"Found value: " << value << std::endl;
            sum = sum + value;
       }

        // printing all the positions as sanity check 
        //for (int i = 0; i < mul_lparen_positions.size(); i++) {
        //    std::cout << mul_lparen_positions[i] << std::endl;
        //}

        //std::cout << lines[i] << std::endl;
    }
    printf("Sum is %d", sum);

    return 0;
}




int main() {
    try {
        std::vector<std::string> lines = readFileLines("input1.txt");
        //std::vector<std::string> lines = readFileLines("test_case1.txt");
        solve_puzzle_1(lines);


    } catch (const std::exception& e ) {
        std::cerr << "Error: " << e.what() << '\n';
    }






    return 0;
}
