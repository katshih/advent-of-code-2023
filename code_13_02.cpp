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

int find_mirror(std::vector<std::string> rows, int old_mirror){
    int m_idx = -2;

    auto m_iter = std::adjacent_find(rows.begin(), rows.end());
    while((m_idx < 0) && (m_iter != rows.end())){
        int aa = m_iter - rows.begin() - 1, bb = m_iter - rows.begin() + 2;
        bool is_mirror = 1;
        while(is_mirror && ((aa >= 0) && (bb < rows.size()))){
            is_mirror *= (rows[aa] == rows[bb]);
            aa -= 1; bb += 1;
        }
        if(is_mirror){
            m_idx = m_iter - rows.begin();
            if(m_idx == (old_mirror - 1)){
                m_idx = -2;
            }
        }
        m_iter = std::adjacent_find(std::next(m_iter), rows.end());
    }
    return  m_idx + 1;
}

int find_smudged_mirror(std::vector<std::string> rows){
    int old_row_mirror = find_mirror(rows);
    int old_col_mirror = find_mirror(transpose(rows));

    int mirror_idx = -1;
    for(int ii = 0; ii < rows.size(); ii++){
        for(int jj = 0; jj < rows[0].size(); jj++){
            rows[ii][jj] = (rows[ii][jj] == '.') ? '#' : '.'; // flip a bit

            mirror_idx = find_mirror(rows, old_row_mirror);
            if(mirror_idx >= 0){
                return 100*mirror_idx;
            }
            else{
                mirror_idx = find_mirror(transpose(rows), old_col_mirror);
                if(mirror_idx >= 0){
                    return mirror_idx;
                }
            }
            rows[ii][jj] = (rows[ii][jj] == '.') ? '#' : '.'; // flip bit back
        }
    }
    return mirror_idx;
}

int main(){
    std::ifstream input_file("./Inputs/input_13.txt");

    int sum = 0, mirror_val;
    char type;
    std::vector<std::string> pattern_rows;
    for(std::string line; std::getline(input_file, line);){
        if(line.size() == 0){ // new pattern; run calculations, then re-init
            // brute force!?
            mirror_val = find_smudged_mirror(pattern_rows);
            if(mirror_val != -1){
                sum += mirror_val;
            }
            else{
                std::cout << "No candidate found. \n";
            }
            pattern_rows.clear();
        }
        else{
            pattern_rows.push_back(line);
        }
    }
    mirror_val = find_smudged_mirror(pattern_rows);
    if(mirror_val != -1){
        sum += mirror_val;
    }
    else{
        std::cout << "No candidate found. \n";
    }

std::cout << sum << "\n";

}