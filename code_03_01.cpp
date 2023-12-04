#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
std::ifstream input_file("./Inputs/input_03.txt");
std::string non_symbol(".0123456789");
std::vector<std::string> schematic;
int sum = 0;

for(std::string line; std::getline(input_file, line);){
    schematic.push_back(line);
}

for(int rr = 0; rr < schematic.size(); rr++){
    int cc_s = 0, cc_e = 0, num, min_r, max_r, min_c, max_c;
    bool valid;

    while(cc_e < schematic[rr].length()){
        valid = 0;
        cc_s = std::min(schematic[rr].find_first_of("0123456789", cc_e), schematic[rr].length());
        cc_e = std::min(schematic[rr].find_first_not_of("0123456789", cc_s), schematic[rr].length());

        if(cc_e != cc_s){num = stoi(schematic[rr].substr(cc_s, cc_e - cc_s));}
        else{continue;}

        min_r = std::max(0, rr - 1); max_r = std::min((int)schematic.size() - 1, rr + 1);
        min_c = std::max(0, cc_s - 1); max_c = std::min((int)schematic[rr].length() - 1, cc_e);

        if(min_r < rr){if(schematic[min_r].substr(min_c, max_c - min_c + 1).find_first_not_of(non_symbol) != std::string::npos){valid = 1;}}
        if(max_r > rr){if(schematic[max_r].substr(min_c, max_c - min_c + 1).find_first_not_of(non_symbol) != std::string::npos){valid = 1;}}
        if(min_c < cc_s){if(non_symbol.find(schematic[rr][min_c]) == std::string::npos){valid = 1;}}
        if(max_c == cc_e){if(non_symbol.find(schematic[rr][max_c]) == std::string::npos){valid = 1;}}
        
        sum += valid*num;
    }
}

std::cout << sum;

}



