//
// Created by intev on 3/03/2021.
//

#ifndef TA_PO_DFA_RE_RE_H
#define TA_PO_DFA_RE_RE_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "json.hpp"
#include <map>
#include <iomanip>
#include <fstream>

using namespace std;

class RE_Inte {
public:

    string REGEX;
    vector<vector<string>> complTransTable;

    vector<string> allStates;
    vector<string> statesToElemin;
    vector<string> alfabet;
    vector<vector<string>> transTable;
    string finaleState;
    string startState;
    vector<string> allAddedKleenes;
    string R;
    string S;
    string U;
    string T;
    string dfaToRegex;

    //  from                 to      with
    map<string, vector<pair<string, string>>> transitions;

    void makeRE(const vector<string>& xalfabet,
                const vector<vector<string>>& xtransTable,
                const string& xfinaleState,
                const string& xstartState);

    void resetAllVar();

    string createREGEX();
    string getStateToEliminate();

    void createMap(string &state);
//    void createNewTable(vector<string> &transRow, int &colom);
    void eleminateState(string &stateToEliminate);

    void addTransitons(const string &from, string &to, string &stateToEliminate);

//    void createKleene(const string &from, string &to);

    void removeEliminatedStateOutMap(string & stateToEliminate);

    pair<bool, int> pairExistAlready(string &from, string &state);

    bool transHasOpperator(string &trans);

    bool uHasHaakjes(string &U);

    void mapToRegex();

    void twoToRE();

    void print();

    void startIsFinal();

};


#endif //TA_PO_DFA_RE_RE_H
