#include <iostream>
#include <fstream>
#include <string>

class TachyonManifold {
    public:
        TachyonManifold() {}

        int process_row(const std::string& row_data) {
            //Data comes in as strings. Compare new row to existing manifold data

            //case 1: emitter
            //replace 'S' emitter with '|' beam
            // ............... current state
            // .......S....... input
            // .......|....... output

            //case 2: beam splitter
            //applying a splitter on top of a beam splits it into two beams. Applying a splitter on empty just copies the splitter as a beam
            // ....|.......... current state
            // ....^.....^.... input
            // ...|^|....^.... output

            //case 3: open space
            //open space overwrites splitters, but not beams
            // ....|.|^|.^.... current state
            // ............... input
            // ....|.|.|...... output

            //multiverse tracking:
            //we actually track the data as integers representing how many
            //paths there are to reach that specific point in the beam
            // '^' is encoded as INT_MAX-2 and '.' as INT_MAX-1 and we just hope no branch count reaches high enough to overflow (spoiler: it did, so we switched to uint64_t)
            // ....1.1..1....
            // ....^.^..1.... input
            // ...1^2^1.1.... output

            //on the first call, just initialize the manifold data
            if (_manifold_data.empty()) {
                _manifold_data = std::vector<uint64_t>(row_data.begin(), row_data.end());
                for (uint64_t& val : _manifold_data) {
                    if (val == 'S') {
                        val = 1;
                    } else {
                        val = 0;
                    }
                }
                return 0;
            }

            long split_count = 0;
            for (size_t idx = 0; idx < row_data.length(); idx++) {
                char input_char = row_data[idx];

                //now process the input character
                switch (input_char) {
                    case '^':
                        if (_manifold_data[idx] != 0) {
                            split_count++;
                        }

                        if (idx > 0) {
                            _manifold_data[idx-1] = _manifold_data[idx-1] + _manifold_data[idx];
                        }
                        if (idx < _manifold_data.size() - 1) {
                            _manifold_data[idx+1] = _manifold_data[idx+1] + _manifold_data[idx];
                        }
                        _manifold_data[idx] = 0;
                        break;
                    case '.':
                        break; //do nothing, open space so we just carry beams forward
                    default:
                        break;
                }
            }
            return split_count;
        }

        long count_timelines() {
            long timelines = 0;
            for (uint64_t t : _manifold_data) {
                timelines += t;
            }
            return timelines;
        }

    private:
        std::vector<uint64_t> _manifold_data;
};

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
    std::string line;
    TachyonManifold manifold;
    long total_splits = 0;
    while (std::getline(file, line)) {
        total_splits += manifold.process_row(line);
        // manifold.debug_print();
    }
    
    std::cout << "Day 7 - Advent of Code 2025" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Part 1: " << total_splits << std::endl;
    std::cout << "Part 2: " << manifold.count_timelines() << std::endl;
    
    return 0;
}
