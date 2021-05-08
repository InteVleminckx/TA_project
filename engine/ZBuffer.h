//
// Created by centu on 26/04/2021.
//

#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include <vector>
#include <limits>

using namespace std;


class ZBuffer: public vector<vector<double>> {
public:
    vector<vector<double>> pixelArray;

    ZBuffer(const double width, const double height);
};


#endif //ENGINE_ZBUFFER_H
