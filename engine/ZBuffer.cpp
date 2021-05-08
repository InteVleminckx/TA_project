//
// Created by centu on 26/04/2021.
//

#include "ZBuffer.h"


ZBuffer::ZBuffer(const double width, const double height) {
    double posInf = numeric_limits<double>::infinity();

    for (int i = 0; i < width; i++) {
        vector<double> hoogte;
        for (int j = 0; j < height; j++) {
            hoogte.push_back(posInf);
        }
        pixelArray.push_back(hoogte);
    }
}
