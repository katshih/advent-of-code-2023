#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main(){
std::ifstream input_file("./Inputs/input_10.txt");
std::vector<std::vector<char>> pipe_map;
std::vector<int> start_point;
std::unordered_map<char, std::vector<std::vector<int>>> map_key({{'|', {{-1, 0}, {1, 0}}}, {'-', {{0, -1}, {0, 1}}},
                                                                {'L', {{-1, 0}, {0, 1}}}, {'J', {{-1, 0}, {0, -1}}},
                                                                {'7', {{1, 0}, {0, -1}}}, {'F', {{1, 0}, {0, 1}}},
                                                                {'.', {{0, 0}}}, {'S', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}});

for(std::string line; std::getline(input_file, line);){
    std::vector<char> map_line;
    for(auto &c : line){
        if(c == 'S'){
            start_point = {int(pipe_map.size()), int(map_line.size())};
        }
        map_line.push_back(c);
    }
    pipe_map.push_back(map_line);
}

std::vector<int> curr_point = start_point;
std::vector<int> last_step({0, 0}), next_step;

int path_length = 0;
char current_pipe = 'S', next_pipe;

// for starting point, need to find a valid path
for(auto &step : map_key[current_pipe]){
    std::vector<int> next_point({curr_point[0] + step[0], curr_point[1] + step[1]});
    if(((next_point[0] >= 0) & (next_point[0] < pipe_map.size())) & ((next_point[1] >= 0) & (next_point[1] < pipe_map[0].size()))){
        last_step = step;
        next_pipe = pipe_map[next_point[0]][next_point[1]];

        if(std::find_if(map_key[next_pipe].begin(), map_key[next_pipe].end(), [last_step] (std::vector<int> v) {return (((v[0] == -last_step[0]) & (v[1] == -last_step[1])));}) != map_key[next_pipe].end()){
            curr_point = next_point;
            path_length += 1;
            break;
        }
    }
}

while(!std::equal(start_point.begin(), start_point.begin() + 2, curr_point.begin())){
    current_pipe = pipe_map[curr_point[0]][curr_point[1]];

    last_step = *std::find_if(map_key[current_pipe].begin(), map_key[current_pipe].end(), [last_step] (std::vector<int> v) {return (!((v[0] == -last_step[0]) & (v[1] == -last_step[1])));});
    curr_point = {curr_point[0] + last_step[0], curr_point[1] + last_step[1]};
    path_length += 1;
}

std::cout << path_length/2 << "\n";
}