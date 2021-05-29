//
// Created by inte on 10.02.21.
//

#include "DFA_Inte.h"

using namespace std;
using namespace nlohmann;

DFA_Inte::DFA_Inte(const string& filename) {

    ifstream input(filename);
    json jsonFile;

    if (!input.is_open()) {
        cerr << "fout, file bestaat niet" << endl;
    }
    input >> jsonFile;

    //slagen alle states op in een global variable
    States = jsonFile["states"];

    //slagen het alfabet op in een global variable
    Alphabet = jsonFile["alphabet"];

    //slagen de transitions op in een global variable
    Transitions = jsonFile["transitions"];

    //slagen het type van automaat op in een global variable
    Type = jsonFile["type"];

    //plaatsen in de vector eerst een lege string (werking van de tabel)
    alfabet.emplace_back(" ");


    //sorteren van de states
    vector<string> stateNames; basic_json<> sortedStates;

    //voegen de namen toe aan een vector
    for (auto & State : States) { stateNames.push_back(State["name"]); }
    //sorteren deze vector
    sort(stateNames.begin(), stateNames.end());

    for (auto &stateName : stateNames){
        for (auto &state : States) {
            if (stateName == state["name"]) { sortedStates.push_back(state); }
        }
    }
    States = sortedStates;

    //plaatsen nadien de elementen uit de global variable in de vector
    for (auto & element : Alphabet){ alfabet.emplace_back(element); }

    //we lopen over de state namen en voegen deze telkens toe vooraan aan een vector
    for (auto & State : States) {

        //plaatsen de state vooraan in de tabel
        TransitionRow.emplace_back(State["name"]);

        //omdat het een DFA is heeft elke state evenveel transities dan de lengte van het alfabet
        //min 1 omdat we hierboven een extra lege string hebben toegevoegd aan het alfabet, om de tabel te laten kloppen
        //we reserever telkens een plek in de vector voor een transitie
        for (int i = 0; i < alfabet.size()-1; ++i) {TransitionRow.emplace_back("");}

        //voegen de rij toe aan de table en magen de rij leeg
        TrasitionTable.push_back(TransitionRow); TransitionRow.clear();

        //kijken of de state een start state is
        if(State["starting"]){ startState = State["name"];  pointer = startState;}

        //houdt bij of het een eindstate is of niet
        end[State["name"]] = State["accepting"];
    }

    //We hebben nu enkel nog maar een tabel met alle states in
    //nu moeten we de transitions nog toevoegen aan de tabel

    //we lopen over de lengte van het aan transities
    for (int i = 0; i < Transitions.size(); ++i) {

        // is gelijk aan de state waar we een transitie aan gaan toevoegen in de tabel
        string from = Transitions[i]["from"];

        //is de transitie die we gaan toevoegen
        string to = Transitions[i]["to"];

        //element uit het alfabet waardoor de transitie van from naar to gaat
        string inputAlfabet = Transitions[i]["input"];

        //nu we al deze variable hebben kunnen we onze transitie plaatsen in de tabel
        //we moeten eerst zoeken op welke rij de state zich bevindt

        //we lopen over de transitietabel
        for (int j = 0; j < TrasitionTable.size(); ++j) {
            //als de state gelijk is aan de state waar we de transitie aan toe willen voegen
            //We stellen de currentRow gelijk aan j
            if (TrasitionTable[j][0] == from){ currentRow = j; break; }
        }

        //We lopen nu over het alfabet om de colom te bepalen
        for (int j = 0; j < alfabet.size(); ++j) {
            //Wanneer we de input hebben gevonden in het alfabet
            //We stellen de currentColom gelijk aan j
            if (alfabet[j] == inputAlfabet){ currentColom = j; break;}
        }

        //We hebben nu de rij en de colom waar we de state aan moeten toevoegen
        TrasitionTable[currentRow][currentColom] = to;
    }

    //controllen: printen van de table
//    cout<<"       |";
//    for (int i = 1; i < alfabet.size(); ++i) {
//        cout<<"------|";
//
//    }
//    cout<<endl;
//
//    cout<<"       |";
//    for (auto & alfab : alfabet) {
//        if (alfab != " "){
//            cout<<"   "<<alfab<<"  |";
//        }
//
//    }
//    cout<<endl;
//
//    cout<<"|";
//    for (int i = 0; i < alfabet.size(); ++i) {
//        cout<<"------|";
//
//    }
//    cout<<endl;
//
//
//    for (int i = 0; i < TrasitionTable.size(); ++i) {
//        cout<<"|";
//
//        bool printed = false;
//
//
//        if(end.find(TrasitionTable[i][0])->second && TrasitionTable[i][0] == pointer){
//            cout<<"->* "<<TrasitionTable[i][0]<<"|";
//            printed = true;
//        }
//        else if(end.find(TrasitionTable[i][0])->second){
//            cout<<"  * "<<TrasitionTable[i][0]<<"|";
//            printed = true;
//        }
//
//
//        if(TrasitionTable[i][0] == pointer && !printed){
//            cout<<"->  "<<TrasitionTable[i][0]<<"|";
//        }
//
//        else if (!printed){
//            cout<<"    "<<TrasitionTable[i][0]<<"|";
//
//        }
//
//
//        for (int j = 1; j < TrasitionTable[i].size(); ++j) {
//            cout<<"  "<<TrasitionTable[i][j]<<"  |";
//        }
//        cout<<endl;
//        cout<<"|";
//        for (int i = 0; i < alfabet.size(); ++i) {
//            cout<<"------|";
//        }
//        cout<<endl;
//    }
    //einde controllen tabel

}

RE_Inte DFA_Inte::toRE() {

    RE_Inte re = RE_Inte();


    int aantalFinalStates = 0;

    //aantalfinalStates ophalen en voegen de final toe aan een vector
    for (auto & string : end) {
        if (string.second){aantalFinalStates+=1;finaleStates.push_back(string.first);}
    }



    for (int i = 0; i < aantalFinalStates; ++i) {
        re.makeRE(alfabet, TrasitionTable, finaleStates[i], startState);
    }

    return re;
}
