#include <iostream>
#include <fstream>
#include <vector>

int main(){
    std::ifstream input_file("./Inputs/input_14.txt");

    std::vector<std::string> mirror_map;

    for(std::string line; std::getline(input_file, line);){
        mirror_map.push_back(line);
    }

    // to tilt north, go column-by-column
    for(int cc = 0; cc < mirror_map[0].size(); cc++){
        int stop_row = 0;
        for(int rr = 0; rr < mirror_map.size();){
            char rock_type = mirror_map[rr][cc];

            int segment_end = rr;
            while((segment_end < mirror_map.size()) && (mirror_map[segment_end][cc] == rock_type)){
                segment_end += 1;
            }

            if(rock_type == '#'){
                stop_row = segment_end;
            }
            else if(rock_type == 'O'){
                if(stop_row != rr){ // if the rocks aren't already in place
                    int num_rocks = segment_end - rr;
                    for(int ii = stop_row; ii < (stop_row + num_rocks); ii++){
                        mirror_map[ii][cc] = 'O';
                    }
                    for(int ii = (stop_row + num_rocks); ii < segment_end; ii++){
                        mirror_map[ii][cc] = '.';
                    }
                    segment_end = stop_row + num_rocks;
                }
                stop_row = segment_end; // regardless, update where the last rock is
            }

            rr = segment_end;
        }
    }

    int weight = mirror_map.size(), sum = 0;
    for(std::string line : mirror_map){
        int rock_count = 0;
        for(char c : line){
            if(c == 'O'){rock_count += 1;}
        }
        sum += weight*rock_count;
        weight -= 1;
    }

std::cout << sum << "\n";
}