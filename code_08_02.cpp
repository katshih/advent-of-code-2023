#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <tuple>
#include <vector>
#include <algorithm>
#include <numeric>

long long gcd(long long a, long long b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

long long lcm(long long a, long long b){
    return (a / gcd(a, b))*b;
}

int main(){
    std::ifstream input_file("./Inputs/input_08.txt");

    std::string instructions, tmp;
    std::getline(input_file, instructions); std::getline(input_file, tmp);
    std::unordered_map<std::string, std::tuple<std::string, std::string>> nodes;
    std::unordered_map<std::string, std::vector<int>> cycles;
    std::vector<std::string> starts;

    for(std::string line; std::getline(input_file, line);){
        std::tuple<std::string, std::string> outputs;

        nodes[line.substr(0, 3)] = std::make_tuple(line.substr(7, 3), line.substr(12, 3));

        if(line[2] == 'A'){
            starts.push_back(line.substr(0, 3));
        }

    }
    int inst_len = instructions.length();

// should look into other cycle-detection algorithms (e.g., turtle & hare) for lower-memory option
    for(auto & s : starts){
        int steps = 0;
        std::vector<int> end_points;
        std::string curr_loc = s;
        std::set<std::string> seen_points({(curr_loc + "0")});
        bool not_done = 1;


        while(not_done){
            curr_loc = (instructions[steps % inst_len] == 'L') ? std::get<0>(nodes[curr_loc]) : std::get<1>(nodes[curr_loc]);
            steps += 1;

            not_done = seen_points.insert(curr_loc + std::to_string(steps % inst_len)).second;

            if(curr_loc[2] == 'Z'){
                end_points.push_back(steps);
            }
        }

        for(auto & i : end_points){
            std::cout << i << '\n';
        }

        cycles[s] = end_points;
    }

    // this only works because there's only one cycle per start point
    // you'd have to check combinations instead of just [0] otherwise
    long long step_total = 1; 
    for(auto &s : cycles){
        step_total = lcm(step_total, s.second[0]);
    }

    std::cout<<step_total<<'\n';

}
