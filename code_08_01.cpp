#include <iostream>
#include <fstream>
#include <unordered_map>
#include <tuple>

int main(){
    std::ifstream input_file("./Inputs/input_08.txt");

    std::string instructions, tmp;
    std::getline(input_file, instructions); std::getline(input_file, tmp);
    std::unordered_map<std::string, std::tuple<std::string, std::string>> nodes;

    for(std::string line; std::getline(input_file, line);){
        std::tuple<std::string, std::string> outputs;

        nodes[line.substr(0, 3)] = std::make_tuple(line.substr(7, 3), line.substr(12, 3));
    }

    int steps = 0, inst_len = instructions.length();
    std::string curr_loc = "AAA";

    while(curr_loc != "ZZZ"){
        curr_loc = (instructions[steps % inst_len] == 'L') ? std::get<0>(nodes[curr_loc]) : std::get<1>(nodes[curr_loc]);
        steps += 1;
    }

    std::cout << steps << '\n';

}