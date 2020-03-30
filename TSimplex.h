//
// Created by mtara on 28.03.2020.
//

#ifndef GOLDBAG_TSIMPLEX_H
#define GOLDBAG_TSIMPLEX_H
#include <utility>
#include <vector>
#include "TFraction.h"
#include <string>
#include <iostream>

using std::vector;
using std::string;

class TSimplex {
    vector <vector<TFraction>> Matrix;
    int ColCount;
    int RowCount;
    vector<string> BasisArray;
public:
    TSimplex(vector <vector<TFraction>> matrix);
    TFraction GetResult();
    bool IsWhole();
    bool IsSimplex();
    TSimplex NewTable();
    TSimplex Algorithm();
private:
    TFraction FindElem(int& indexRow, int& indexCol);
    int FindStandartCol();
    int FindStandartRow(int indexCol);
    TSimplex AddColRow();
    TSimplex AddS(vector <TFraction> equation);
    vector<TFraction> AddEquation();
    TSimplex NewIterationTable();
    int FindTwiceCol(int indexRow);
    int FindTwiceRow();
};

TSimplex::TSimplex(vector <vector<TFraction>> matrix)
    : Matrix(std::move(matrix)) {
    RowCount = Matrix.size();
    ColCount = Matrix[0].size();
    for(int i = 0; i < RowCount - 1; ++i){
        BasisArray.push_back ("x" + std::to_string(ColCount - RowCount + i + 1));
    }
}

TSimplex TSimplex::Algorithm() {
    while(!IsWhole()) {
        NewIterationTable();
        vector <TFraction> equation = AddEquation();
        AddS(equation);
        GetResult();
    }
    return *this;
}

TFraction TSimplex::GetResult() {
    for(int i = 0; i < RowCount - 1; ++i){
        std::cout << BasisArray[i] << " = " << Matrix[i][ColCount - 1] << " ";
    }
    std::cout << "z = " << Matrix[RowCount - 1][ColCount - 1] << std::endl;
    return Matrix[RowCount - 1][ColCount - 1];
}

vector<TFraction> TSimplex::AddEquation() {
    vector <TFraction> equation(ColCount);
    int indexRow = 0;
    int count = 0;
    for(int i = 0; i < ColCount; ++i) {
        if(Matrix[indexRow][i].Denominator != 1)
            count++;
        if(i == ColCount - 1 && count == 0) {
            indexRow++;
            if(indexRow == RowCount) {
                if(IsWhole()) {
                    GetResult();
                    exit(0);
                }
                std::cout << "No whole result"; exit(-1);
            }
            i = 0;
        }
    }
    for(int i = 0; i < ColCount; i++) {
        if(Matrix[indexRow][i].Denominator == 1 || Matrix[indexRow][i] == 0){
            equation[i] = 0;
        }
        else{
            equation[i] = Matrix[indexRow][i];
        }
    }
    TFraction example(1);
    for( int i = 0; i < ColCount; ++i){
        if(equation[i] > example){
            equation[i] = equation[i] - equation[i].Numerator / equation[i].Denominator;
        }
        if(equation[i].Sign == 1 && equation[i] < example) {
            equation[i] = equation[i] + example;
        }
    }
    for(int i = 0; i < ColCount; ++i){
        if(equation[i].Numerator != 0) {
            equation[i].Sign = !equation[i].Sign;
        }
    }
    return equation;
}

TSimplex TSimplex::AddS(vector<TFraction> equation) {
    AddColRow();
    for(int i = 0; i < ColCount - 2; ++i){
        Matrix[RowCount - 2][i] = equation[i];
    }
    Matrix[RowCount - 2][ColCount - 1] = equation[ColCount - 2];
    Matrix[RowCount - 2][ColCount - 2] = 1;
    BasisArray.push_back("x" + std::to_string(ColCount - 1));
    return *this;
}

TSimplex TSimplex::AddColRow() {
    ColCount++;
    RowCount++;
    Matrix.resize(RowCount);
    for(int i = 0; i < RowCount; ++i){
        Matrix[i].resize(ColCount);
    }
    for(int i = 0; i < ColCount; ++i){
        TFraction val = Matrix[RowCount - 2][i];
        Matrix[RowCount - 2][i] = Matrix[RowCount - 1][i];
        Matrix[RowCount - 1][i] = val;
    }
    for(int i = 0; i < RowCount; ++i){
        TFraction val = Matrix[i][ColCount - 2];
        Matrix[i][ColCount - 2] = Matrix[i][ColCount - 1];
        Matrix[i][ColCount - 1] = val;
    }
    return *this;
}

TSimplex TSimplex::NewIterationTable() {
    while(bool s = IsSimplex()) {
        NewTable();
    }
    return *this;
}

bool TSimplex::IsWhole() {
    for(int i = 0; i < RowCount; ++i) {
        if(Matrix[i][ColCount - 1].Denominator != 1)
            return false;
    }
    if (Matrix[RowCount - 1][ColCount  - 1] == 0)
        return false;
    return true;
}

bool TSimplex::IsSimplex() {
    bool is = false;
    for(int i = 0; i < ColCount; ++i){
        if(Matrix[RowCount - 1][i].Sign == 1) {
            is = true;
        }
    }
    for(int i = 0; i < RowCount; ++i) {
        if(Matrix[i][ColCount - 1].Sign == 1) {
            is = true;
        }
    }
    return is;
}

TSimplex TSimplex::NewTable() {
    if(ColCount == 8)
    {
        bool f = true;
    }
    vector<vector<TFraction>> newMatrix;
    newMatrix.resize(RowCount);
    for(int i = 0; i < RowCount; ++i) {
        newMatrix[i].resize(ColCount);
    }
    int indexCol = 0, indexRow = 0;
    TFraction elem = FindElem(indexRow, indexCol);
    if(elem.Denominator == -1) {
        return *this;
    }
    for (int i = 0; i < RowCount; ++i) {
        for (int j = 0; j < ColCount; ++j) {
            if (i == indexRow) {
                newMatrix[i][j] = Matrix[i][j] / elem;
                continue;
            }
            if (j == indexCol && i != indexRow) {
                newMatrix[i][j] = 0;
                continue;
            }
            newMatrix[i][j] = Matrix[i][j] - (Matrix[indexRow][j] * Matrix[i][indexCol] / elem);
        }
    }
    Matrix = newMatrix;
    return *this;
}

TFraction TSimplex::FindElem(int& indexRow, int& indexCol) {
    bool twice = false;
    for(int i = 0; i < RowCount; ++i) {
        bool f = Matrix[i][ColCount - 1].Sign;
        if(f == true) {
            twice = true;
            break;
        }
    }
    if(twice){
        indexRow = FindTwiceRow();
        indexCol = FindTwiceCol(indexRow);
    } else {
        indexCol = FindStandartCol();
        indexRow = FindStandartRow(indexCol);
    }
    if(indexCol == -1 || indexRow == -1) {
        std::cout << "error noone negative in simplex table";
        TFraction flag(0, -1);
        return flag;
    }
    //меняем базисную пременную
    BasisArray[indexRow] = "x" +  std::to_string(indexCol + 1);
    return Matrix[indexRow][indexCol];
}

int TSimplex::FindStandartCol() {
    int indexCol = -1;
    TFraction min(1000);
    for(int i = 0; i < ColCount; ++i){
            if(Matrix[RowCount - 1][i].Sign == 1) {
                if(Matrix[RowCount - 1][i] < min) {
                    min = Matrix[RowCount - 1][i];
                    indexCol = i;
                }
        }
    }
    return indexCol;
}

int TSimplex::FindStandartRow(int indexCol) {
    int indexRow = -1;
    TFraction min(1000);
    for(int i = 0; i < RowCount - 1; ++i){
        if( Matrix[i][indexCol].Numerator != 0 &&  Matrix[i][indexCol].Sign == false) {
            TFraction val = Matrix[i][ColCount - 1] / Matrix[i][indexCol];
            if (val < min) {
                min = val;
                indexRow = i;
            }
        }
    }
    return indexRow;
}

int TSimplex::FindTwiceCol(int indexRow) {
    TFraction min(1000);
    bool decision = false;
    int indexCol= 0;
    for(int i = 0; i < ColCount; ++i){
        if(Matrix[indexRow][i].Sign != 0) {
            decision = true;
            TFraction val = Matrix[RowCount - 1][i] / Matrix[indexRow][i];
            if(val < min) {
                min = val;
                indexCol = i;
            }
            continue;
        }
    }
    if(!decision){
        std::cout << "Таблица не имеет решения" << std::endl;
        exit(0);
    }
    return indexCol;
}

int TSimplex::FindTwiceRow() {
    double max = -1; //мах по модулю тк и так отрицательный
    int indexRow = 0;
    for(int i = 0; i < RowCount; ++i) {
        if (Matrix[i][ColCount - 1].Sign == 1) {
            double fraction = (double) Matrix[i][ColCount - 1].Numerator / Matrix[i][ColCount - 1].Denominator;
            if (fraction > max) {
                max = fraction;
                indexRow = i;
            }
        }
    }
    return indexRow;
}

#endif //GOLDBAG_TSIMPLEX_H
