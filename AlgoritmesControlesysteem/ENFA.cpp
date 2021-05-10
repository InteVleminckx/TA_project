//
// Created by Dzhem Myumyun on 02/03/2021.
//

#include <fstream>
#include <iostream>
#include <utility>

#include "ENFA.h"
#include "json.hpp"

using namespace std;

ENFA::ENFA() = default;

ENFA::ENFA(const string &input) {
    ifstream input_json(input);
    nlohmann::json j = nlohmann::json::parse(input_json);
    input_json.close();

    auto aa = j["alphabet"];
    for (auto i:aa){
        string s = i;
        alphabet.push_back(s.at(0));
    }

    string epsilon = j["eps"];
    eps = epsilon[0];

    string start_state;
    for (auto s:j["states"]){
        string name = s["name"];
        bool acc = s["accepting"];
        bool start = s["starting"];
        if (start){
            start_state = name;
            q0 = name;
        }
        auto state = new State_NFA(start, name, acc, epsilon[0]);
        states.insert(pair<string, State_NFA*> (name, state));
    }

    for (auto t:j["transitions"]){
        string from = t["from"];
        string to = t["to"];
        string input_char = t["input"];


        states[from]->addTransition(input_char[0], states[to]);
    }

    set<State_NFA*> start_set = states[start_state]->ECLOSE();
    for (auto set:start_set){
        current_states.insert(set->getName());
        starting.insert(set->getName());
    }
}


set<string> ENFA::toStringSet(set<State_NFA*> states){
    set<string> string_set;
    for (auto state:states){
        string_set.insert(state->getName());
    }
    return string_set;
}


bool ENFA::acceptingSet(set<string> current){
    for (auto s:current){
        bool accept = states[s]->is_accepting();
        if (accept){
            return true;
        }
    }
    return false;
}


bool ENFA::accepts(string input) {
    for (auto c:input) {
        set<State_NFA *> state_set;
        //cout << "begin#####################" << endl;
        for (auto s:current_states) {
            //cout << s << endl;
            set<State_NFA *> res_after_input = states[s]->transition(c);
            state_set.insert(res_after_input.begin(), res_after_input.end());
        }
        //cout << "eind#####################" << endl;

        current_states.clear();
        current_states = toStringSet(state_set);
    }
    bool accepting = acceptingSet(current_states);
    reset();
    return accepting;
}


void ENFA::reset() {
    current_states = starting;
    for (auto state:states){
        auto starting_state = starting.find(state.first);
        if (starting_state != starting.end()){
            state.second->setState(true);
        }else{
            state.second->setState(false);
        }
    }
}


string ENFA::setToString(set<State_NFA*> states){
    string name = "{";
    auto states_set = toStringSet(states);  //Omzetting naar set van strings met de namen van de staten.
    if (states_set.size() == 0){    //Als het een lege set is.
        name = name + "}";
        return name;
    }
    for (auto state:states_set){    //String wordt samengesteld
        auto it = states_set.end();
        it--;
        if (state == *it){  //Laatste staat van de set.
            name = name + state + "}";
            continue;
        }
        name = name + state + ",";
    }
    return name;
}


DFA ENFA::toDFA() {
    vector<set<State_NFA*>> subsets = {states[q0]->ECLOSE()};   //vector me de subsets gevormd door Lazy evaluation.
    map<string, State*> DFA_states; //map met staten voor de te cosntrueren DFA.

    State* dfa_startState = new State(true, setToString(*subsets.begin()),
                                      acceptingSet(toStringSet(*subsets.begin())));    //Startstaat van de DFA = ECLOSE(q0)
    DFA_states.insert(pair<string, State*> (dfa_startState->getName(), dfa_startState));

    for (auto it=0; it< subsets.size(); it++) {
        for (auto c:alphabet) {
            //Per inputcharacter wordt per subset de output bepaald.
            set<State_NFA*> sub;

            for (auto s:subsets.at(it)){
                auto res = s->transition(c);
                sub.insert(res.begin(), res.end());
            }

            if (find(subsets.begin(), subsets.end(), sub) == subsets.end()){    //Als de subset nog niet in de vector zit.
                subsets.push_back(sub);
            }

            if (DFA_states.find(setToString(sub)) == DFA_states.end()){
                //Als de Staat die de huidige subsetvoorstelt nog niet bestaat = LAZY EVALUATION
                State* n_state = new State(false, setToString(sub), acceptingSet(toStringSet(sub)));
                DFA_states.insert(pair<string, State*> (n_state->getName(), n_state));
                string n = setToString(subsets.at(it));
                DFA_states[n]->addTransition(c, n_state);
            }
            else {  //ALs de staat voorde subset al bestaat.
                DFA_states[setToString(subsets.at(it))]->addTransition(c, DFA_states[setToString(sub)]);
            }
        }
    }

    //Alle transities naar de DEAD-state.
    for (auto s:DFA_states){
        auto death_transitions = s.second->no_transitionChars(alphabet);
        for (auto t:death_transitions){
            s.second->addTransition(t, DFA_states["{}"]);
        }
    }
    DFA dfa(DFA_states, alphabet); //DFA wordt geconstrueert..
    return dfa;
}


ENFA::ENFA(map<string, State_NFA *> s, vector<char> alfabet, string start, char e) {
    eps = e;
    states = s;
    alphabet = alfabet;
    q0 = start;
    set<State_NFA*> start_set = states[start]->ECLOSE();
    for (auto set:start_set){
        current_states.insert(set->getName());
        starting.insert(set->getName());
    }
}


void ENFA::printStats() {
    cout << "no_of_states=" << states.size() << endl;
    map<char, int> no_input_trans;
    map<int, int> degree;
    for (char c:alphabet){
        no_input_trans[c]= 0;
    }
    no_input_trans[eps] = 0;

    for (auto state:states){
        state.second->countUpTransitions(no_input_trans, degree);
    }

    sort(alphabet.begin(), alphabet.end());
    cout << "no_of_transitions[" << eps << "]=" << no_input_trans[eps] << endl;
    for (auto c:alphabet){
        cout << "no_of_transitions[" << c << "]=" << no_input_trans[c] << endl;
    }
    for(auto d:degree){
        cout << "degree[" << d.first << "]=" << d.second << endl;
    }
}

void ENFA::addToStates(State_NFA *state) {
    states[state->getName()] = state;
}

char ENFA::getEpsilon() const {
    return eps;
}

void ENFA::addToStartingStates(const string &name) {
    starting.insert(name);
}

void ENFA::addToCurrentStates(const string &name) {
    current_states.insert(name);
}

const map<string, State_NFA *> &ENFA::getStates() const {
    return states;
}

vector<State_NFA *> ENFA::getAcceptingStates() const {
    vector<State_NFA*> accepting_states = {};

    // Over alle states loopen
    for (const auto &pair : getStates())
    {
        // Als state accepting is ==> toevoegen aan vector
        if (pair.second->is_accepting())
        {
            accepting_states.push_back(pair.second);
        }
    }
    return accepting_states;
}

void ENFA::setStartState(string &startState) {
    q0 = startState;
}

void ENFA::setEpsilon(char epsilon) {
    eps = epsilon;
}
