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
    set<string> namen = {};
    map<string, State*> nieuwe_states = {};

    // Voor elke state in de productautomaat
    for(auto &state : productautomaat.getStates())
    {
        // Voor elke transitie in deze state
        for (auto it : state.second->getTTo())
        {
            // Naam van TO state toevoegen aan namen
            namen.insert(it.second->getName());
        }
    }

    // Over alle states loopen
    for (const auto& naam : productautomaat.allStates())
    {
        //Als er wel transities zijn, voegen we deze toe aan de
        if (namen.count(naam) || productautomaat.getStates().at(naam)->isStarting())
        {
            nieuwe_states[naam] = productautomaat.getStates().at(naam);
        }
    }

    // productautomaat zijn states aanpassen zodat enkel bereikbare states erin zitten
    productautomaat.setStates(nieuwe_states);
}
