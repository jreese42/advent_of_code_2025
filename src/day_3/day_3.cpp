#include <iostream>
#include <fstream>
#include <string>

class BatteryBank {
public:
    BatteryBank(const std::string& bank, int max_allowed) : 
        _bank(bank), 
        _max_allowed(max_allowed) //no one will care but I called that I would need this in part 1, so pt. 2 was trivial
    {}
    long long calculate_joltage() {

        //Find the highest single digit between 0 and len-max_allowed (always leaving room at the end for the remaining digits)
        //Then find the next highest between that digit+1 and len-(max_allowed-1)
        //optimization: 9 always wins, so stop searching when you find a 9

        size_t search_start = 0;
        std::string result;
        for (size_t battery_num = 0; battery_num < _max_allowed; battery_num++) {
            char best_char = 0;
            size_t best_pos = 0;
            for (size_t pos = search_start; pos <= _bank.length() - (_max_allowed - battery_num); pos++) {
                if (_bank[pos] > best_char) {
                    best_char = _bank[pos];
                    best_pos = pos;
                    search_start = pos + 1;
                    if (best_char == '9') {
                        break; //can't do better than 9
                    }
                }
            }
            result += best_char;
        }
        return std::stoll(result);
    }
private:
    const std::string _bank;
    int _max_allowed;
};

std::string part_one(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }
    
    // Read and process input
    std::string line;
    long long joltage = 0;
    while (std::getline(file, line)) {
        BatteryBank bank(line, 2);
        joltage += bank.calculate_joltage();
    }
    
    return std::to_string(joltage);
}

std::string part_two(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }
    
    // Read and process input
    std::string line;
    long long joltage = 0;
    while (std::getline(file, line)) {
        BatteryBank bank(line, 12);
        joltage += bank.calculate_joltage();
    }
    
    return std::to_string(joltage);
}

int main(int argc, char* argv[]) {
    std::string input_file = "input";
    
    // Allow custom input file via command line argument
    if (argc > 1) {
        input_file = argv[1];
    }

    //run test cases

    std::cout << "Day 3 - Advent of Code 2025" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Part 1: " << part_one(input_file) << std::endl;
    std::cout << "Part 2: " << part_two(input_file) << std::endl;
    
    return 0;
}
