#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>

int find_matches(std::string card){
    int matches = 0;
    std::set<int> win_nums;

    int idx = card.find_first_not_of(' ', card.find(':') + 1), idx_next;

    while(idx < card.find('|') - 1){
        idx_next = card.find_first_of(' ', idx + 1);
        win_nums.insert(stoi(card.substr(idx, idx_next - idx)));
            idx = card.find_first_not_of(' ', idx_next);
    }

    idx = card.find_first_not_of(' ', card.find('|') + 1);

    while(idx < card.length()){
        idx_next = card.find_first_of(' ', idx + 1);
        if((win_nums.find(stoi(card.substr(idx, idx_next - idx))) != win_nums.end())){
            matches++;
        }

        idx = card.find_first_not_of(' ', idx_next);
    }
    return matches;
}

class Deck{
    public:
        Deck(std::unordered_map<int, std::tuple<std::vector<int>, int>> cards);

        int getTotalCards(int id);

    private:
        std::unordered_map<int, std::tuple<std::vector<int>, int>> cards;
};

Deck::Deck(std::unordered_map<int, std::tuple<std::vector<int>, int>> cards){
    Deck::cards = cards;
}

int Deck::getTotalCards(int id){
    int total_cards = std::get<1>(cards[id]);
    //std::cout << std::get<1>(cards[id]);
    if(total_cards == 0){
        for (int &cid : std::get<0>(cards[id])){
            total_cards += getTotalCards(cid);
        }
        total_cards += 1;
        std::get<1>(cards[id]) = total_cards;
    }
    return total_cards;
}

int main(){
    std::ifstream input_file("./Inputs/input_04.txt");
    std::unordered_map<int, std::tuple<std::vector<int>, int>> my_cards;
    int max_id;

    for(std::string line; std::getline(input_file, line);){
        std::vector<int> children; std::tuple<std::vector<int>, int> card_info; int total_cards;

        int id_s = line.find_first_not_of(' ', line.find_first_of(' ')), id_e = line.find_first_of(':');

        int id = stoi(line.substr(id_s, id_e - id_s));
        int matches = find_matches(line);

        if(matches == 0){
            total_cards = 1;
        }
        else{
            for(int ii = 0; ii < matches; ii++){
                children.push_back(id + ii + 1);
            }
            total_cards = 0;
        }
        card_info = std::make_tuple(children, total_cards);

        my_cards[id] = card_info;
        max_id = id;
    }
    Deck my_deck(my_cards);

    int sum = 0;

    for(int id = 0; id < max_id; id++){
        //std::cout << (id + 1) << ", total: " << my_deck.getTotalCards(id + 1) << '\n';
        sum += my_deck.getTotalCards(id + 1);
    }

    std::cout<<sum;

}