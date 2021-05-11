//
// Created by Dzhem Myumyun on 10/02/2021.
//

#ifndef SO1_TA_DFA_H
#define SO1_TA_DFA_H

#include <string>
#include <iostream>
#include <vector>
#include "State.h"
#include <set>

using namespace std;

/**
 * Deze finctie neem de som van alle getallen gaande van 0 t.e.m. de gegeven getal i en geeft de som terug.
 */
int sommatie(int i);


class DFA {
private:
    string start_state; //string die gebruikt wordt bij het resetten van de DFA
    string current; //huidige staat
    map<string, State*> states; //alle staten van de DFA
    vector<char> alphabet;
    map<string ,map<string ,char>> TFA_table;

public:
    /**
    * Constructoe van de DFA object.
    * @param input: pad naar de in te lezen .json bestand.
    */
    DFA(const string& input);

    /**
     * Dit is de constructor voor het genereren van de productautomaat van 2 gegeven DFA's.
     * @param dfa1: automaat 1
     * @param dfa2: automaat 2
     * @param ddorsnede: boolean die aangeeft of het om de ddorsnede of de unie gaat.
     */
    DFA(DFA dfa1, DFA dfa2, bool doorsnede);

    /**
    * Dit is de constructor voor de DFA die wordt geconstrueert a.d.h.v. de toDFA.
    * @param sets: Alle staten die subsets van de eNFA, waruit deze DFA geconstrueert wordt, voorstellen.
    * @param a: alphabet
    */
    explicit DFA(map<string, State*> sets, vector<char> alphabet);  //constructor voor de toDFA

    /**
    * Deze functie kijkt na of de gegeven string wordt geaccepteert door de DFA.
    * @param input: input string
    * @return: boolean
    */
    bool accepts(string input);

    /**
    * Deze functie reset de DFA naar zijn start-staat na het inlezen van een input string.
    */
    void reset();

    /**
    * Deze functie maakt een nlholman::json object aan van de DFA en print deze vervolgens uit.
    */
    void print();

    /**
     * Geeft de alfabet van de automaat terug.
     */
    vector<char> getAlphabet();

    /**
     * Deze functie geeft weer of de staat in de automaat met de gegeven naam accepterend is.
     * @param state: naam van de staat
     * @return: boolean
     */
    bool isStateAccepting(string state);

    /**
     * deze functie geeft weer of de staat met de gegevn naam een startstaat is of niet.
     * @param state:naam van de staat
     * @return: boolean
     */
    bool isStateStarting(string state);

    /**
     * Deze functie geeft voor de staat met de gegeven naam in de automaat de staat waarnaar die toe gaat op de gegevn input.
     * @param name: naam van de staat
     * @param input: input character
     * @return: naam van de resulterende staat.
     */
    string stateGoesTo(string name, char input);

    /**
     * Deze functie geeft een vector terug met de namen van alle staten van de DFA.
     * @return: vector van strings
     */
    vector<string>  allStates();

    /**
     * Deze functie zal de DFA minimaliseren a.d.h.v. de table filling algoritme en zal daarmee een nieuwe geminimaliseerde DFA aanmaken.
     * @return
     */
    DFA minimize();

    /**
     * Deze functie voor de table-filling algoritme uit en maakt hierbij ook de tabel aan.
     * @param table: De tabel die wordt aangemaakt.
     * @param mapOfStates: de map van staten waarop de TFA wordt uitgevoerd
     */
    void TFA(map<string ,map<string ,char>>& table, map<string, State*>& mapOfStates);

    /**
     * Deze functie kijkt na of twee gegeven staten van de onderscheibaar zijn bij het inlezen van een van de mogelijke inputs.
     * @param A: staat 1
     * @param B: staat 2
     */
    void distinguisible(string A, string B, map<string, map<string ,char>>& table, map<string, State*>& states);

    /**
     * Deze funvtie drukt de tabel af na het uitvoeren van de table filling algoritme.
     * @param: table: is de tabel die moet worden afgedrukt
     * @param: statess: alle staten die in de table zitten.
     */
    void tablePrinter(map<string ,map<string ,char>>& table, map<string, State*>& statess);

    /**
     * Deze functie roept de tablePrinter functie op voor het printen van de TFA tabel voor een geminimaliseerde DFA.
     */
    void printTable();

    /**
     * Deze functie zal uit de gegeven vector van staten die equivalent zijn met andere staten een staat van maken, de
     * resultaat is dus een map van de nieuwe staten.
     * @param states: map die alle staten bevat die equivaent zijn met een of meerdere staten.
     * @param: new_states:  map die de naam van de nieuwe staat en de staten waaruit deze gemaakt zijn, dus uit staten
     *                      die equivalent zijn met elkaar.
     */
    void eqStatesToOne(map<string, vector<string>>& states, map<string, vector<string>>& new_states );

    /**
     * Dit is het overloaden van de == operator om deze dfa met een gegeven dfa met de TFA te vergelijken of ze equivalent zijn.
     * @param d: tegen te vergelijken DFA
     */
    bool operator ==(const DFA& d);

    /**
     * Getter voor de states
     * @return map<string, State *>
     */
    const map<string, State *> &getStates() const;

    /**
     * Setter voor het aanpassen van de states na het bekijken of er unreachable states zijn.
     * @param newStates : de nieuwe states.
     */
    void setStates(map<string, State *> &newStates);

    /**
     * Getter voor de startstate
     * @return startstate (type = string)
     */
    const string &getStartState() const;

    /**
     * Functie die alle accepting states van een DFA teruggeeft met een vector
     * @return vector<State*>
     */
    vector<State*> getAcceptingStates() const;

    /**
     * Deze functie veranderd de namen van de staten naar simpele namen.
     */
    void renameStates();
};


#endif //SO1_TA_DFA_H
