#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

void print_boxes(std::vector<std::vector<std::tuple<std::string, int>>> boxes){
    for(int b = 0; b < boxes.size(); ++b){
        if(boxes[b].size() > 0){
        std::cout << "Box " << b << ": ";
        for(auto lens : boxes[b]){
            std::cout << "[" << std::get<0>(lens) << " " << std::get<1>(lens) << "]";
        }
        std::cout << "\n";
    }
    }
    std::cout << "\n";
}

int hash(std::string s){
    int current_val = 0;
    for(char c : s){
        if(c >= 33 && c <= 126){
            current_val += c;
            current_val *= 17;
            current_val %= 256;
        }
    }
    return current_val;
}

int main(){
    std::ifstream input_file("./Inputs/input_15.txt");
    std::vector<std::vector<std::tuple<std::string, int>>> boxes(256);

    for(std::string line; std::getline(input_file, line, ',');){
        int delim = line.find_first_of("-=");
        std::string label = line.substr(0, delim);
        char operation = line[delim];
        int box = hash(label);

        //  check if label is in box
        auto label_idx = std::find_if(boxes[box].begin(), boxes[box].end(), [label](std::tuple<std::string, int> lens){return std::get<0>(lens) == label;});

        if(operation == '='){
            int focal_length = stoi(line.substr(delim + 1));
            if(label_idx != boxes[box].end()){ // if label in box, update focal length
                *label_idx = std::make_tuple(label, focal_length);
            }
            else{ // if not, place at back of box
                boxes[box].push_back(std::make_tuple(label, focal_length));
            }

        }
        else if(operation == '-'){
            // if label in box, remove label
            if(label_idx != boxes[box].end()){
                boxes[box].erase(label_idx);
            }
        }
        else{
            std::cout << "Operation invalid.\n";
        }

        //std::cout << line << "\n";
        //print_boxes(boxes);
    }

    int sum = 0;

    for(int ii = 0; ii < boxes.size(); ++ii){
        for(int jj = 0; jj < boxes[ii].size(); ++jj){
            sum += (ii + 1)*(jj + 1)*(std::get<1>(boxes[ii][jj]));
        }
    }

    std::cout << sum << "\n";

}