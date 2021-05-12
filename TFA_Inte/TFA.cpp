//
// Created by inte on 10.02.21.
//

#include "TFA.h"

using namespace std;
using namespace nlohmann;


TFA::TFA() {}

TFA::TFA(const string& filename) {

    ifstream input(filename);
    json jsonFile;

    if (!input.is_open()) {
        cerr << "fout, file bestaat niet" << endl;
    }
    input >> jsonFile;

    basic_json<> States;
    basic_json<> Alphabet;
    basic_json<> Transitions;

    //slagen alle states op in een global variable
    States = jsonFile["states"];

    //slagen het alfabet op in een global variable
    Alphabet = jsonFile["alphabet"];

    //slagen de transitions op in een global variable
    Transitions = jsonFile["transitions"];

    //slagen het type van automaat op in een global variable
    Type = jsonFile["type"];

    //maken een state aan
    for (auto state : States) {
        TFA_State newState;
        newState.name = state["name"];
        newState.starting = state["starting"];
        newState.accepting = state["accepting"];
        states.push_back(newState);
    }

    //sorteren van de states
    //zolang er een verandering is gedaan is de vector nog niet gesorteerd
    //(bubbelsort)
    while (sortStates(states));

    //we voegen de transities toe aan de states
    for (auto & Transition : Transitions) {
        for (auto & state : states) {
            //We hebben de state gevonden die bij de transitie hoort
            if (Transition["from"] == state.name){
                pair<string, string> trans = make_pair(Transition["to"],Transition["input"]);
                state.addTransition(trans);
            }
        }
    }

    //sorteren van de states zijn transities aan de hand van alfabet
    //zolang er een verandering is gedaan is de vector nog niet gesorteerd
    //(bubbelsort)
    while (sortStatesTransitions(states));

    //toevoegen van het alfabet
    for (auto & charac : Alphabet) {alfabet.push_back(charac);}
    //sorteren het voor de zekerheid
    sort(alfabet.begin(), alfabet.end());

}

void TFA::print() {

    json  j;

    //toevoegen van het type
    j["type"] = Type;

    //toevoegen van het alfabet
    for (auto & charac : alfabet) { j["alphabet"].push_back(charac);}

    //toevoegen van de states en transities
    for (auto &state : states) {
        basic_json<> mapState;
        basic_json<> mapTrans;

        mapState["name"] = state.name;
        mapState["starting"] = state.starting;
        mapState["accepting"] = state.accepting;
        j["states"].push_back(mapState);

        for (auto &trans : state.transitions) {
            mapTrans["from"] = state.name;
            mapTrans["to"] = trans.first;
            mapTrans["input"] = trans.second;
            j["transitions"].push_back(mapTrans);
        }
    }

    cout<<setw(4)<<j<<endl;
}

bool TFA::sortStates(vector<TFA_State> &statesVec) {

    bool swapped = false;

    //lopen over de vector
    for (int i = 0;i < statesVec.size()-1; ++i) {

        string state1 = statesVec[i].name;
        string state2 = statesVec[i+1].name;

        if (state1[0] == '{'){
            state1 = state1[1];
        }
        if (state2[0] == '{'){
            state2 = state2[1];
        }

        //als de rechter in de vector kleiner is als de linkse moeten deze van
        //plaats wisselen
        if (state1 > state2){
            TFA_State temp = statesVec[i+1];
            statesVec[i+1] = statesVec[i];
            statesVec[i] = temp;
            swapped = true;
        }
    }
    return swapped;
}

bool TFA::sortStatesTransitions(vector<TFA_State> &statesVec) {

    bool swapped = false;
    for (auto & state : statesVec) {
        for (int j = 0; j < state.transitions.size()-1; ++j) {

            if (state.transitions[j].second > state.transitions[j+1].second){
                pair<string, string> temp = state.transitions[j+1];
                state.transitions[j+1] = state.transitions[j];
                state.transitions[j] = temp;
                swapped = true;
            }
        }
    }
    return swapped;
}

TFA TFA::minimize(long &time) {

    auto start = high_resolution_clock::now();

    createTable();
    addMarksFinalStatesBegin();
    TFA oldDFA = copyDFA();
    int iteratie = 0;
    while (minimizeTable(iteratie)){iteratie++;}
    createNewStates();
    TFA newDFA = copyDFA();
    makeMiniDFA(newDFA);
    restoreDFA(oldDFA);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    time = duration.count();

    return newDFA;
}

void TFA::createTable() {
    //We maken eerst een table aan
    for (int i = 0; i < states.size(); ++i) {
        vector<string> row;
        for (int j = 0; j < states.size(); ++j) {

            //voegen de states langs de zijkant toe
            if (i < states.size()-1 && j == 0){
                row.push_back(states[i+1].name);
            }
            //voegen de states langs onder toe
            else if (i == states.size()-1 && j > 0){
                row.push_back(states[j-1].name);
            }
            //vullen de legenplaatsen op
            else{
                row.emplace_back("");
            }
        }
        table.push_back(row);
    }

    addMarksFinalStatesBegin();

}

void TFA::printTable() {


    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j){
            if (i == table.size()-1){cout << table[i][j][0] << "\t";}
            else if (table[i][0] <= table[table.size()-1][j]){break;}
            else if(table[i][j].empty()) {cout << "-" << "\t";}
            else{cout << table[i][j][0] << "\t";}
        }
        cout << endl;
    }
}

void TFA::addMarksFinalStatesBegin() {

    for (auto & state : states) {

        //zetten een kruisje als het een accepting state is
        if (state.accepting){
            addMarksHorizontaleBegin(state.name);
            addMarksVerticalBegin(state.name);
        }
    }
}

void TFA::addMarksHorizontaleBegin(string &state) {

    int rowNumber;
    for (int i = 0; i < table.size(); ++i) {
        //hebben de row van de state gevonden
        if (table[i][0] == state){
            rowNumber = i;
            break;
        }
    }

    for (int i = 1; i < table.size(); ++i) {
        //als het op de onderste rij geen final is kunnen we
        //op de huidige rij een kruisje zetten
        if (!isFinal(table[table.size()-1][i]) && isNotBiggerOrEqual(table[table.size()-1][i], state)){
            table[rowNumber][i] = "X0";
        }
    }
}

void TFA::addMarksVerticalBegin(string &state) {

    int colomNumber;
    for (int i = 1; i < table.size(); ++i) {
        //hebben de row van de state gevonden
        if (table[table.size()-1][i] == state){
            colomNumber = i;
            break;
        }
    }

    for (int i = 0; i < table.size()-1; ++i) {
        //als het in de linkse kolom geen finalstate is
        //dan kunnen we een kruisje zetten
        if (!isFinal(table[i][0]) && isNotSmallerOrEqual(table[i][0], state)){
            table[i][colomNumber] = "X0";
        }
    }
}

bool TFA::isFinal(string &state) {
    for (auto & curState : states) {
        if (curState.name == state){
            return curState.accepting;
        }
    }
    return false;
}

bool TFA::isNotSmallerOrEqual(string &state1, string &state2) {

    int posState1;
    int posState2;

    for (int i = 0; i < states.size(); ++i) {
        if (states[i].name == state1){
            posState1 = i;
        }
        if (states[i].name == state2){
            posState2 = i;
        }
    }
    if (posState1 <= posState2){
        return false;
    }
    return true;
}

bool TFA::isNotBiggerOrEqual(string &state1, string &state2) {
    int posState1;
    int posState2;

    for (int i = 0; i < states.size(); ++i) {

        if (states[i].name == state1){
            posState1 = i;
        }
        if (states[i].name == state2){
            posState2 = i;
        }
    }
    if (posState1 >= posState2){
        return false;
    }
    return true;

}

TFA TFA::copyDFA() {
    TFA oldDFA = TFA();
    oldDFA.states = this->states;
    oldDFA.alfabet = this->alfabet;
    oldDFA.Type = this->Type;
    oldDFA.table = this->table;
    oldDFA.koppelVector = this->koppelVector;
    oldDFA.vectorNewStates = this->vectorNewStates;
    oldDFA.newStates = this->newStates;
    return oldDFA;
}

bool TFA::minimizeTable(int iteratie) {



    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            string state1 = table[i][0];
            if (table[i][j] == "X" + to_string(iteratie)){
                string state2 = table[table.size()-1][j];
                searchInDFA(state1, state2);
            }
        }
    }
    return addNewMarks(iteratie+1);
}

void TFA::searchInDFA(string &state1, string &state2) {

    vector<vector<string>> state1Vector;
    vector<vector<string>> state2Vector;
    vector<pair<string, string>> canBePlacesInTable;

    for (int i = 0; i < states[0].transitions.size(); ++i) {

        vector<string> newTransState1;
        vector<string> newTransState2;

        for (int j = 0; j < states.size(); ++j) {
            if (states[j].transitions[i].first == state1){
                newTransState1.push_back(states[j].name);
            }
            else{
                newTransState1.emplace_back("");
            }
            if (states[j].transitions[i].first == state2){
                newTransState2.push_back(states[j].name);
            }
            else{
                newTransState2.emplace_back("");
            }
        }

        state1Vector.push_back(newTransState1);
        state2Vector.push_back(newTransState2);

    }



    for (int i = 0; i < state1Vector.size(); ++i) {
        makeVectorWithKoppels(state1Vector[i], state2Vector[i]);
    }
}

void TFA::makeVectorWithKoppels(vector<string> states1, vector<string> states2) {

    for (int i = 0; i < states1.size(); ++i) {
        for (int j = 0; j < states2.size(); ++j) {
            if (!states1[i].empty() && !states2[j].empty()){
                koppelVector.emplace_back(states1[i], states2[j]);
            }
        }
    }
}

bool TFA::addNewMarks(int iteratie) {

    bool returnBool = false;

    for (int i = 0; i < koppelVector.size(); ++i) {
        string state1;
        string state2;

        if (koppelVector[i].first > koppelVector[i].second){
            state1 = koppelVector[i].first;
            state2 = koppelVector[i].second;
        }
        else{
            state2 = koppelVector[i].first;
            state1 = koppelVector[i].second;
        }

        pair<int, int> positionMark = findMarkPositon(state1, state2);

        if (table[positionMark.first][positionMark.second].empty()){

            table[positionMark.first][positionMark.second] = "X" + to_string(iteratie);
            returnBool = true;
        }
    }

    koppelVector.clear();
    return returnBool;
}

pair<int, int> TFA::findMarkPositon(string state1, string state2) {
    pair<int, int> postionMark;
    bool found = false;
    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            if (table[i][0] == state1 && table[table.size()-1][j] == state2){
                postionMark.first = i;
                postionMark.second=j;
                found = true;
                break;
            }
        }
        if (found){break;}
    }
    return postionMark;
}

void TFA::createNewStates() {

    for (int i = 1; i < table[0].size(); ++i) {

        vector<string> newStateName;
        string stateBeneden;

        for (int j = 0; j < table.size()-1; ++j) {

            if (table[j][i].empty() && table[j][0] > table[table.size()-1][i]){
                newStateName.push_back(table[j][0]);
                stateBeneden = table[table.size()-1][i];
            }
        }

        if (!newStateName.empty()){
            newStateName.push_back(stateBeneden);
            sort(newStateName.begin(), newStateName.end());
            vectorNewStates.push_back(newStateName);
        }
    }
    vectorToStates();

    for (int i = 0; i < vectorNewStates.size(); ++i) {
        string stateName = "{";
        TFA_State newState;
        bool accepting = false;
        bool starting = false;
        vector<vector<pair<string, string>>> trans;

        for (int j = 0; j < vectorNewStates[i].size(); ++j) {
            if (j == 0){stateName += vectorNewStates[i][j];}
            else{stateName += ", " + vectorNewStates[i][j];}

            TFA_State curState = getState(vectorNewStates[i][j]);
            if (!accepting && curState.accepting){
                accepting = true;
            }
            if(!starting && curState.starting){
                starting = true;
            }
            trans.push_back(curState.transitions);

        }
        stateName += "}";
        newState.name = stateName;
        newState.accepting = accepting;
        newState.starting = starting;

        vector<vector<string>> transi;
        for (int t = 0; t < alfabet.size(); ++t) {
            vector<string> newTrans;
            for (int k = 0; k < trans.size(); ++k) {
                newTrans.push_back(trans[k][t].first);
            }
            sort(newTrans.begin(), newTrans.end());

            if (newTrans.size() > 1){
                existAlready(newTrans);
            }

            transi.push_back(newTrans);
        }


        for (int j = 0; j < transi.size(); ++j) {
            string stateName = "{";
            for (int k = 0; k < transi[j].size(); ++k) {
                if (k == 0){stateName += transi[j][k];}
                else{stateName += ", " + transi[j][k];}
            }
            stateName += "}";
            newState.transitions.emplace_back(stateName, alfabet[j]);
        }
        newStates.push_back(newState);
    }
}

void TFA::vectorToStates() {

//    bool makedChange = true;

//    while (makedChange){
    if (vectorNewStates.size() > 0)
    {
        for (int i = 0; i < vectorNewStates.size()-1; ++i) {
            for (int j = 0; j < vectorNewStates.size(); ++j) {
                stateExistinOtherState(vectorNewStates[i], vectorNewStates[j]);
                if (vectorNewStates.size() == 1){break;}
            }
            if (vectorNewStates.size() == 1){break;}
        }
    }
//
//        //nog weg doen
//        makedChange = true;
//    }



}

void TFA::stateExistinOtherState(vector<string> state1, vector<string> state2) {

    bool vectorExistinOther = false;

    if (state1.size() > state2.size()){

        for (int i = 0; i < state2.size(); ++i) {

            if (count(state1.begin(), state1.end(), state2[i])){
                vectorExistinOther = true;
            }
            else{
                vectorExistinOther = false;
                break;
            }
        }
    }
    else if (state1.size() < state2.size()){
        for (int i = 0; i < state1.size(); ++i) {
            if (count(state2.begin(), state2.end(), state1[i])){
                vectorExistinOther = true;
            }
            else{
                vectorExistinOther = false;
                break;
            }
        }
    }

    if (vectorExistinOther && state1.size() > state2.size()){
        for (int i = 0; i < vectorNewStates.size(); ++i) {
            if (vectorNewStates[i] == state2){
                vectorNewStates.erase(vectorNewStates.begin()+i);
                break;
            }
        }
    }

    else if (vectorExistinOther && state1.size() < state2.size()){
        for (int i = 0; i < vectorNewStates.size(); ++i) {
            if (vectorNewStates[i] == state1){
                vectorNewStates.erase(vectorNewStates.begin()+i);
                break;
            }
        }
    }

}

TFA_State TFA::getState(const string& stateName) {
    for (int i = 0; i < states.size(); ++i) {
        if (stateName == states[i].name){
            return states[i];
        }
    }
    TFA_State a;
    return a;
}

void TFA::existAlready(vector<string> &trans) {

    bool exist = false;
    for (int j = 0; j < vectorNewStates.size(); ++j) {
        for (int i = 0; i < trans.size(); ++i) {
            if (count(vectorNewStates[j].begin(), vectorNewStates[j].end(), trans[i])){
                exist = true;
            }
            else{
                exist = false;
                break;
            }
        }

        if (exist){
            trans = vectorNewStates[j];
            break;
        }
    }
}

void TFA::restoreDFA(TFA oldDFA) {

    this->states = oldDFA.states;
    this->alfabet = oldDFA.alfabet;
    this->Type = oldDFA.Type;
    this->koppelVector = oldDFA.koppelVector;
    this->vectorNewStates = oldDFA.vectorNewStates;
    this->newStates = oldDFA.newStates;

}

void TFA::makeMiniDFA(TFA &newDFA) {

    for (int i = 0; i < states.size(); ++i) {
        for (int j = 0; j < states[i].transitions.size(); ++j) {
            transitionToNewState(states[i].transitions[j].first);
        }
    }

    vector<int> posStateToEliminate;

    for (int i = 0; i < states.size(); ++i) {
        if(deleteOldStates(states[i].name)){
            posStateToEliminate.push_back(i);
        }
    }

    reverse(posStateToEliminate.begin(), posStateToEliminate.end());

    for (auto i : posStateToEliminate) {
        states.erase(states.begin()+i);
    }


    for (int i = 0; i < newStates.size(); ++i) {
        states.push_back(newStates[i]);
    }

    while (sortStates(states));

    clearDubbels();
    setHaakjes();

    newDFA = copyDFA();

}

void TFA::transitionToNewState(string &transTo) {
    bool found = false;

    for (int i = 0; i < newStates.size(); ++i) {
        string state = newStates[i].name;
        for (int j = 0; j < state.size(); ++j) {
            char trans = transTo[0];

            if ( trans == state[j]){
                transTo = newStates[i].name;
                found = true;
                break;
            }
        }
        if (found){break;}
    }
}

bool TFA::deleteOldStates(string state) {

    for (int i = 0; i < newStates.size(); ++i) {
        char charState = state[0];
        string stateNew = newStates[i].name;
        for (int j = 0; j < stateNew.size(); ++j) {

            if (stateNew[j] == charState){
                return true;

            }
        }
    }

    return false;
}

void TFA::setHaakjes() {

    for (int i = 0; i < states.size(); ++i) {

        if (states[i].name[0] != '{'){
            states[i].name = "{" + states[i].name + "}";
        }

        for (int j = 0; j < states[i].transitions.size(); ++j) {
            if (states[i].transitions[j].first[0] != '{'){
                states[i].transitions[j].first = "{" + states[i].transitions[j].first + "}";
            }
        }
    }
}

void TFA::clearDubbels() {

    for (int i = 0; i < states.size(); ++i) {
        for (int j = 0; j < states[i].transitions.size(); ++j) {
                checkDoubles(states[i].transitions[j].first);
        }

    }
}

void TFA::checkDoubles(string &stateTo) {

    vector<char> eachState;
    if (stateTo.size() > 1){
        for (int i = 0; i < stateTo.size(); ++i) {
            if (stateTo[i] != '{' && stateTo[i] != '}' && stateTo[i] != ',' && stateTo[i] != ' '){
                eachState.push_back(stateTo[i]);
            }
        }

        sort(eachState.begin(), eachState.end());

        vector<char> newStateVec;

        for (int i = 0; i < eachState.size(); ++i) {
            if (!count(newStateVec.begin(), newStateVec.end(), eachState[i])){
                newStateVec.push_back(eachState[i]);
            }
        }

        string newState = "{";

        for (int i = 0; i < newStateVec.size(); ++i) {

            if (i == 0){
                newState += newStateVec[i];
            }
            else{
                newState += ", " ;
                newState += newStateVec[i];
            }
        }

        newState += '}';
        stateTo = newState;
    }

}
