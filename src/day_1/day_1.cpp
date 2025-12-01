#include <iostream>
#include <fstream>
#include <string>

std::string part_one(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }
    
    // Read and process input
    std::string line;
    int dial = 50;
    int acc = 0;
    while (std::getline(file, line)) {
        // we only need an accumulator to solve this, since we only care when landing on 0
        // first character is positive or negative
        #define DIAL_MAX 99
        #define WRAP_AROUND(x) (((x) % (DIAL_MAX+1) + DIAL_MAX + 1) % (DIAL_MAX + 1))
        if (line[0] == 'L') {
            // move left
            dial -= std::stoi(line.substr(1));
        } else if (line[0] == 'R') {
            // move right
            dial += std::stoi(line.substr(1));
        }
        dial = WRAP_AROUND(dial);
        if (dial == 0) {
            acc++;
        }
    }
    
    return std::to_string(acc);
}

std::string part_two(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }
    
    // Read and process input
    std::string line;
    int dial = 50;
    int acc = 0;
    while (std::getline(file, line)) {
        // we only need an accumulator to solve this, since we only care when landing on 0
        // first character is positive or negative
        // we need to count any wraparound which means any time dial is OOB after a move
        #define DIAL_MAX 99
        #define WRAP_AROUND(x) (((x) % (DIAL_MAX+1) + DIAL_MAX + 1) % (DIAL_MAX + 1))
        bool was_zero = (dial == 0);
        if (line[0] == 'L') {
            // move left
            dial -= std::stoi(line.substr(1));
        } else if (line[0] == 'R') {
            // move right
            dial += std::stoi(line.substr(1));
        }

        // count how many times we passed 0, correcting for edge case of starting on 0 and moving left
        acc += abs(dial / (DIAL_MAX + 1)) + (dial <= 0) - (was_zero && dial < 0 ? 1 : 0);
        dial = WRAP_AROUND(dial);

    }
    
    return std::to_string(acc);
}

int main(int argc, char* argv[]) {
    std::string input_file = "input";
    
    // Allow custom input file via command line argument
    if (argc > 1) {
        input_file = argv[1];
    }
    
    std::cout << "Day 1 - Advent of Code 2025" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Part 1: " << part_one(input_file) << std::endl;
    std::cout << "Part 2: " << part_two(input_file) << std::endl;
    
    return 0;
}
