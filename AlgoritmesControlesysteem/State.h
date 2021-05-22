//
// Created by Dzhem Myumyun on 19/02/2021.
//

#ifndef SO1_TA_STATE_H
#define SO1_TA_STATE_H

#include <string>
#include <map>
#include <set>
#include <istream>

#include "json.hpp"

using namespace std;

class State {
private:
    bool starting;
    bool state; //huidige staat
    string name;
    bool accepting;
    map<char, State*> t_to; //de transities naar andere staten

public:
    /**
     *Zet de staat van deze state naar true of false.
     */
    void setState(bool s);

    /**
     * Constructor van een staat
     * @param start: boolean die aangeeft of de staat een startstaat is.
     * @param n: de naam van de staat
     * @param acc: boolean die aangeeft of de staat accepterend is.
     */
    State(bool starting, string n, bool acc);   //constructor

    /**
     * Geeft de naam van de state terug.
     * @return: name
     */
    string getName() const;

    /**
     * Voegt een transitie toe aan deze staat.
     * @param input: de input character waarop de transitie gebeurt.
     * @param to: De staat waar men naar gaat op de input.
     */
    void addTransition(char input, State* tgt); //voegt een transitie toe aan de state.

    /**
     * voert de transitie uit en geeft de naam terug van de nieuwe staat..
     * @return: string
     */
    string transition(char i);  //voert de transitie uit.

    /**
     * geeft terug of de staat accepting is.
     * @return: boolean
     */
    bool is_accept() const;

    /**
     * Deze functie maakt een nlohmann::json object aan die de state zelf voorsteld.
     * @return: geeft de json object terug.
     */
    nlohmann::json to_map();

    /**
     * Deze vector geeft een vector<map<string, string>> object terug die elke transitie van de de staat in map-vorm bevat.
     * @return: vector met de transities in map-vorm
     */
    vector<map<string, string>> transitionsToMap();

    /**
     * Geeft terug of de staat eer start-staat is.
     */
    bool isStarting();

    /**
     * Deze functie geeft een set van strings terug. Deze string zijn de string waarbij deze staat geen transitie op heeft
     * op de symbolen uit de gegeven alfabet.
     * @param alphabet: de alfabet waaruit er controleert wordt op transities per character.
     * @return: set van strings waarbij geen transitie gebeurt.
     */
    set<char> no_transitionChars(vector<char>& alphabet);

    /**
     * Deze functie geeft de naam van de staat waarnaar deze staat gaat op de gegeven input character.
     * @param c: input
     * @return: naam
     */
    string goesTo(char c);

    /**
     * Deze functie veranderd de naam van de staat naar de gegeven string.
     */
    void changeName(string n);

    /**
     * Getter voor de transities van een state
     * @return map<char, State *>
     */
    const map<char, State *> &getTTo() const;

    /**
     * Deze functie verandert de naam van de staat naar de gegeven string
     * @param Name: nieuwe naam van de staat.
     */
    void setName(string Name);

    /**
     * Functie die de bool "state" teruggeeft
     * @return boolean
     */
    bool isState() const;

};

/**
 * Speciale klasse voor de eNFA staten.
 */
class State_NFA{
private:
    bool starting;
    bool state; //huidige staat
    string name;
    char eps;
    bool accepting;
    map<char, set<State_NFA*>> t_to;

public:
    /**
     * zet de staat van de ENFA staat naar de gegeven boolean.
     * @param s: boolean.
     */
    void setState(bool s);

    /**
     * Constructor van de ENFA-staat
     * @param s: boolean die aangeeft of de staat een startstaat is.
     * @param n: de naam van de staat
     * @param acc: boolean die aangeeft of de staat accepterend is.
     */
    State_NFA(bool starting, string n, bool acc, char eps);

    /**
     * Deze functie zet of de staat accepting is of niet naar de gegeven boolean.
     * @param b: boolean
     */
    void setAccepting(bool b);

    /**
     * Deze functie stelt de staat in als een startstaat.
     * @param b
     */
    void setStarting(bool b);

    /**
     * Deze functie geeft de naam van de staat terug.
     * @return: string
     */
    string getName() const;

    /**
     * Deze functie voegt een transitie toe aan deze staat. Als deze staat al bestaande transities heeft op de gegeven input,
     * wordt de nieuwe staat gewoon bij de set met de andere staten toegevoegd.
     * @param input: input character voor de transitie;
     * @param tgt; set van staten waarnaar men gaat op de gegeven input.
     */
    void addTransition(char input, State_NFA* tgt); //voegt een transitie toe aan de state.

    /**
     * Deze functie geeft een set terug van staten die uit deze staat bereikt worden met epsilon transities inclusief de staat zelf.
     * ->  def ECLOSE
     * @return: set van de bereikte staten.
     */
    set<State_NFA*> ECLOSE();

    /**
     * Deze functie geeft terug of een ENFA staat accepterend is of niet.
     * @return: boolean
     */
    bool is_accepting();

    /**
     * Deze functie voort de transitie uit en geeft een set terug van de resulterende staten.
     * @param i: de input character
     * @return: set van de resulterende staten.
     */
    set<State_NFA*> transition(char i);  //voert de transitie uit.

    /**
     * Deze functie telt de aantal transities per input character waarvoor deze staat een transitie uitvoert en bepaald
     * de graad van de staat.
     * @param counter_map: map voor het tellen van de transities.
     * @param degree_map: map voor het tellen voor staten van verschillende graad.
     */
    void countUpTransitions(map<char,int>& counter_map, map<int,int>& degree_map);


    /**
     * Getter voor de transities van een state
     * @return map<char, set<State_NFA*>>
     */
    const map<char, set<State_NFA*>> &getTTo() const;

    /**
     * Deze functie verandert de naam van de staat naar de gegeven string
     * @param Name: nieuwe naam van de staat.
     */
    void setName(string Name);

};


#endif //SO1_TA_STATE_H
