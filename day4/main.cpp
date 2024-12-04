
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// returns vector of strings, where the "string" is the entire line in the file
std::vector<std::vector<std::string>> readFileLines(const std::string& filename) {
    std::vector<std::vector<std::string>> lines;

    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    while (std::getline(file, line)) {
        std::vector<std::string> currentLine;
        for (int i=0; i<line.length(); i++) {
            currentLine.push_back(std::string(1,line[i]));
        }
        lines.push_back(currentLine);
    }
    file.close();
    return lines;
}


typedef struct {
    // if either is -1 then failed
    int x;
    int y;
} gridpos;



/*
   relative grid
   0 1 2 x rowsize x
   0 X X X
   1 X X X
   2 X X X
   colsize - y 

   { -1, -1}, { 0, -1}, { 1, -1},
   { -1,  0},           { 1,  0},
   { -1,  1}, { 0, 1},  { 1,  1},

*/

gridpos find_surrounding_character(gridpos pos, std::string next_string,
        std::vector<std::vector<std::string>>& grid, int rowSize, int colSize) {

    gridpos default_position = {-1,-1};


    // CORNERS
    std::cout << "debug 2" << std::endl;
    std::cout << "pos: " << pos.x << pos.y << std::endl;
    if (pos.x == 0 && pos.y == 0) {
        // (1,0), (1,1), (0,1)
        std::vector<gridpos> check_positions = {
            { 1,  0},
            { 0, 1},  { 1,  1},
        };

        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        }
        return default_position;
    }

    std::cout << "debug 3" << std::endl;
    std::cout << "pos: " << pos.x << pos.y << std::endl;
    if (pos.x == rowSize && pos.y == 0) {
        // (1,0), (1,1), (0,1)
        std::vector<gridpos> check_positions = {
            { -1,  0},         
            { -1,  1}, { 0, 1},
        };


        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        }
        return default_position;
    }

    std::cout << "debug 4" << std::endl;
    if (pos.x == rowSize && pos.y == colSize) {
        // (1,0), (1,1), (0,1)
        std::vector<gridpos> check_positions = {
            { -1, -1}, { 0, -1},
            { -1,  0},          
        };

        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        }
        return default_position;
    }

    std::cout << "debug 5" << std::endl;
    if (pos.x == 0 && pos.y == colSize) {
        // (1,0), (1,1), (0,1)
        std::vector<gridpos> check_positions = {
            { 0, -1}, { 1, -1},
            { 1,  0},
        };

        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        return default_position;
        }
    }

    // CORNERSDONE



    // VERTICIES

    std::cout << "debug 6" << std::endl;
    if (pos.y == 0) {
        std::vector<gridpos> check_positions = {

            { -1,  0},           { 1,  0},
            { -1,  1}, { 0, 1},  { 1,  1},

        };
        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        return default_position;
        }
    }

    std::cout << "debug 7" << std::endl;
    if (pos.y == colSize) {
        // (1,0), (1,1), (0,1)
        std::vector<gridpos> check_positions = {

            { -1, -1}, { 0, -1}, { 1, -1},
            { -1,  0},           { 1,  0},

        };
        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        return default_position;
        }
    }

    std::cout << "debug 8" << std::endl;
    if (pos.x == rowSize) {
        // (1,0), (1,1), (0,1)
        std::vector<gridpos> check_positions = {

            { -1, -1}, { 0, -1}, 
            { -1,  0},           
            { -1,  1}, { 0, 1},  

        };
        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        return default_position;
        }
    }

    std::cout << "debug 9" << std::endl;
    if (pos.x == 0) {
        std::vector<gridpos> check_positions = {

            { 0, -1}, { 1, -1},
            { 1,  0},
            { 0, 1},  { 1,  1},


        };
        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        return default_position;
        }
    }

    // VERTICIES DONE



    /*
       relative grid
       -1 0 1 x rowSize
       -1 X X X
       0 X O X
       1 X X X
       y
       colSize
       */

    //basecase
    std::cout << "debug 10" << std::endl;
    std::vector<gridpos> check_positions = {
        // x,  y
        { -1, -1}, { 0, -1}, { 1, -1},
        { -1,  0},           { 1,  0},
        { -1,  1}, { 0, 1},  { 1,  1},
    };

        for (int i=0; i<check_positions.size(); i++) {
            if (grid[pos.x+check_positions[i].x][pos.y+check_positions[i].y] == next_string) {
                pos.x = pos.x+check_positions[i].x;
                pos.y = pos.y+check_positions[i].y;
                return pos;
            }
        return default_position;
        }

    std::cout << "debug 11" << std::endl;
    return default_position;
}


int solve_puzzle_1(std::vector<std::vector<std::string>> grid) {
    int count = 0;

    std::vector<std::string> targetWord = {"X", "M", "A", "S"};


    int row_size = grid.size()-1;
    int col_size = grid[0].size()-1;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j] << std::endl;
            for (int k = 0; k <targetWord.size(); k++) {
                gridpos position = {i,j};
                std::cout << "debug 1" << std::endl;
                gridpos nextStringPos = find_surrounding_character(position, targetWord[k], grid, row_size, col_size);
                if (nextStringPos.x == -1 && nextStringPos.y == -1) {
                    break;
                }
            }
            count++;
        }
    }
    printf("count is %d", count);
    return 0;
}

int main() {
    try {
        //std::vector<std::string> lines = readFileLines("input1.txt");
        std::vector<std::vector<std::string>> lines = readFileLines("test_case1.txt");
        solve_puzzle_1(lines);

    } catch (const std::exception& e ) {
        std::cerr << "Error: " << e.what() << '\n';
    }


    return 0;
}
