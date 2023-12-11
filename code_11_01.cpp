#include <iostream>
#include <fstream>
#include <vector>

int manhattan(std::vector<int> a, std::vector<int> b){
    if(a.size() != b.size()){
        return -1;
    }
    else{
        int sum = 0;
        for(int ii = 0; ii < a.size(); ii++){
            sum += abs(a[ii] - b[ii]);
        }
        return sum;
    }
}

int main(){
    std::ifstream input_file("./Inputs/input_11.txt");
    std::vector<std::vector<int>> galaxies;
    std::vector<int> empty_cols, empty_rows;

    std::string line;
    std::getline(input_file, line);

    std::vector<bool> is_empty_col(line.size(), 1);

    int rr = 0;
    do{
        bool empty = 1;
        for(int cc = 0; cc < line.size(); cc++){
            if(line[cc] == '#'){
                galaxies.push_back({rr, cc});
                empty = 0;
                is_empty_col[cc] = 0;
            }
        }
        if(empty){
            empty_rows.push_back(rr);
        }
        rr += 1;
    }
    while(std::getline(input_file, line));
    for(int ii = 0; ii < is_empty_col.size(); ii++){
        if(is_empty_col[ii]){
            empty_cols.push_back(ii);
        }
    }

    int sum = 0;

    for(int ii = 0; ii < galaxies.size() - 1; ii++){
        for(int jj = ii + 1; jj < galaxies.size(); jj++){
            std::vector<int> g0 = galaxies[ii], g1 = galaxies[jj];
            g0[0] += std::lower_bound(empty_rows.begin(), empty_rows.end(), g0[0]) - empty_rows.begin();
            g0[1] += std::lower_bound(empty_cols.begin(), empty_cols.end(), g0[1]) - empty_cols.begin();
            g1[0] += std::lower_bound(empty_rows.begin(), empty_rows.end(), g1[0]) - empty_rows.begin();
            g1[1] += std::lower_bound(empty_cols.begin(), empty_cols.end(), g1[1]) - empty_cols.begin();

            sum += manhattan(g0, g1);

        }
    }

    std::cout << sum << "\n";
}