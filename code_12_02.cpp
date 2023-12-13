#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

int get_arrangements(std::string blueprint, std::vector<int> counts, int cidx){
    if((cidx >= counts.size())){ // no more groups to match
        if(blueprint.find('#') >= blueprint.size()){ // no more hashes in sequence
            return 1;
        }
        else{ // there are extra hashes
            return 0;
        }
    }
    else if(counts.at(cidx) > blueprint.size()){ // the sequence isn't long enough for the current group
        //std::cout << "too many hashes needed \n";
        return 0;
    }
    else{
        if(blueprint[0] == '.'){ // leading '.' can be ignored
            //std::cout << "cut off lone . \n";
            return get_arrangements(blueprint.substr(1), counts, cidx);
        }
        else if(blueprint[0] == '#'){ // check if leading '#' corresponds to first group remaining
            if((blueprint.substr(0, counts.at(cidx)).find('.') >= counts.at(cidx)) && (blueprint[counts.at(cidx)] != '#')){ // the sequence of '#' and '?' is long enough, and there's space for a '.' afterwards
                //std::cout << "found group, chopping off hashes \n";
                if(counts.at(cidx) >= blueprint.size()){
                    return get_arrangements(std::string(""), counts, cidx + 1);
                }
                else{
                    return get_arrangements(blueprint.substr(counts.at(cidx) + 1), counts, cidx + 1);
                }
            }
            else{
                //std::cout << "not enough or too many hashes \n";
                return 0;
            }
        }
        else{
            //std::cout << "forking \n";
            int arr = 0;
            blueprint[0] = '#';
            arr += get_arrangements(blueprint, counts, cidx);
            //std::cout << "(fork here)\n";
            arr += get_arrangements(blueprint.substr(1), counts, cidx);
            return arr;
        }
    }
}


int main(){
    std::ifstream input_file("./Inputs/input_12.txt");

    int sum = 0;
    int ii = 1;

    for(std::string line; std::getline(input_file, line);){
        int split = line.find(' ');
        std::string blueprint = line.substr(0, split);
        std::vector<int> counts;

        std::string token; std::istringstream stream(line.substr(split));
        while(std::getline(stream, token, ',')){
            counts.push_back(stoi(token));
        }

        std::string blueprint_long = blueprint;
        std::vector<int> counts_long = counts;

        for(int jj = 0; jj < 4; jj++){
            blueprint_long += "?" + blueprint;
            for(int i : counts){
                counts_long.push_back(i);
            }
        }

        int arr = get_arrangements(blueprint_long, counts_long, 0);

        std::cout<< ii << " " << blueprint_long << " " << arr <<  "\n";

        sum += arr;
        ii += 1;
    }

std::cout << sum << "\n";

}