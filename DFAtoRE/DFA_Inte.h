//
// Created by inte on 10.02.21.
//

#ifndef TA_PROGRAMMEEROPDRACHT_01_DFA_H
#define TA_PROGRAMMEEROPDRACHT_01_DFA_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../TFA_Inte/json.hpp"
#include <map>
#include <iomanip>
#include <fstream>
#include "RE_Inte.h"

using namespace nlohmann;
using namespace std;

class DFA_Inte{


    vector<string> TransitionRow;
    vector<vector<string>> TrasitionTable;
    map<string, bool> end;
    string pointer;
    string startState;

    vector<string> finaleStates;

    vector<string> alfabet;

    basic_json<> States;
    basic_json<> Alphabet;
    basic_json<> Transitions;
    basic_json<> Type;

    int currentRow;
    int currentColom;

    bool inputGeldig = true;

public:

    DFA_Inte(const string& filename);

    RE_Inte toRE();

};


#endif //TA_PROGRAMMEEROPDRACHT_01_DFA_H
