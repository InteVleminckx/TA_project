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
#include "State.h"
using namespace nlohmann;
using namespace std;

class DFA{
    vector<pair<string, string>> koppelVector;
    vector<vector<string>> vectorNewStates;


public:
    vector<State> states;
    vector<string> alfabet;
    basic_json<> Type;
    vector<vector<string>> table;
    vector<State> newStates;

    static bool sortStatesTransitions(vector<State> &statesVec);
    void addMarksFinalStatesBegin();
    void addMarksHorizontaleBegin(string &state);
    void addMarksVerticalBegin(string &state);
    bool isFinal(string &state);
    bool isNotSmallerOrEqual(string &state1, string &state2);
    bool isNotBiggerOrEqual(string &state1, string &state2);
    DFA copyDFA();
    void restoreDFA(DFA oldDFA);
    void createTable();
    bool minimizeTable(int iteratie);
    void searchInDFA(string &state1, string &state2);
    void makeVectorWithKoppels(vector<string> states1, vector<string> states2);
    bool addNewMarks(int iteratie);
    pair<int, int> findMarkPositon(string state1, string state2);
    void createNewStates();
    void vectorToStates();
    void stateExistinOtherState(vector<string> state1, vector<string> state2);
    State getState(const string& stateName);
    void existAlready(vector<string> &trans);

    void makeMiniDFA(DFA &newDFA);
    void transitionToNewState(string &transTo);
    bool deleteOldStates(string state);
    void setHaakjes();
    void clearDubbels();
    void checkDoubles(string &stateTo);

    DFA();
    static bool sortStates(vector<State> &statesVec);
    DFA(const string& filename);
    void print();
    void printTable();
    DFA minimize();

};

inline bool operator==(DFA &oldDFA, DFA &miniDFA){

    DFA EQdfa;
    vector<State> oldStates = oldDFA.states;
    vector<State> miniStates = miniDFA.states;
    vector<State> allStates;

    allStates = oldStates;
    for (auto & miniState : miniStates) {allStates.push_back(miniState);}

    while (DFA::sortStates(allStates));

    EQdfa.states = allStates;
    EQdfa.alfabet = oldDFA.alfabet;
    EQdfa.Type = oldDFA.Type;

    DFA minEQDFA = EQdfa.minimize();
    EQdfa.printTable();

    string finaleState1;
    string finaleState2;

    for (auto & oldState : oldStates) {
        if (oldState.accepting){
            finaleState1 = oldState.name;
            break;
        }
    }
    for (auto & miniState : miniStates) {
        if (miniState.accepting){
            finaleState2 = miniState.name;
            break;
        }
    }

    vector<State> newStates = minEQDFA.newStates;
    bool isStart1 = false;
    bool isStart2 = false;
    for (int i = 0; i < newStates.size(); ++i) {
        isStart1 = false;
        isStart2 = false;
        for (int j = 0; j < newStates[i].name.size(); ++j) {
            if (newStates[i].name[j] == finaleState1[0]){
                isStart1 = true;
            }
            else if (newStates[i].name[j] == finaleState2[0]){
                isStart2 = true;
            }
            if (isStart1 && isStart2){break;}
        }
        if (isStart1 && isStart2){break;}
    }

    if (isStart1 && isStart2){return true;}


    return false;
}


#endif //TA_PROGRAMMEEROPDRACHT_01_DFA_H
