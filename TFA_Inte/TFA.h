//
// Created by inte on 10.02.21.
//

#ifndef TA_PROGRAMMEEROPDRACHT_01_DFA_H
#define TA_PROGRAMMEEROPDRACHT_01_DFA_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "json.hpp"
#include <map>
#include <iomanip>
#include <fstream>
#include "TFA_State.h"
#include <chrono>
#include <algorithm>
using namespace nlohmann;
using namespace std;
using namespace std::chrono;

class TFA{
    vector<pair<string, string>> koppelVector;
    vector<vector<string>> vectorNewStates;


public:
    vector<TFA_State> states;
    vector<string> alfabet;
    basic_json<> Type;
    vector<vector<string>> table;
    vector<TFA_State> newStates;

    static bool sortStatesTransitions(vector<TFA_State> &statesVec);
    void addMarksFinalStatesBegin();
    void addMarksHorizontaleBegin(string &state);
    void addMarksVerticalBegin(string &state);
    bool isFinal(string &state);
    bool isNotSmallerOrEqual(string &state1, string &state2);
    bool isNotBiggerOrEqual(string &state1, string &state2);
    TFA copyDFA();
    void restoreDFA(TFA oldDFA);
    void createTable();
    bool minimizeTable(int iteratie);
    void searchInDFA(string &state1, string &state2);
    void makeVectorWithKoppels(vector<string> states1, vector<string> states2);
    bool addNewMarks(int iteratie);
    pair<int, int> findMarkPositon(string state1, string state2);
    void createNewStates();
    void vectorToStates();
    void stateExistinOtherState(vector<string> state1, vector<string> state2);
    TFA_State getState(const string& stateName);
    void existAlready(vector<string> &trans);

    void makeMiniDFA(TFA &newDFA);
    void transitionToNewState(string &transTo);
    bool deleteOldStates(string state);
    void setHaakjes();
    void clearDubbels();
    void checkDoubles(string &stateTo);

    TFA();
    static bool sortStates(vector<TFA_State> &statesVec);
    TFA(const string& filename);
    void print();
    void printTable();
    TFA minimize(long &time);

};


#endif //TA_PROGRAMMEEROPDRACHT_01_DFA_H
