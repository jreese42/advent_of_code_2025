#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


std::string read_last_line(const std::string& input_file) {
    std::ifstream f_in(input_file);
     if (!f_in.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return "";
    }

    f_in.seekg(-1, std::ios_base::end); 

    char ch;
    bool keepLooping = true;
    while (keepLooping) {
        f_in.get(ch);

        if (static_cast<int>(f_in.tellg()) <= 1) { 
            f_in.seekg(0); 
            keepLooping = false;
        } else if (ch == '\n') { 
            keepLooping = false;
        } else {
            f_in.seekg(-2, std::ios_base::cur); 
        }

    }

    std::string lastLine;            
    std::getline(f_in, lastLine);
    return lastLine;
}

class ProblemSet {
    public:
        enum class Race { HUMAN, CEPHALOPOD };
        class MathProblem {
            public:
                using OperatorFunction = std::function<long(long, long)>;

                MathProblem() : 
                    _operands(),
                    _operator()
                {
                }

                void add_operand(long operand) {
                    _operands.push_back(operand);
                }

                size_t count_operands() const {
                    return _operands.size();
                }

                long get_operand(size_t index) const {
                    if (index < _operands.size()) {
                        return _operands[index];
                    }
                    return 0;
                }

                void set_operand(size_t index, long value) {
                    if (index < _operands.size()) {
                        _operands[index] = value;
                    }
                }

                void set_operator(OperatorFunction op) {
                    _operator = op;
                }

                long solve() const {
                    long result = _operands[0];
                    for (size_t i = 1; i < _operands.size(); i++) {
                        result = _operator(result, _operands[i]);
                    }
                    return result;
                }

            private:
                std::vector<long> _operands;
                //well store the operator as function pointer to a function which takes two longs and returns a long
                OperatorFunction _operator;
        };

        ProblemSet(const std::string& input_file, Race race) :
            _problems()
        {
            switch (race)
            {
            case Race::HUMAN:
                construct_problems_human(input_file);
                break;
            case Race::CEPHALOPOD:
                construct_problems_cephalopod(input_file);
                break;
            default:
                break;
            }
        }
    
        const std::vector<MathProblem>& get_problems() const {
            return _problems;
        }

    private:
        std::vector<MathProblem> _problems;

        void construct_problems_human(const std::string& input_file) {
            std::ifstream file(input_file);

            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string token;
                size_t problem_idx = 0;

                while (iss >> token) {
                    //all digits means operand
                    if (std::all_of(token.begin(), token.end(), ::isdigit)) {
                        if (problem_idx >= _problems.size()) {
                            MathProblem problem;
                            _problems.push_back(problem);
                        }
                        _problems[problem_idx].add_operand(std::stol(token));
                    }
                    //otherwise, it's an operator
                    else if (token == "+") {
                        _problems[problem_idx].set_operator([](long a, long b) { return a + b; });
                    }
                    else if (token == "*") {
                        _problems[problem_idx].set_operator([](long a, long b) { return a * b; });
                    }

                    problem_idx++;
                }
            }
        }

        void construct_problems_cephalopod(const std::string& input_file) {
            //first we want to know the colums of the operators which marks the left side of each problem
            std::string operators_line = read_last_line(input_file);
            std::vector<size_t> problem_cols;

            for (size_t idx = 0; idx < operators_line.length(); idx++) {
                if (operators_line[idx] != ' ') {
                    problem_cols.push_back(idx);
                    _problems.push_back(MathProblem());
                    _problems.back().set_operator(
                        (operators_line[idx] == '+') ? 
                        [](long a, long b) { return a + b; } : 
                        [](long a, long b) { return a * b; });
                }
            }

            //now read the file again, this time parsing operands
            std::ifstream file(input_file);
            std::string line;
            while (std::getline(file, line)) {
                size_t curr_problem_id = -1;
                size_t local_problem_operand_idx = 0;
                //grab an iterator to the current problem column vector
                auto next_problem_col_it = problem_cols.begin();
                size_t next_problem_col = (next_problem_col_it != problem_cols.end()) ? *next_problem_col_it : -1;

                for (size_t idx = 0; idx < line.length(); idx++) {
                    char c = line[idx];
                    //if we reach the next problem column, increment problem id and move to next problem col
                    if (idx == next_problem_col) {
                        curr_problem_id++;
                        next_problem_col_it++;
                        next_problem_col = (next_problem_col_it != problem_cols.end()) ? *next_problem_col_it : -1;
                        local_problem_operand_idx = 0;
                    }

                    //if needed create a new operand first
                    //only create a new operand if we're within the problem's column range (not trailing whitespace at the end of the line)
                    if (local_problem_operand_idx >= _problems[curr_problem_id].count_operands() && idx + 1 < next_problem_col) {
                        _problems[curr_problem_id].add_operand(0);
                    }

                    //finally, actually update the operand value
                    //the topmost digit is the highest place value, so we multiply the current operand by 10 and add the new digit
                    //then we can keep iterating to build up the full operand value as we read each line
                    if (std::isdigit(c)) { //skip the spaces
                        _problems[curr_problem_id].set_operand(local_problem_operand_idx,
                            _problems[curr_problem_id].get_operand(local_problem_operand_idx) * 10 + (c - '0'));
                    }

                    local_problem_operand_idx++;

                }
            }
        }
};


std::string part_one(const ProblemSet& problem_set) {
    long acc = 0;
    for (const auto& problem : problem_set.get_problems()) {
        acc += problem.solve();
    }
    
    return std::to_string(acc);
}

std::string part_two(const ProblemSet& problem_set) {
    long acc = 0;
    for (const auto& problem : problem_set.get_problems()) {
        acc += problem.solve();
    }
    
    return std::to_string(acc);
}

int main(int argc, char* argv[]) {
    std::string input_file = "input";
    
    // Allow custom input file via command line argument
    if (argc > 1) {
        input_file = argv[1];
    }

    ProblemSet problem_set_human(input_file, ProblemSet::Race::HUMAN);
    ProblemSet problem_set_cephalopod(input_file, ProblemSet::Race::CEPHALOPOD);
    
    std::cout << "Day 6 - Advent of Code 2025" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Part 1: " << part_one(problem_set_human) << std::endl;
    std::cout << "Part 2: " << part_two(problem_set_cephalopod) << std::endl;
    
    return 0;
}
