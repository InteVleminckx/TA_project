//
// Created by Dzhem Myumyun on 02/03/2021.
//

#ifndef SO1_TA_ENFA_H
#define SO1_TA_ENFA_H

#include <set>
#include <map>
#include <vector>
#include <fstream>

#include "State.h"
#include "json.hpp"
#include "DFA.h"

using namespace std;

class State_NFA;

class ENFA {
private:
    string q0;
    char eps;
    set<string> starting; //set van state-names van de startstaten.
    set<string> current_states; //Huidige set van staten waar de NFA zich bevindt
    map<string, State_NFA*> states; //Alle staten van de ENFA
    vector<char> alphabet;

public:

    /**
     * Default constructor.
     */
    ENFA();

    /**
     * Constructor die gebruikt wordt door de klasse RE na de omzetting van regex naar een eNFA om de ENFA te initialiseren.
     * @param s: de map met alle staten van de ENFA.
     * @param alfabet: de alfabet voor de automaat
     * @param start:de naam van de startstate
     * @param eps: de character die epsilon voorstelt
     */
    ENFA(map<string, State_NFA*> s, vector<char> alfabet, string start, char eps);


    /**
    * constructor van de ENFA
    * @param input: de pad naar de json bestand.
    */
    ENFA(const string& input);


    /**
    * Deze functie kijkt of een geven input-string geaccepteerd wordt.
    * @param input: input-string
    * @return: boolean
    */
    bool accepts(string input);


    /**
     * Deze methode zet een gegeven set van pointers naar Staat_NFA objecten om naar een set van de name van deze staten.
     * @param states: set van pointers
     * @return: set van namen
     */
    set<string> toStringSet(set<State_NFA*> states);


    /**
     * Deze functie kijkt na of een staat in een gegeven set van staten accepterend is.
     * @return: boolean
     */
    bool acceptingSet(set<string> current);


    /**
     * Deze functie reset de ENFA naar zijn startstaat.
     */
    void reset();


    /**
     * Deze functie zet een gegeven set van staten een string. Deze string wordt gebruikt als naam voor een DFA staat gemaakt
     * door de toDFA
     * @param states: set van State_NFA objecten.
     * @return: string
     */
    string setToString(set<State_NFA*> states);


    /**
     * Deze funcie zet de eNFA om in een DFA a.d.h.v. de toDFA.
     * @return: DFA gemaakt uit de toDFA.
     */
    DFA toDFA();

    /**
     * Deze funtie print alle informatie over de automaat.
     */
    void printStats();

    /**
     * Functie die een state aan de verzameling states toevoegt
     * @param state = state die we aan de ENFA willen toevoegen
     */
    void addToStates(State_NFA* state);

    /**
     * Functie die het symbool dat als epsilon gebruikt wordt teruggeeft
     * @return epsilon-symbol (type = const)
     */
    char getEpsilon() const;

    /**
     * Functie die een string toevoegd aan de set van strings die de starting states bevatten
     * @param name = naam (type = string)
     */
    void addToStartingStates(const string &name);

    /**
     * Functie die een string toevoegd aan de set van strings die de current states bevatten
     * @param name = naam (type = string)
     */
    void addToCurrentStates(const string &name);

    /**
     * Functie die alle accepting states van een bepaalde ENFA teruggeeft
     * @return vector<State_NFA*>
     */
    vector<State_NFA*> getAcceptingStates() const;

    /**
     * Getter voor de states map
     * @return map<string, State_NFA *>
     */
    const map<string, State_NFA *> &getStates() const;

    /**
     * Initialisseerd q0
     * @param startState: string, naam van de start state
     */
    void setStartState(string &startState);

    /**
     * Initialisseerd eps
     * @param epsilon: char, zegt welke char epsilon moet voorstellen
     */
    void setEpsilon(char epsilon);

};


#endif //SO1_TA_ENFA_H
