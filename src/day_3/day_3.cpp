#include <iostream>
#include <fstream>
#include <string>

std::string part_one(const std::string& input_file) {
    // TODO: Implement part one solution
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }
    
    // Read and process input
    std::string line;
    while (std::getline(file, line)) {
        // Process each line
    }
    
    return "Not implemented yet";
}

std::string part_two(const std::string& input_file) {
    // TODO: Implement part two solution
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }
    
    // Read and process input
    std::string line;
    while (std::getline(file, line)) {
        // Process each line
    }
    
    return "Not implemented yet";
}

int main(int argc, char* argv[]) {
    std::string input_file = "input";
    
    // Allow custom input file via command line argument
    if (argc > 1) {
        input_file = argv[1];
    }
    
    std::cout << "Day 3 - Advent of Code 2025" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Part 1: " << part_one(input_file) << std::endl;
    std::cout << "Part 2: " << part_two(input_file) << std::endl;
    
    return 0;
}
