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
    static void brzozowskiAlgorithm(DFA &productAutomaat, vector<long> &times);

    /**
     * Hulpfunctie die de reversal van een DFA gaat nemen
     * @param productAutomaat = automaat waarvan we de reversal willen nemen
     */
    static void reversal(DFA &productAutomaat, ENFA &e_nfa);

    /**
     * Functie die nagaat of een bepaalde state reachable is vanuit de startstate
     * @param start_state = state die de startstate is van onze DFA
     * @param target = eindstate waarvan we willen weten of deze bereibaar is
     * @param alphabet = verzameling van chars
     * @return bool
     */
    static bool isStateReachable(State* start_state, State* current_state, State* target, vector<char> alphabet,
                                 vector<State*> &reeds_gehad);

    /**
     * Functie die states verwijderd wanneer deze niet bereikbaar zijn.
     * @param productautomaat = een DFA waar de non reachable states verwijderd moeten worden.
     */
    static void elemNonReachableStatesRecursively(DFA &productautomaat);
    // Extra functie van NFA naar DFA = subsetconstruction of modified toevoegen
};


#endif //PROJECTTA_BRZOZOWSKI_H
