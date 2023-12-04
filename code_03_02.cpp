#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

int main() {
std::ifstream input_file("./Inputs/input_03.txt");
std::vector<std::string> schematic;
int sum = 0;

for(std::string line; std::getline(input_file, line);){
    schematic.push_back(line);
}

for(int rr = 0; rr < schematic.size(); rr++){
    int idx = schematic[rr].find('*');
    while(idx < schematic[rr].length()){

        std::vector<int> num_list;

        for(int r_check = std::max(0, rr - 1); r_check < std::min((int)schematic.size(), rr + 2); r_check++){
            int c_check = std::max(0, idx - 1);
            int n_left = std::max(0, idx - 3);
            int n_right;

            while(c_check < std::min((int)schematic[rr].length(), idx + 2)){

                if(isdigit(schematic[r_check][c_check])){
                    n_left = schematic[r_check].find_first_of("0123456789", n_left);
                    n_right = schematic[r_check].find_first_not_of("0123456789", n_left);
                    if(n_right == std::string::npos){n_right = (int)schematic[rr].length();}

                    if(n_right > c_check){
                    num_list.push_back(stoi(schematic[r_check].substr(n_left, n_right - n_left)));
                    }

                    n_left = n_right;
                }
                else{
                    n_left = c_check;
                }

                c_check = n_left + 1;
            }
        }

        if(num_list.size() == 2){
            sum += num_list[0]*num_list[1];
        }

    idx = schematic[rr].find('*', idx + 1);
    }
}

std::cout << sum;

}