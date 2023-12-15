#include <iostream>
#include <fstream>


int main(){
    std::ifstream input_file("./Inputs/input_15.txt");

    int sum = 0, current_val = 0;
    char input = input_file.get();

    while(input_file){
        if(input == ','){
            //std::cout << "\n" << current_val << "\n";
            sum += current_val;
            current_val = 0;
        }
        else if(input >= 33 && input <= 126){
            //std::cout << input;
            current_val += input;
            current_val *= 17;
            current_val %= 256;
        }

        input = input_file.get();
    }
    //std::cout << "\n" << current_val << "\n";

    sum += current_val;

    std::cout << sum << "\n";

}