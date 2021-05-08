//
// Created by centu on 24/02/2021.
//

#ifndef ENGINE_L2DSYSTEEM_H
#define ENGINE_L2DSYSTEEM_H
#include "l_parser.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include "Lsysteem.h"
# define M_PI   3.14159265358979323846 // gevonden op https://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c

using namespace std;


class L2Dsysteem {
public:
    std::set<char> alfabet;
    map<char, bool> drawMap;
    map<char,vector<pair<string,double>>> replacements;
    double angleDegrees;
    double angle;
    string initiator;
    unsigned int nr_iterations;
    double startingAngle;

    // functie: parse
    // parset het L2D bestand en tekent de lijnen
    list<Line2D> parse(const string& filenaam, vector<double> color);

};


#endif //ENGINE_L2DSYSTEEM_H
