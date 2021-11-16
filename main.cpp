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

    for (auto& row : parser) {
        for (auto& field : row) {
            cout << field << " | ";
        }
        cout << endl;
    }

}