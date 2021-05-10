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

    // ENFA die we zullen gebruiken doorheen de functies
    ENFA enfa = ENFA();

    reversal(productAutomaat, enfa);             // Stap 1
    productAutomaat = enfa.toDFA();                    // Stap 2
    elemNonReachableStates(productAutomaat);        // Stap 3
    reversal(productAutomaat, enfa);             // Stap 4
    productAutomaat = enfa.toDFA();                    // Stap 5
    elemNonReachableStates(productAutomaat);        // Stap 6
}

void Brzozowski::reversal(DFA &productAutomaat, ENFA &e_nfa) {
    /*
     * Stappenplan:
     * 1) Starting state wordt enigste accepting state ==> direct toevoegen
     * 2) Accepting states worden start state
     *      1 Accepting state ==> normale start state
     *      Meerdere accepting states ==> nieuwe start state met eps-trans naar deze accepting states
     * 3) Alle andere states toevoegen die nog niet werden toegevoegd
     * 4) Alle transities omkeren ==> to_state wordt this + transitie toevoegen aan to_state
     */

    // Starting state wordt enigste accepting state + toevoegen aan e_nfa
    const string& name_start_state = productAutomaat.getStartState();
    State* state = productAutomaat.getStates().at(name_start_state);
    State_NFA* new_accepting_state = new State_NFA(state->isStarting(), state->getName(), true, e_nfa.getEpsilon());
    e_nfa.addToStates(new_accepting_state);

    // Accepting states bepalen
    vector<State*> accepting_states = productAutomaat.getAcceptingStates();

    // Als er slechts 1 accepting state is ==> maken en toevoegen aan e_nfa
    if (accepting_states.size() == 1)
    {
        State_NFA* new_starting_state = new State_NFA(true,
                                              accepting_states[0]->getName(),
                                              false,
                                              e_nfa.getEpsilon());
        e_nfa.addToStates(new_starting_state);
        e_nfa.addToStartingStates(new_starting_state->getName());
        e_nfa.addToCurrentStates(new_starting_state->getName());
    }

    // Meerdere states
    else if (accepting_states.size() > 1)
    {
        State_NFA* new_starting_state = new State_NFA(true,
                                                      "S",
                                                      false,
                                                      e_nfa.getEpsilon());
        // Voor elke accepting state een transitie van new_starting_state naar accepting state
        for (State* state1 : accepting_states)
        {
            State_NFA* new_state = new State_NFA(false, state1->getName(), false, e_nfa.getEpsilon());
            e_nfa.addToStates(new_state);
            new_starting_state->addTransition(e_nfa.getEpsilon(), new_state);
        }
        e_nfa.addToStates(new_starting_state);

    }

    for (const auto &stateDFA : productAutomaat.getStates())
    {
        //De overige states moeten nog worden toegevoegd, we controlleren dus eerst of de state er al in zit of niet
        //als dit niet het geval is maken we een nieuwe state aan en voegen we deze toe.
        if (!e_nfa.getStates().count(stateDFA.second->getName()))
        {
            State_NFA* new_NFA_state = new State_NFA(false,
                                                     stateDFA.second->getName(),
                                                     false,
                                                     e_nfa.getEpsilon());

            e_nfa.addToStates(new_NFA_state);
        }
    }


    //nu moeten we enkel nog de transities toevoegen aan de states.
    for (const auto &stateDFA : productAutomaat.getStates())
    {
        string fromDFA = stateDFA.first;
        State_NFA* from;

        for (auto &fromState : e_nfa.getStates())
        {
            if (fromDFA == fromState.second->getName())
            {
                from = fromState.second;
                break;
            }
        }

        for (auto to : stateDFA.second->getTTo()) setTransitions(to, e_nfa, from);
    }
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

void Brzozowski::setTransitions(pair<const char, State *> &stateDFA, ENFA &e_nfa, State_NFA* from)
{
    const char transitie = stateDFA.first;

    for (auto &state : e_nfa.getStates())
    {
        //Als de state nog geen transities heeft moeten we deze nog toevoegen
        //En we hebben de juiste state gevonden
        if (stateDFA.second->getName() == state.second->getName())
        {
            state.second->addTransition(transitie, from);
            break;
        }
    }
}
