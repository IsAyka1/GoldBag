//
// Created by mtara on 28.03.2020.
//
#include <vector>
#include <iostream>
#include "TOutput.h"
#include "TFraction.h"
//#include "TSimplex.h"
#include "TInput.h"


using std::vector;

int main() {
    TInput input;
    auto a = input.GetData();
    TSimplex matrix(a);
    matrix.Algorithm();
    return 0;
}