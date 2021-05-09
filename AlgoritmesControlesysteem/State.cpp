//
// Created by Dzhem Myumyun on 19/02/2021.
//

#include <vector>
#include "State.h"
#include "json.hpp"

#define boolToStr(b) (b?"true":"false")


State::State(bool start, string n, bool acc) {
    starting = start;
    state  = start;
    name = n;
    accepting = acc;
}


string State::getName() const{
    return name;
}


void State::addTransition(char input, State *to) {
    t_to.insert(pair<char, State*>(input, to));
}


void State::setState(bool s) {
    state = s;
}


string State::transition(char i) {
    auto to_state = t_to[i];
    state = false;
    to_state->setState(true);
    return to_state->getName();
}


bool State::is_accept() const {
    return accepting;
}


nlohmann::json State::to_map() {
    nlohmann::json j;
    j["name"] = name;
    j["starting"] = starting;
    j["accepting"] = accepting;
    return j;
}


vector<map<string, string>> State::transitionsToMap() {
    vector<map<string, string>> t;
    for (auto s:t_to){
        map<string, string> map;
        map["from"] = name;
        map["input"] = s.first;
        map["to"] = s.second->getName();
        t.push_back(map);
    }
    return t;
}


bool State::isStarting() {
    return starting;
}


set<char> State::no_transitionChars(vector<char>& alphabet) {
    set<char> chars;
    for (auto c:alphabet){
        if (t_to.find(c) == t_to.end()){
            chars.insert(c);
        }
    }
    return chars;
}


string State::goesTo(char c) {
    return t_to[c]->getName();
}

void State::changeName(string n) {
    name = n;
}


void State_NFA::setState(bool s) {
    state = s;
}


State_NFA::State_NFA(bool s, string n, bool acc, char e) {
    starting = s;
    state = s;
    name = n;
    accepting = acc;
    eps = e;
}


string State_NFA::getName() const {
    return name;
}


void State_NFA::addTransition(char input, State_NFA *tgt) {
    auto transitie = t_to.find(input);
    if (transitie == t_to.end()){
        set<State_NFA*> set_toStates = {tgt};
        t_to.insert(pair<char,set<State_NFA*>> (input, set_toStates));
    }else{
        t_to[input].insert(tgt);
    }
}


set<State_NFA*> State_NFA::ECLOSE() {
    auto eps_transities = t_to.find(eps);
    state = true;
    set<State_NFA*> _set;
    _set.insert(this);
    if (eps_transities == t_to.end()){
        _set;
        return _set;
    }else{
        for (auto s:eps_transities->second){
            if (s == this){
                continue;
            }
            auto elc_s = s->ECLOSE();
            _set.insert(elc_s.begin(), elc_s.end());
        }
        return _set;
    }
}


bool State_NFA::is_accepting() {
    return accepting;
}


set<State_NFA *> State_NFA::transition(char i) {
    auto transities = t_to.find(i);
    state = false;
    if (transities == t_to.end()){
        return set<State_NFA *>();
    }else{
        set<State_NFA*> states_to;
        for (auto s:transities->second){
            auto e_closed = s->ECLOSE();
            states_to.insert(e_closed.begin(), e_closed.end());
        }
        return states_to;
    }
}


void State_NFA::setAccepting(bool b) {
    accepting = b;
}


void State_NFA::setStarting(bool b) {
    starting = b;
    state = b;
}


void State_NFA::countUpTransitions(map<char, int>& counter_map, map<int, int>& degree_map) {
    for(auto t:t_to){
        counter_map[t.first] = counter_map[t.first] + t.second.size();
    }
    int degree = 0;
    for(auto t:t_to){
        degree = degree + t.second.size();
    }
    if(degree_map.find(degree) == degree_map.end()){
        degree_map[degree] = 1;
    }else{
        degree_map[degree]++;
    }
}

