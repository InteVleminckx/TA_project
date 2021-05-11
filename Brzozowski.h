//
// Created by jonas on 9/05/21.
//

#ifndef PROJECTTA_BRZOZOWSKI_H
#define PROJECTTA_BRZOZOWSKI_H

#include "Datastructuur.h"
#include "AlgoritmesControlesysteem/DFA.h"
#include "AlgoritmesControlesysteem/ENFA.h"
#include "AlgoritmesControlesysteem/State.h"
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

class DFA;

class Brzozowski {

    /**
     * Deze functie keert de transities om en kent ze toe aan de juiste state
     * @param stateDFA: De state naar waar de transitie naar toe moet gaan
     * @param e_nfa: De ENFA
     * @param from: De state waaruit de transities vertrekken
     */
    static void setTransitions(pair<const char, State*> &stateDFA, ENFA &e_nfa, State_NFA* from);

public:
    /**
     * Functie die een automaat gaat minimaliseren met Brzozowski-algoritme
     * @param productAutomaat = automaat die we willen minimaliseren
     * @param time = tijd die we by ref meegeven waarin we de duur van de functie kunnen opslagen
     */
    static void brzozowskiAlgorithm(DFA &productAutomaat, long &time);

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
