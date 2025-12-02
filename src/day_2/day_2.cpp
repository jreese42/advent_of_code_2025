#include <iostream>
#include <fstream>
#include <string>

//IDs are bad if they are the same thing repeated twice
//to check this, the len must be even, and the first half must equal the second half

std::string part_one(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }

    //we don't need tons of comparisons to find bad IDs, we only need to count
    //the prefixes which fall in the range if repeated twice which massively narrows the search
    long long acc = 0;
    std::string line;
    while (std::getline(file, line, ',')) {
        //"prefix" means the first half of the ID, rounded up if odd length
        // e.g. for 95-115, we search only "9", "10", "11"
        // giving "99", "1010", "1111" as bad IDs, except only 99 is in the range
        std::string low_bound_str = line.substr(0, line.find('-'));
        std::string high_bound_str = line.substr(line.find('-') + 1);
        long long low_bound = std::stoll(low_bound_str);
        long long high_bound = std::stoll(high_bound_str);

        //edge case for single digit IDs, we'll just search from 
        std::string low_prefix_str = low_bound_str.substr(0, (low_bound_str.length()) / 2);
        long long low_prefix = std::stoll(low_prefix_str.empty() ? "0" : low_prefix_str); //rounded down on left side so lower bound is always lower
        long long high_prefix = std::stoll(high_bound_str.substr(0, (high_bound_str.length() + 1) / 2));

        for (long long prefix = low_prefix; prefix <= high_prefix; prefix++) {
            //construct bad ID from prefix
            std::string prefix_str = std::to_string(prefix);
            std::string bad_id_str = prefix_str + prefix_str;
            long long bad_id = std::stoll(bad_id_str);
            if (bad_id >= low_bound && bad_id <= high_bound) {
                acc += bad_id;
            }
        }
    }
    
    return std::to_string(acc);
}

long long helper_is_bad_id(long long id) {
    std::string id_str = std::to_string(id);
    //check every possible substring length looking for repetition
    for (size_t substr_len = 1; substr_len <= id_str.length(); substr_len++) {
        std::string substr = id_str.substr(0, substr_len);
        for (size_t pos = 0; pos < id_str.length(); pos += substr_len) { 
            if (id_str.substr(pos, substr_len) != substr || substr_len >= id_str.length()) {
                break; //quit as soon as any sub-sub-string doesnt match
            }
            if (pos + substr_len >= id_str.length()) {
                //we made it to the end with all matches, so this is a bad ID
                return id;
            }
        }
    }
    return 0;
}

std::string part_two(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }

    long long acc = 0;
    std::string line;
    while (std::getline(file, line, ',')) {
        //in part 2, the prefix trick from before doesn't work
        //we'll actually iterate through all IDs in the ranges this time - theres probably a more efficient way though
        
        std::string low_bound_str = line.substr(0, line.find('-'));
        std::string high_bound_str = line.substr(line.find('-') + 1);
        long long low_bound = std::stoll(low_bound_str);
        long long high_bound = std::stoll(high_bound_str);
        for (long long id = low_bound; id <= high_bound; id++) {
            acc += helper_is_bad_id(id);
        }
    }

    
    return std::to_string(acc);
}


int main(int argc, char* argv[]) {
    std::string input_file = "input";
    
    // Allow custom input file via command line argument
    if (argc > 1) {
        input_file = argv[1];
    }
    
    std::cout << "Day 2 - Advent of Code 2025" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Part 1: " << part_one(input_file) << std::endl;
    std::cout << "Part 2: " << part_two(input_file) << std::endl;
    
    return 0;
}
