//
// Created by jonas on 9/05/21.
//

#include "Brzozowski.h"

void Brzozowski::brzozowskiAlgorithm(DFA &productAutomaat) {

    /*
     * Stap 1 : reversal
     * Stap 2 : determineren
     * Stap 3 : states die niet bereikbaar zijn elimineren
     * Stap 4 : reversal
     * Stap 5 : determineren
     * Stap 6 : states die niet bereikbaar zijn elimineren
     */

    ENFA enfa = ENFA();

    reversal(productAutomaat, enfa);
    productAutomaat = enfa.toDFA();
    elemNonReachableStates(productAutomaat);
    reversal(productAutomaat, enfa);
    productAutomaat = enfa.toDFA();
    elemNonReachableStates(productAutomaat);
}

void Brzozowski::reversal(DFA &productAutomaat, ENFA &e_nfa) {

}

void Brzozowski::elemNonReachableStates(DFA &productautomaat) {

    /*
     * Lopen over alle states uit de DFA en de TO van elke transitie toevoegen in die namen
     *
     */

    set<string> namen = {};

    // Voor elke state in de productautomaat
    for(auto &state : productautomaat.getStates())
    {
        // Voor elke transitie in deze state
        for (auto it : state.second->getTTo())
        {
            // Naam van TO state toevoegen aan namen
            string name_to_state = it.second->getName();
            namen.insert(name_to_state);
        }
    }

    // Over alle states loopen
    for (const auto& naam : productautomaat.allStates())
    {
        //Als er geen transitie is naar deze state dan mag deze verwijdert worden
        if (!namen.count(naam))
        {

        }
    }
}
