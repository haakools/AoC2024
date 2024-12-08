
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


// 12 for test case, 50 for input
//#define MATRIXSIZE 50
#define MATRIXSIZE 12


typedef struct {
    char matrix[MATRIXSIZE][MATRIXSIZE];

} matrix;

matrix readMatrixFromFile(const std::string& filename) {
    matrix mat;
    std::ifstream file(filename);

    for (int i = 0; i < MATRIXSIZE; ++i) {
        std::string line;
        std::getline(file, line);
        for (int j = 0; j < MATRIXSIZE; ++j) {
            mat.matrix[i][j] = line[j];
        }
    }
    return mat;
}



//manhattan distance
int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1-x2) + abs(y1-y2);
}

/*  tried calculating but would rather brute force with an assumption
// Reverse this
manhattan_distance(x1, y1, p1.x, p1.y) + 2 * manhattan_distance(x1, y1, p2.x, p2.y)


// possible distance for a point (just that one, 
// 2 value will be flipped when searching for the others
d(x,y) = ( |x1-px|+2|x2-px|,  |y1-px| + 2|y2-py| )

// distance values for each of the axis.
d_x = |x1-px| + 2 * | x2-px|
d_y = |y1-py| + 2 * | y2-py|

// Possible x values
d_x_1 = x1 - px + 2*x2 - 2*px
d_x_2 = px - x1 + 2*x2 - 2*px
d_x_3 = x1 - px - 2*x2 + 2*px
d_x_4 = px - x1 - 2*x2 + 2*px
// possible y values
d_y_1 = y1 - py + 2*y2 - 2*py
d_y_2 = py - y1 + 2*y2 - 2*py
d_y_3 = y1 - py - 2*y2 + 2*py
d_y_4 = py - y1 - 2*y2 + 2*py

// factored down
d_x_1 =  x1 - 3*px +2*x2
d_x_2 = -x1 - 3*px +2*x2
d_x_3 =  x1 +   px -2*x2
d_x_4 = -x1 +   px -2*x2

d_y_1 =  y1 - 3*py +2*y2
d_y_2 = -y1 - 3*py +2*y2
d_y_3 =  y1 +   py -2*y2
d_y_4 = -y1 +   py -2*y2

// solving px and py
d_x_1 =  x1 - 3*px +2*x2
d_y_1 =  y1 - 3*py +2*y2

*/
// given x1, x2, y1, y2, how to expresss px with a value of d_x_1?



// and
//2 * manhattan_distance(x1, y1, p1.x, p1.y) + manhattan_distance(x1, y1, p2.x, p2.y)


// want a point that has 2x manhattan distance from one and 1x manhattan distance from the other



void solve_puzzle_1(matrix freqMat) {
    int antinodeUniqueLocations = 0; 

    // A..Z, a..z, 0..9 are the different frequencies
    // # is the antipode
    // Find all the location for a frequency.

    // Finally sum the #


    // Populate this with all the frequencies
    //std::vector<char> frequencies = {'0','A'};
    std::vector<char> frequencies;
    for (char ch = '0'; ch <= '9'; ++ch) {
        frequencies.push_back(ch);
    }

    // Add uppercase letters 'A' to 'Z'
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        frequencies.push_back(ch);
    }

    // Add lowercase letters 'a' to 'z'
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        frequencies.push_back(ch);
    }

    matrix antinodes;

    for (int i = 0; i < MATRIXSIZE; ++i) {
        for (int j = 0; j < MATRIXSIZE; ++j) {
            antinodes.matrix[i][j] = '.';
        }
    }

    // Loop over the locations of the frequencies 
    for (char frequency : frequencies) {
        //std::cout << frequency<< std::endl; 
        std::vector<std::pair<int, int>> freqLoc;

        // find the frequency locations
        for (int i = 0; i < MATRIXSIZE; ++i) {
            for (int j = 0; j < MATRIXSIZE; ++j) {
                if (freqMat.matrix[i][j] == frequency) {
                    // if the first one just add and then skip to the next
                    freqLoc.push_back(
                            std::make_pair(i, j)
                            );
                    if (freqLoc.size() <= 1) {
                        continue;
                    };

                    // For each frequency, loop over the other frequencies
                    for (int p=0; p<freqLoc.size()-1; p++) {
                        // For each value that is twice the length away, insert a #
                        int x1 = i;
                        int y1 = j;

                        int x2 = freqLoc[p].first;
                        int y2 = freqLoc[p].second;

                        int maxPointDistance = 2*manhattan_distance(x1, y1, x2, y2);

                        // assuming the distance cannot reach the dista
                        for (int p1= 0; p1<maxPointDistance; p1++) {
                            for (int p2= 0; p2<maxPointDistance; p2++) {

                                int potentialDistance = manhattan_distance(x1, y1, p1, p2);
                                int doubleDistance = 2*manhattan_distance(x2, y2, p1, p2);
                                //printf("\nEvaluating point (%d, %d)", p1, p2);
                                //printf("\t D(p1, (x1,y1)) = %d", potentialDistance);
                                //printf("\t D(p1, (x2,y2)) = %d\n", doubleDistance);
                                 // also check if either i or j is valid --> between 0 and MATRIXSIZE
                                if (potentialDistance == doubleDistance) {
                                    if (p1>0 && p2 > 0) {
                                        //printf("\n\tFound match for (%d, %d)\n", p1, p2);
                                        antinodes.matrix[p1][p2] = '#';
                                    };
                                }
                            }
                        }


                    }

                }
                //std::cout<< freqLoc.back().first << freqLoc.back().second << std::endl;
            }
        }
    }






    // finding unique entries in matrix antinodes
    int uniqueAntinodes = 0;
    for (int i = 0; i < MATRIXSIZE; ++i) {
        for (int j = 0; j < MATRIXSIZE; ++j) {
            if (antinodes.matrix[i][j] == '#') {
                uniqueAntinodes++;
            }
            std::cout << antinodes.matrix[i][j] << ' ';
        }
        std::cout << '\n' << std::endl;
    }
    std::cout<< "Unique antinodes:" << uniqueAntinodes << std::endl;
};


int main() {
    try {

        // 309 too high
        //matrix freqMat = readMatrixFromFile("input1.txt");
        matrix freqMat = readMatrixFromFile("test_case1.txt");
        solve_puzzle_1(freqMat);


    } catch (const std::exception& e ) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
