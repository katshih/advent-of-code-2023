#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <deque>

void add_beam(std::vector<int> next_step, std::deque<std::vector<int>> &beams, std::unordered_set<std::string> &nodes_seen){
    std::string next_step_str = std::to_string(next_step[0]) + "|" + std::to_string(next_step[1]) + "|" + std::to_string(next_step[2]) + "|" + std::to_string(next_step[3]);
    if(!nodes_seen.count(next_step_str)){
        nodes_seen.insert(next_step_str);
        beams.push_back(next_step);
    }
}

int main(){
    std::ifstream input_file("./Inputs/input_16.txt");

    std::vector<std::string> layout;
    std::unordered_set<std::string> nodes_seen;
    std::deque<std::vector<int>> beams;

    for(std::string line; std::getline(input_file, line);){
        layout.push_back(line);
    }

    int num_cols = layout[0].size(), num_rows = layout.size();
    std::vector<std::vector<bool>> energized(num_rows, std::vector<bool>(num_cols, 0));

    std::vector<int> first_node({0, 0, 0, 1});
    add_beam(first_node, beams, nodes_seen);

    while(!beams.empty()){
        std::vector<int> beam_active = beams.front();
        std::vector<int> next_step;

        // if beam is inside bounds
        if(((beam_active[0] >= 0) && (beam_active[0] < num_rows)) && (beam_active[1] >= 0) && (beam_active[1] < num_cols)){
            energized[beam_active[0]][beam_active[1]] = 1; // update energy map
            char loc_type = layout[beam_active[0]][beam_active[1]];

            if(loc_type == '.'){ // add next location in the same direction to the queue
                next_step = std::vector<int>({beam_active[0] + beam_active[2], beam_active[1] + beam_active[3], beam_active[2], beam_active[3]});
                add_beam(next_step, beams, nodes_seen);
            }
            else if(loc_type == '/'){ // this swaps and inverts vertical/horizontal travel
                int new_vert = -beam_active[3], new_hor = -beam_active[2];
                next_step = std::vector<int>({beam_active[0] + new_vert, beam_active[1] + new_hor, new_vert, new_hor});
                add_beam(next_step, beams, nodes_seen);
            }
            else if(loc_type == '\\'){ // this swaps vertical/horizontal travel
                int new_vert = beam_active[3], new_hor = beam_active[2];
                next_step = std::vector<int>({beam_active[0] + new_vert, beam_active[1] + new_hor, new_vert, new_hor});
                add_beam(next_step, beams, nodes_seen);
            }
            else if(loc_type == '|'){
                if(beam_active[3] != 0){ // beam is traveling horizontally; split
                    // add next location below, traveling downwards
                    next_step = std::vector<int>({beam_active[0] - 1, beam_active[1], -1, 0});
                    add_beam(next_step, beams, nodes_seen);
                    // add next location above, traveling upwards
                    next_step = std::vector<int>({beam_active[0] + 1, beam_active[1], 1, 0});
                    add_beam(next_step, beams, nodes_seen);
                }
                else{ // keep going
                    next_step = std::vector<int>({beam_active[0] + beam_active[2], beam_active[1] + beam_active[3], beam_active[2], beam_active[3]});
                    add_beam(next_step, beams, nodes_seen);
                }
            }
            else if(loc_type == '-'){
                if(beam_active[2] != 0){ // beam is traveling vertically; split
                    // add next location to the left, traveling left
                    next_step = std::vector<int>({beam_active[0], beam_active[1] - 1, 0, -1});
                    add_beam(next_step, beams, nodes_seen);
                    // add next location to the right, traveling right
                    next_step = std::vector<int>({beam_active[0], beam_active[1] + 1, 0, 1});
                    add_beam(next_step, beams, nodes_seen);
                }
                else{ // keep going
                    next_step = std::vector<int>({beam_active[0] + beam_active[2], beam_active[1] + beam_active[3], beam_active[2], beam_active[3]});
                    add_beam(next_step, beams, nodes_seen);
                }
            }
            else{
                std::cout << "Bad input?\n";
            }
        }
        beams.pop_front();
    }

    // for(auto i : layout){
    //     std::cout << i << '\n';
    // }

    int sum = 0;
    for(auto i : energized){
        for(bool b : i){
            // std::cout << b;
            if(b){sum += 1;}
        }
        // std::cout << '\n';
    }

std::cout << sum << "\n";

// for(auto i : nodes_seen){
//     std::cout << i << "\n";
// }

}