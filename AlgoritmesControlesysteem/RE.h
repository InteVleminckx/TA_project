//
// Created by Cem Tuncay on 06/03/2021.
//

#ifndef SO1_TA_RE_H
#define SO1_TA_RE_H

#include "State.h"
#include "ENFA.h"

#include <string>
#include <vector>

using namespace std;

class RE {
private:
    vector<char> alphabet;
    vector<char> tokens;
    char eps;
    string expressie;
    int replaced = -1;
    int nr0fStates = -1;
    map<string, vector<vector<State_NFA*>>> subENFAs;
    map<string,string> placeholders;
    map<string, vector<State_NFA*>> placeholderENFAs;



public:
    /**
     * Constructor van RE.
     * @param expressie: Expressie in stringvorm
     * @param epsilon: De character die epsilon voorstelt.
     */
    RE(string expressie, char epsilon);


    /**
     * Deze functie leidt de alfabet uit de gegeven expressie en epsilon char af. En maakt een vector aan met elke
     * individuele character in de expressie -> tokens
     * @param expr: RegEx
     * @param eps: epsilon
     */
    void getAlphabet(string& expr, char eps);


    /**
     *Deze functie parsed over de expressie en maakt voor al de geconcateneerde subexpressies een eNFA.
     */
    void parser();


    /**
     * Deze functie maakt voor de stukken in de expressie die tussen haakjes zitten een replacernaam en steekt deze in de map
     * placeholders met de vervangen stuk als value.
     */
    void PlaceHolderMaker();


    /**
     * Deze functie maakt voor elke placeholder een overeenkomstige ENFA aan samen met de replToENFA functie.
     * Deze worden in de juiste volgerde gemaakt. repl0->...->repl(k)
     */
    void PlaceHolderENFAmaker();


    /**
     * Deze functie maakt een ENFA aan voor een replacement.
     * @param replnaam van de replacement.
     * @param i: nummer van replacement
     * @return: ENFA in de vorma van een vector van ENFA
     */
    vector<State_NFA*> replToENFA(string repl, int i);


    /**
     * Deze functie zet uieindelijk allem replacements en de rest van de expressie samen.
     * @return: Resulterende ENFA in de vorm van een vector
     */
    vector<State_NFA*> replacedMerger();

    /**
     * Deze functie kijk na of de gegeven string een concatenatie voorstelt.
     * @param subexpression: de expressie die gecontroleert wordt
     * @return: geconcateneerde ENFA
     */
    vector<State_NFA*>concatChecker(string subexpression);


    /**
     * Deze functie zet de RE om in een ENFA.
     * @return: ENFA object.
     */
    ENFA toENFA();

    /**
     * Deze functie zet de gegvene regex om naar een DFA met als tussenstap een ENFA.
     * @return: DFA
     */
    DFA toDFA();


    /**
     * Deze functie maakt een ENFA voor expressie in de vorm van een enkele character.
     * @param input: input char
     */
    vector<State_NFA*> getCharENFA(char input);


    /**
     * Deze functie maakt een ENFA voor een expressie in de vorm van geconcateneerde characters. vb: abc*d
     * @param conChar: vector van de geconcateneerde characters in de juiste volgorde.
     * @return: ENFA in de vorm vaan een vector met ENFA-staten.
     */
    vector<State_NFA*> concatenator(vector<char> conChar);


    /**
     * Deze functie maakt een unie van gegeven subENFA's.
     * @param subEnfa: De subENFA's
     * @param epsilon: geeft aan of eer epsilontransitie is in de unie.
     * @param kleen: Geeft an of de unie kleenClosed moet worden
     * @return: ENFA in de vorm van een vector.
     */
    vector<State_NFA*> Union(vector<vector<State_NFA*>> subEnfa, bool epsilon, bool kleen);


    /**
     * Deze functie KeenClosed een gegefen subENFA.
     * @param subEnfa
     * @return: resulterende ENFA in de vorm van een vector.
     */
    vector<State_NFA*> KleeneStar(vector<State_NFA*> subEnfa);
};

#endif //SO1_TA_RE_H
