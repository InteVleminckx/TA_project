//
// Created by jonas on 9/05/21.
//

#ifndef PROJECTTA_BRZOZOWSKI_H
#define PROJECTTA_BRZOZOWSKI_H

#include "Datastructuur.h"

using namespace std;

class DFA;

class Brzozowski {
public:
    /**
     * Functie die een automaat gaat minimaliseren met Brzozowski-algoritme
     * @param productAutomaat = automaat die we willen minimaliseren
     */
    static void brzozowskiAlgorithm(DFA &productAutomaat);

    /**
     * Hulpfunctie die de reversal van een DFA gaat nemen
     * @param productAutomaat = automaat waarvan we de reversal willen nemen
     */
    static void reversal(DFA &productAutomaat, ENFA &e_nfa);

    /**
     * Functie die alle niet-bereikbare states gaat elemineren
     * @param productautomaat = automaat waarop we dit willen toepassen
     */
    static void elemNonReachableStates(DFA &productautomaat);


    // Extra functie van NFA naar DFA = subsetconstruction of modified toevoegen
};


#endif //PROJECTTA_BRZOZOWSKI_H
