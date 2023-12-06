#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <limits>
#include <algorithm>

// this gets the right answer, but I think there is still an off-by-one in the range selection

std::vector<std::vector<long>> mergeIntervals(std::vector<std::vector<long>> ranges){
    std::sort(ranges.begin(), ranges.end());

    std::stack<std::vector<long>> output_stack;
    output_stack.push(ranges[0]);

    for(int ii = 1; ii < ranges.size(); ii++){
        std::vector<long> curr = ranges[ii];

        if(curr[0] <= output_stack.top()[1] + 1){
            output_stack.top()[1] = std::max(output_stack.top()[1], curr[1]);
        }
        else{
            output_stack.push(curr);
        }
    }

    std::vector<std::vector<long>> output_merged;
    while(!output_stack.empty()){
        output_merged.insert(output_merged.begin(), output_stack.top());
        output_stack.pop();
    }

    return output_merged;
}

class piecewiseLine{
    public:
        piecewiseLine(std::vector<std::vector<long>> map);
        //piecewiseLine(piecewiseLine lin_1, piecewiseLine lin_2);

        long evaluate(long input);
        std::vector<std::vector<long>> evaluateRange(std::vector<std::vector<long>> input_ranges);

    private:
        std::vector<long> intervals_, constants_;
};

// PL from set of (destination, source, range) vectors
piecewiseLine::piecewiseLine(std::vector<std::vector<long>> map){
    std::vector<long> intervals, constants;

    std::sort(map.begin(), map.end(), [](const std::vector<long>& a, const std::vector<long>& b){return a[1] < b[1];});

    long last_int_end = 0;

    for(auto &line : map){
        if(line[1] > last_int_end){ // not specified in map
            intervals.push_back(last_int_end);
            constants.push_back(0);
        }
        intervals.push_back(line[1]);
        constants.push_back(line[0] - line[1]);
        last_int_end = line[1] + line[2];
    }
    intervals.push_back(last_int_end);
    constants.push_back(0);

    intervals_ = intervals; constants_ = constants;
}

// evaluate a single value
long piecewiseLine::evaluate(long input){
    // find interval
    int idx = (int)(std::upper_bound(intervals_.begin(), intervals_.end(), input) - intervals_.begin()) - 1;
    return (input + constants_[idx]);
}

// evaluate a set of ranges
std::vector<std::vector<long>> piecewiseLine::evaluateRange(std::vector<std::vector<long>> input_ranges){
    std::vector<std::vector<long>> output;

    for(auto &input : input_ranges){
        long i_low = input[0], i_high = input[0];
        while(i_high < input[1]){
            int idx_lower = (int)(std::upper_bound(intervals_.begin(), intervals_.end(), i_low) - intervals_.begin()) - 1;
            if((idx_lower + 1 != intervals_.size()) && intervals_[idx_lower + 1] <= input[1]){
                i_high = intervals_[idx_lower + 1];
            }
            else{
                i_high = input[1];
            }

            output.push_back(std::vector<long>{i_low + constants_[idx_lower], i_high + constants_[idx_lower]});
            i_low = i_high;
        }
    }

    // consolidate
    return mergeIntervals(output);
}

int main(){
    std::ifstream input_file("./Inputs/input_05.txt");
    std::vector<piecewiseLine> atlas;
    std::vector<std::vector<long>> seed_ranges;

    std::string line; std::getline(input_file, line);
    // read in seeds
    bool s_flag = 1;
    long range_start;
    int ii_s = line.find(' ') + 1, ii_e = ii_s;
    while(ii_e < line.length()){
        ii_e = line.find(' ', ii_s + 1);
        long num = stol(line.substr(ii_s, ii_e - ii_s));
        if(s_flag){
            range_start = num;
            s_flag = 0;
        }
        else{
            seed_ranges.push_back({range_start, range_start + num - 1});
            s_flag = 1;
        }
        ii_s = ii_e + 1;
    }

    // read in maps
    int order = 0; std::vector<std::vector<long>> map;
    while(std::getline(input_file, line)){
        if(line.find("map") != std::string::npos){
            if(order != 0){
                atlas.push_back(piecewiseLine(map));
            }
            order += 1;
            map.clear();
        }
        else if(isdigit(line[0])){
            int div1 = line.find(' '); int div2 = line.find(' ', div1 + 1);
            map.push_back(std::vector<long>{stol(line.substr(0, div1)), stol(line.substr(div1 + 1, div2 - div1)), stol(line.substr(div2 + 1, line.length() - div2))});
        }
    }
    atlas.push_back(piecewiseLine(map));

    std::sort(seed_ranges.begin(), seed_ranges.end());
    std::vector<std::vector<long>> output_ranges = seed_ranges;

    //for(auto & o : output_ranges){
    //std::cout << "Range [" << o[0] << ", " << o[1] << "]\n";
    //}    
    //std::cout << "\n";

    for(auto &pl : atlas){
        output_ranges = pl.evaluateRange(output_ranges);
    //    for(auto & o : output_ranges){
    //    std::cout << "Range [" << o[0] << ", " << o[1] << "]\n";
    //    }
    //    std::cout << "\n";    
    }

    std::cout<<output_ranges[0][0];

}