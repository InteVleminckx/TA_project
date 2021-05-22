//
// Created by Cem Tuncay on 06/05/2021.
//

#ifndef PROJECTTA_BESTEMMING_H
#define PROJECTTA_BESTEMMING_H

#include <string>
#include "AlgoritmesControlesysteem//DFA.h"

using namespace std;

class Bestemming {
private:
    string fNaam;
    string fRegex;
    DFA dfa;

public:

    /**
     * Constructor met memebervariabelen.
     * @param naam: Naam van het halte.
     * @param RegEx: Reguliere expressie voor de halte
     */
    Bestemming(string naam, string RegEx);

    /**
     * Default constructor
     */
    Bestemming();

    /**
     * Deze functie stelt de naam in van de halte.
     * @param naam: naam van de halte
     */
    void setName(string naam);

    /**
     * Deze functie geeft de naam van de halte terug.
     * @return: fNaam
     */
    string getName();

    /**
     * Deze functie stelt het RegEx in voor deze halte.
     * @param RegEx: Unieke Regex voor de halte
     */
    void setRegex(string RegEx);

    /**
     * Deze functie geeft de regex van de halte terug.
     * @return
     */
    string getRegex();

    /**
     * Deze functie stelt de geminimaliseerde DFA in voor de bestemming.
     */
    void setDFA(DFA& dfa);

    /**
     * Deze functie geeft een refference naar de DFA van de bestemming.
     * @return: dfa
     */
    DFA& getDFA();


};


#endif //PROJECTTA_BESTEMMING_H
