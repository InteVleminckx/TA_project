//
// Created by jonas on 9/05/21.
//

#include "Brzozowski.h"

void Brzozowski::brzozowskiAlgorithm(DFA &productAutomaat, vector<long> &times) {
    /*
     * Stap 1 : reversal
     * Stap 2 : determineren
     * Stap 3 : states die niet bereikbaar zijn elimineren
     * Stap 4 : reversal
     * Stap 5 : determineren
     * Stap 6 : states die niet bereikbaar zijn elimineren
     */

    // Voor de duur van de functie te bepalen
    long time;
    auto start = high_resolution_clock::now();

    // ENFA die we zullen gebruiken doorheen de functies
    ENFA enfa = ENFA();
    enfa.setEpsilon('e');
    enfa.setAlphabet(productAutomaat.getAlphabet());
    //enfa.setStartState(const_cast<string &>(productAutomaat.getStartState()));

    reversal(productAutomaat, enfa);                    // Stap 1
    productAutomaat = enfa.toDFA(true);              // Stap 2
    productAutomaat.renameStates();                           // Stap 3
    elemNonReachableStatesRecursively(productAutomaat);    // Stap 4
    enfa = ENFA();
    enfa.setEpsilon('e');
    enfa.setAlphabet(productAutomaat.getAlphabet());

    reversal(productAutomaat, enfa);                    // Stap 5
    productAutomaat = enfa.toDFA(true);              // Stap 6
    productAutomaat.renameStates();                           // Stap 7
    elemNonReachableStatesRecursively(productAutomaat);    // Stap 8
  
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    time = duration.count();
    times.push_back(time);
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
    State_NFA* new_accepting_state = new State_NFA(false, state->getName(), true, e_nfa.getEpsilon());
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

        // Als de enigste starting state eig ook de enigste accepting state was, passen we de new_accepting_state aan
        if (new_starting_state->getName() == new_accepting_state->getName())
        {
            new_accepting_state->setStarting(true);
            string temp_name = accepting_states[0]->getName();
            e_nfa.setStartState(temp_name);
            e_nfa.addToStartingStates(new_accepting_state->getName());
            e_nfa.addToCurrentStates(new_accepting_state->getName());
        }
        else
        {
            string temp_name = accepting_states[0]->getName();
            e_nfa.setStartState(temp_name);
            e_nfa.addToStates(new_starting_state);
            e_nfa.addToStartingStates(new_starting_state->getName());
            e_nfa.addToCurrentStates(new_starting_state->getName());
        }
    }

    // Meerdere states
    else if (accepting_states.size() > 1)
    {
        State_NFA* new_starting_state = new State_NFA(true,"q0",false, e_nfa.getEpsilon());

        string tempString = "q0";
        e_nfa.setStartState(tempString);

        // Voor elke accepting state een transitie van new_starting_state naar accepting state
        for (State* state1 : accepting_states)
        {
            State_NFA* new_state = new State_NFA(false, state1->getName(), false, e_nfa.getEpsilon());

            // Als het zowel een startstate als accepting state was oorspronkelijk, dan wordt de state nu ook accepting
            if (state1->isStarting())
            {
                new_state->setAccepting(true);
            }
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
            State_NFA* new_NFA_state = new State_NFA(false,stateDFA.second->getName(),false, e_nfa.getEpsilon());
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

bool Brzozowski::isStateReachable(State *start_state, State* current_state, State *target, vector<char> alphabet,
                                  vector<State*> &reeds_gehad) {
    // Voor deze functie gaan we recursie gebruiken

    // Loop om te kijken of we een state niet al zijn tegengekomen
    for (State* state : reeds_gehad)
    {
        if (state == current_state)  return false;
    }

    // We hebben state gevonden, returnen true
    if (current_state == target) return true;

    // Als deze state geen "kinderen" meer heeft, hebben we de state niet kunnen vinden dus returnen false
    else if (current_state->getTTo().empty()) return false;

    // Kijken naar de "kinderen" en recursief de functie toepassen
    else
    {
        reeds_gehad.push_back(current_state);

        // Voor elke letter
        for (char letter : alphabet)
        {
            // Als de state bestaat, returnen we true
            if (isStateReachable(start_state, current_state->getTTo().at(letter), target, alphabet, reeds_gehad))
            {
                return true;
            }
        }
        return false;
    }
}

void Brzozowski::elemNonReachableStatesRecursively(DFA &productautomaat) {
    map<string, State*> nieuwe_states = {};
    State* start_state = productautomaat.getStates().at(productautomaat.getStartState());
    vector<State*> reeds_gehad = {};
    for (const auto& it : productautomaat.getStates())
    {
        // Als de state reachable is, voegen we deze toe
        if (isStateReachable(start_state, start_state, it.second, productautomaat.getAlphabet(), reeds_gehad))
        {
            nieuwe_states[it.first] = it.second;
        }
        reeds_gehad.clear();
    }
    productautomaat.setStates(nieuwe_states);
}
