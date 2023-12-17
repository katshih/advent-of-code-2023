#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <limits.h>
#include <unordered_map>

int main(){
    std::ifstream input_file("./Inputs/input_17.txt");
    std::vector<std::string> layout;
    std::unordered_map<std::string, int> node_cost;
    std::vector<std::vector<int>> facing({{0, 1}, {1, 0}, {0, -1}, {-1, 0}});

    for(std::string line; std::getline(input_file, line);){
        layout.push_back(line);
    }

    int num_rows = layout.size(), num_cols = layout[0].size();
    //std::cout << num_rows << ", " << num_cols << "\n";

    auto comp = [num_rows, num_cols] (std::vector<int> a, std::vector<int> b) -> bool {
        int f_a = a[0] + std::abs(num_rows - 1 - a[1]) + std::abs(num_cols - 1 - a[2]);
        int f_b = b[0] + std::abs(num_rows - 1 - b[1]) + std::abs(num_cols - 1 - b[2]);

        return f_a > f_b; // why is this greater
    };
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, decltype(comp)> path_nodes(comp);

    // {cost_so_far, x_pos, y_pos, facing, steps_taken}
    std::vector<int> start_node_1({0, 0, 0, 1, 0});
    std::vector<int> start_node_2({0, 0, 0, 0, 0});
    path_nodes.push(start_node_1); path_nodes.push(start_node_2);

    int min_cost = INT_MAX;
    while(!path_nodes.empty()){
        std::vector<int> curr_node = path_nodes.top();

        if((curr_node[4] >= 4) && ((curr_node[1] == (num_rows - 1)) && (curr_node[2] == (num_cols - 1)))){
            min_cost = curr_node[0]; //std::min(curr_node[0], min_cost);
            break;
        }
        path_nodes.pop();

        //std::cout << std::to_string(curr_node[0]) + "|" + std::to_string(curr_node[1]) + "|" + std::to_string(curr_node[2]) + "|" + 
        //                                std::to_string(curr_node[3]) + "|" + std::to_string(curr_node[4]) + "\n"; 

        for(int turn : std::vector<int>({-1, 0, 1})){
            int next_facing = (((curr_node[3] + turn) % 4) + 4) % 4;
            int next_row = curr_node[1] + facing[next_facing][0], next_col = curr_node[2] + facing[next_facing][1];
            int next_steps = ((turn == 0) ? curr_node[4] : 0) + 1;

            if(turn == 0){ // can move maximum of 10 steps forward
                if((next_steps <= 10) && ((next_row >= 0) && (next_row < num_rows)) && ((next_col >= 0) && (next_col <  num_cols))){
                    int next_cost = curr_node[0] + layout[next_row][next_col] - '0';
                    std::string node_str = std::to_string(next_row) + "|" + std::to_string(next_col) + "|" + 
                                            std::to_string(next_facing) + "|" + std::to_string(next_steps);                
                    
                    if((!node_cost.count(node_str)) || (next_cost < node_cost[node_str])){
                        node_cost[node_str] = next_cost;
                        path_nodes.push(std::vector<int>({next_cost, next_row, next_col, next_facing, next_steps}));
                        //std::cout << std::to_string(next_cost) + "|" + node_str << "\n";
                    }
                }
            }
            else{ // needs to move 4 steps before turning
                if((curr_node[4] >= 4) && ((next_row >= 0) && (next_row < num_rows)) && ((next_col >= 0) && (next_col <  num_cols))){
                    int next_cost = curr_node[0] + layout[next_row][next_col] - '0';
                    std::string node_str = std::to_string(next_row) + "|" + std::to_string(next_col) + "|" + 
                                            std::to_string(next_facing) + "|" + std::to_string(next_steps);                
                    
                    if((!node_cost.count(node_str)) || (next_cost < node_cost[node_str])){
                        node_cost[node_str] = next_cost;
                        path_nodes.push(std::vector<int>({next_cost, next_row, next_col, next_facing, next_steps}));
                        //std::cout << std::to_string(next_cost) + "|" + node_str << "\n";
                    }
                }
            }
        }
    
        //std::cout << "\n";
        //std::getchar();
    }

std::cout << min_cost << "\n";

}