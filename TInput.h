//
// Created by mtara on 28.03.2020.
//

#ifndef GOLDBAG_TINPUT_H
#define GOLDBAG_TINPUT_H

#include <string>
#include <utility>
#include <fstream>
#include <exception>
#include <vector>
#include "TFraction.h"

using std::string;
using std::ifstream;
using std::vector;

class TInput {
private:
    ifstream stream;
public:
    TInput();
    explicit TInput(string fileName);
    vector<vector<TFraction>> GetData();
};

TInput::TInput() {
    stream.open("../input.txt");
    stream.exceptions(std::ifstream::failbit);
}

TInput::TInput(string fileName) {
    stream.open(fileName);
    stream.exceptions(std::ifstream::failbit);
}

vector<vector<TFraction>> TInput::GetData() {
    unsigned short int sizeCol;
    unsigned short int sizeRow;
    stream >> sizeCol;
    stream >> sizeRow;
    vector<vector<TFraction>> matrix(sizeCol);
    for (auto & row : matrix) {
        row.resize(sizeRow);
        for (auto & sell : row) {
            int tmp;
            stream >> tmp;
            //sell = tmp;
        }
    }
    return matrix;
}

#endif