#include <iostream>
#include <fstream>
#include <string>

std::string part_one(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }
    
    // Read and process input
    std::string grid;
    std::string line;
    int width = 0;
    while (std::getline(file, line)) {
        grid += line;
        width = line.length();
    }

    //we'll just operate on this string since we have to read text anyway
    //we can just do 8 separate comparisons which is just as efficient as any complex data structure as far as cycle counts go
    int accessible_rolls = 0;
    for (size_t idx = 0; idx < grid.length(); idx++) {
        int neighbor_paper_count = 0;
        if (grid[idx] == '@') {
            bool is_N_edge = (idx < width);
            bool is_S_edge = (idx >= grid.length() - width);
            bool is_E_edge = ((idx + 1) % width == 0);
            bool is_W_edge = (idx % width == 0);
            
            if (!is_N_edge && grid[idx - width] == '@') neighbor_paper_count++; //N
            if (!is_S_edge && grid[idx + width] == '@') neighbor_paper_count++; //S
            if (!is_W_edge && grid[idx - 1] == '@') neighbor_paper_count++; //W
            if (!is_E_edge && grid[idx + 1] == '@') neighbor_paper_count++; //E
            if (!is_N_edge && !is_E_edge && grid[idx - width + 1] == '@') neighbor_paper_count++; //NE
            if (!is_N_edge && !is_W_edge && grid[idx - width - 1] == '@') neighbor_paper_count++; //NW
            if (!is_S_edge && !is_E_edge && grid[idx + width + 1] == '@') neighbor_paper_count++; //SE
            if (!is_S_edge && !is_W_edge && grid[idx + width - 1] == '@') neighbor_paper_count++; //SW
            
            accessible_rolls += (neighbor_paper_count < 4) ? 1 : 0;
        }

    }
    
    return std::to_string(accessible_rolls);
}

std::string part_two(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        return "Error: Could not open input file";
    }
    
    // Read and process input
    std::string line;
    std::vector<uint8_t> grid;
    int width = 0;
    while (std::getline(file, line)) {
        for (char& c : line) {
            if (c == '.') c = 0x00; //empty space
            else c = 0xFF; //present roll of paper
            grid.push_back(c);
        }
        width = line.length();
    }

    int removed_rolls_total = 0;
    int removed_rolls = 0;
    int round = 0;
    do {
        removed_rolls = 0;
        for (size_t idx = 0; idx < grid.size(); idx++) {
            int neighbor_paper_count = 0;
            if (grid[idx] == 0xFF) {
                bool is_N_edge = (idx < width);
                bool is_S_edge = (idx >= grid.size() - width);
                bool is_E_edge = ((idx + 1) % width == 0);
                bool is_W_edge = (idx % width == 0);

                //current_round_marker = '@' + round;
                
                //just to be difficult, we'll store in the grid a value indicating in which iteration we removed it which lets us compare grids without extra memory
                //on the initial read we replace all the '.' with 0 and '@' with FF just so we have more room to count
                // e.g.
                //      '0xFF' indicates an untouched roll, '0x00' indicates an empty space
                //      '0x01' indicates removed in first round
                //      if we are in round x, then any cell > x is still present, but anything lower than that was removed in a prior round
                //          round 1: <=0 is empty, >0 is present, mark removed rolls as 1
                //          round 2: <=1 is empty, >1 is present, mark removed rolls as 2.
                if (!is_N_edge && grid[idx - width] > round) neighbor_paper_count++; //N
                if (!is_S_edge && grid[idx + width] > round) neighbor_paper_count++; //S
                if (!is_W_edge && grid[idx - 1] > round) neighbor_paper_count++; //W
                if (!is_E_edge && grid[idx + 1] > round) neighbor_paper_count++; //E
                if (!is_N_edge && !is_E_edge && grid[idx - width + 1] > round) neighbor_paper_count++; //NE
                if (!is_N_edge && !is_W_edge && grid[idx - width - 1] > round) neighbor_paper_count++; //NW
                if (!is_S_edge && !is_E_edge && grid[idx + width + 1] > round) neighbor_paper_count++; //SE
                if (!is_S_edge && !is_W_edge && grid[idx + width - 1] > round) neighbor_paper_count++; //SW
                
                if (neighbor_paper_count < 4) {
                    grid[idx] = round+1;
                    removed_rolls++;
                }


            }
        }

        removed_rolls_total += removed_rolls;
        round++;

    } while (removed_rolls > 0);
    

    
    return std::to_string(removed_rolls_total);
}

int main(int argc, char* argv[]) {
    std::string input_file = "input";
    
    // Allow custom input file via command line argument
    if (argc > 1) {
        input_file = argv[1];
    }
    
    std::cout << "Day 4 - Advent of Code 2025" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Part 1: " << part_one(input_file) << std::endl;
    std::cout << "Part 2: " << part_two(input_file) << std::endl;
    
    return 0;
}
