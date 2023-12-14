#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>

std::vector<std::string> transpose(std::vector<std::string> rows){
    std::vector<std::string> cols(rows[0].size());

    for(int ii = 0; ii < rows.size(); ii++){
        for(int jj = 0; jj < rows[0].size(); jj++){
            cols[jj] += rows[ii][jj];
        }
    }

    return cols;
}

int find_mirror(std::vector<std::string> rows){
    int m_idx = -2;

    auto m_iter = std::adjacent_find(rows.begin(), rows.end());
    while((m_idx == -2) && (m_iter != rows.end())){
        int aa = m_iter - rows.begin() - 1, bb = m_iter - rows.begin() + 2;
        bool is_mirror = 1;
        while(is_mirror && ((aa >= 0) && (bb < rows.size()))){
            is_mirror *= (rows[aa] == rows[bb]);
            aa -= 1; bb += 1;
        }
        if(is_mirror){m_idx = m_iter - rows.begin();}
        m_iter = std::adjacent_find(std::next(m_iter), rows.end());
    }
    return  m_idx + 1;
}

int main(){
    std::ifstream input_file("./Inputs/input_13_test.txt");

    int sum = 0, mirror_idx;
    char type;
    std::vector<std::string> pattern_rows;
    for(std::string line; std::getline(input_file, line);){
        if(line.size() == 0){ // new pattern; run calculations, then re-init
            mirror_idx = find_mirror(pattern_rows);
            if(mirror_idx != -1){
                sum += 100*mirror_idx;
            }
            else{
                mirror_idx = find_mirror(transpose(pattern_rows));
                if(mirror_idx != -1){
                    sum += mirror_idx;
                }
                else{
                    std::cout << "No reflection found. \n";
                }
            }
            pattern_rows.clear();
        }
        else{
            pattern_rows.push_back(line);
        }
    }
    // do last pattern
    mirror_idx = find_mirror(pattern_rows);
    if(mirror_idx != -1){
        sum += 100*mirror_idx;
    }
    else{
        mirror_idx = find_mirror(transpose(pattern_rows));
        if(mirror_idx != -1){
            sum += mirror_idx;
        }
        else{
            std::cout << "No reflection found. \n";
        }
    }

std::cout << sum << "\n";

}