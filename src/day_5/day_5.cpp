#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::string part_one(const std::vector<std::pair<long long,long long>>& ranges,
                     const std::vector<long long>& ids_to_check) {
    int count_fresh_ids = 0;
    for (long long id_to_check : ids_to_check) {
        for (const auto& range : ranges) {
            if (id_to_check >= range.first && id_to_check <= range.second) {
                count_fresh_ids++;
                break;
            }
        }
    }

    return std::to_string(count_fresh_ids);
}

std::string part_two(const std::vector<std::pair<long long,long long>>& ranges) {
    long long count_fresh_ids = 0;
    // Count how many fresh IDs exist
    // This is trivial since we sorted and collapsed the list
    for (const auto& range : ranges) {
        count_fresh_ids += (range.second - range.first) + 1;
    }

    return std::to_string(count_fresh_ids);
}

int main(int argc, char* argv[]) {
    std::string input_file = "input";

    // Allow custom input file via command line argument
    if (argc > 1) {
        input_file = argv[1];
    }

    std::ifstream file(input_file);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open input file" << std::endl;
        return 1;
    }

    // Read and process input
    std::vector<std::pair<long long,long long>> ranges; // ranges are stored as min-max pairs
    std::string line;

    // Read ranges from file
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }

        // Start by reading all ranges into the list direct from file
        size_t dash_pos = line.find('-');
        long long range_min = std::stoll(line.substr(0, dash_pos));
        long long range_max = std::stoll(line.substr(dash_pos + 1));
        ranges.insert(ranges.end(), std::make_pair(range_min, range_max));
    }

    // Process the ranges to handle overlaps. First, sort on min
    std::sort(ranges.begin(), ranges.end(), [](const std::pair<long long,long long>& a, const std::pair<long long,long long>& b) {
        return a.first < b.first;
    });

    // Iterate list to collapse overlapping ranges
    for (size_t idx = 0; idx < ranges.size() - 1; idx++) {
        if (ranges[idx].second >= ranges[idx + 1].first) {
            // Collapse the next range into this one if they overlap
            ranges[idx].second = std::max(ranges[idx].second, ranges[idx + 1].second);
            ranges.erase(ranges.begin() + idx + 1);
            idx--; // Stay on this index to check for further range collapses
        }
    }

    // Read IDs to check for part 1
    std::vector<long long> ids_to_check;
    while (std::getline(file, line)) {
        long long id_to_check = std::stoll(line);
        ids_to_check.push_back(id_to_check);
    }

    std::cout << "Day 5 - Advent of Code 2025" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Part 1: " << part_one(ranges, ids_to_check) << std::endl;
    std::cout << "Part 2: " << part_two(ranges) << std::endl;

    return 0;
}
