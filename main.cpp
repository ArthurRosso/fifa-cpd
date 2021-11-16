#include <iostream>
#include <string>
#include <vector>
#include "./csv-parser/parser.hpp"

using namespace aria::csv;
using namespace std;

struct PlayerPosition{
    int id;
    int id_player;
    string position;
};

struct Player{
    int id;
    string name;
    float rating;
    int count;
};


int main (){
    ifstream f("simple.csv");
    CsvParser parser(f);

    // TODO: fazer pular a primeira linha
    for (auto& row : parser) {
        cout << "Player id: " << row.at(0) << endl;
        cout << "Player name: " << row.at(1) << endl;
    }

}