//
// Created by inte on 11.03.21.
//

#ifndef TABLEFILLINGALGORITME_STATE_H
#define TABLEFILLINGALGORITME_STATE_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "json.hpp"
#include <map>
#include <iomanip>
#include <fstream>
using namespace nlohmann;
using namespace std;

class TFA_State{
public:
    string name;
    bool starting;
    bool accepting;
    vector<pair<string, string>> transitions;


    void addTransition(pair<string, string> &transtion);


};


#endif //TABLEFILLINGALGORITME_STATE_H
