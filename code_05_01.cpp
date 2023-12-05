#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <limits>

long get_destination(long source, std::vector<std::vector<long>> map){
    long destination = source;

    for(auto &line : map){
        if((source >= line[1]) && (source < line[1] + line[2])){
            destination = line[0] + (source - line[1]);
            break;
        }
    }

    return destination;
}

int main(){
    std::ifstream input_file("./Inputs/input_05.txt");
    std::map<int, std::vector<std::vector<long>>> atlas;
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
                atlas[order] = map;
            }
            order += 1;
            map.clear();
        }
        else if(isdigit(line[0])){
            int div1 = line.find(' '); int div2 = line.find(' ', div1 + 1);
            map.push_back(std::vector<long>{stol(line.substr(0, div1)), stol(line.substr(div1 + 1, div2 - div1)), stol(line.substr(div2 + 1, line.length() - div2))});
        }
    }
    atlas[order] = map;

    // go through seeds
    long min_loc = std::numeric_limits<long>::max(), curr_loc;

    for(auto &s : seeds){
        curr_loc = s;
        //std::cout << curr_loc << '\n';
        for(auto &o_map : atlas){
            curr_loc = get_destination(curr_loc, o_map.second);
            //std::cout << curr_loc << '\n';
        }
        if(curr_loc < min_loc){
            min_loc = curr_loc;
        }
        //std::cout<<'\n';
    }

    std::cout<<min_loc;
}