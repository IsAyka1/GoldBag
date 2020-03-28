//
// Created by mtara on 28.03.2020.
//

#ifndef GOLDBAG_TOUTPUT_H
#define GOLDBAG_TOUTPUT_H

#include <vector>
#include <string>
#include <fstream>
#include "TFraction.h"
#include "TSimplex.h"


using std::ofstream;
using std::vector;
using std::string;

class TOutput {
public:
    explicit TOutput(TSimplex & simplex, string fileName="../output.txt");
};

TOutput::TOutput(TSimplex & simplex, string fileName) {
    ofstream stream(fileName, std::ios_base::trunc);
    stream.exceptions(std::ofstream::failbit);
//    for (int i = 1; i < simplex.GetMatrix().Size(); ++i) {
//
//    }
}

#endif //GOLDBAG_TOUTPUT_H
