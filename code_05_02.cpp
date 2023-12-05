#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

class piecewiseLine{
    public:
        piecewiseLine(std::vector<std::vector<long>> map);
        //piecewiseLine(piecewiseLine lin_1, piecewiseLine lin_2);

        long evaluate(long input);

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

// PL from composition of two PLs
//piecewiseLine::piecewiseLine(piecewiseLine lin_1, piecewiseLine lin_2){

//}

// evaluate a single value
long piecewiseLine::evaluate(long input){
    // find interval
    int idx = (int)(std::upper_bound(intervals_.begin(), intervals_.end(), input) - intervals_.begin()) - 1;
    return (input + constants_[idx]);
}

int main(){
    std::ifstream input_file("./Inputs/input_05.txt");
    std::vector<piecewiseLine> atlas;
    std::vector<long> seeds;

    std::string line; std::getline(input_file, line);
    // read in seeds
    int ii_s = line.find(' ') + 1, ii_e = ii_s;
    while(ii_e < line.length()){
        ii_e = line.find(' ', ii_s + 1);
        seeds.push_back(stol(line.substr(ii_s, ii_e - ii_s)));
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




    //    go through seeds
    // long min_loc = std::numeric_limits<long>::max(), curr_loc;

    // for(auto &s : seeds){
    //     curr_loc = s;
    //     std::cout << curr_loc << '\n';
    //     for(auto &pl : atlas){
    //         curr_loc = pl.evaluate(curr_loc);
    //         std::cout << curr_loc << '\n';
    //     }
    //     if(curr_loc < min_loc){
    //         min_loc = curr_loc;
    //     }
    //     std::cout<<'\n';
    // }

    // std::cout << min_loc;



    // compose piecewise linear functions into one
    // find minimum value over a range
}