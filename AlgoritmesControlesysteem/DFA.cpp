//
// Created by Dzhem Myumyun on 10/02/2021.
//

#include "DFA.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include "State.h"
#include <iomanip>
#include <algorithm>

using namespace std;


bool DFA::accepts(string input) {
    //Loop over de inputstring
    for(auto c:input){
        current = states[current]->transition(c);
    }
    bool accept = states[current]->is_accept(); //bool die aangeeft of de cirrent state accepting is
    reset();
    return accept;
}


void DFA::reset() {
    //current wordt terug de start state
    current = start_state;
    for(auto s:states){ //loop over de states
        if (s.first == start_state){    //start state wordt true
            s.second->setState(true);
        }else{
            s.second->setState(false);
        }
    }
}


using json = nlohmann::json;


DFA::DFA(const string& input) {
    //inlezen van het .json bestand
    ifstream input_json(input);
    json j = nlohmann::json::parse(input_json);
    input_json.close();

    auto aa = j["alphabet"];
    for (auto i:aa){
        string s = i;
        alphabet.push_back(s.at(0));
    }

    //Loop over de states van .json bestand en maakt de states aan.
    for (auto s:j["states"]){
        string name = s["name"];
        bool acc = s["accepting"];
        bool start = s["starting"];
        if (start) {
            current = name;
            start_state = name; //start state van de DFA(veranderd niet);
        }
        auto state = new State(start, name, acc);
        states.insert(pair<string, State*> (name, state));
    }

    //maakt de transities van de states aan.
    for (auto t:j["transitions"]){
        string from = t["from"];
        string to = t["to"];
        string input = t["input"];

        states[from]->addTransition(input.at(0), states[to]);
    }
}


void DFA::print(ostream &os_stream) {
    nlohmann::json j;
    j["type"] = "DFA";
    vector<string> alfabet;
    for (char c:alphabet){
        string s;
        s = s + c;
        alfabet.push_back(s);
    }
    j["alphabet"] = alfabet;


    vector<nlohmann::json> st;
    for (auto s:states){
        st.push_back(s.second->to_map());
    }
    j["states"] = st;

    vector<map<string, string>> tr;
    for (auto t:states){
        auto vect = t.second->transitionsToMap();
        tr.insert(tr.end(), vect.begin(), vect.end());
    }
    j["transitions"] = tr;

    cout << setw(4) << j << endl;
}


DFA::DFA(map<string, State *> sets, vector<char> a) {
    states = sets;
    for (auto s:sets){
        if (s.second->isStarting()){
            start_state = s.first;
            current = s.first;
        }
    }
    alphabet = a;
}


DFA::DFA(DFA dfa1, DFA dfa2, bool doorsnede) {
    //Staten van de 2 dfa's in string vorm
    auto states1 = dfa1.getAllStates();
    auto states2 = dfa2.getAllStates();

    //Vector die al de bereikbare koppels van staten bij zal houden.
    vector<pair<string, string>> state_pairs;

    //Startstaat van de productautomaat
    pair<string, string> p;
    p.first = states1.at(0);
    p.second = states2.at(0);
    state_pairs.push_back(p);

    alphabet = dfa1.getAlphabet();

    //loop die al de staten die bereikbaar zijn van de productautomaat bepaald.
    for (int i=0; i<state_pairs.size(); i++) {
        auto pairs = state_pairs.at(i);
        for(auto c: alphabet) {
            pair<string, string> stateTo;
            stateTo.first = dfa1.stateGoesTo(pairs.first, c);
            stateTo.second = dfa2.stateGoesTo(pairs.second, c);
            if (find(state_pairs.begin(), state_pairs.end(), stateTo) == state_pairs.end()) {
                state_pairs.push_back(stateTo);
            }
        }
    }


    //Aanmaak van de staten van de productautomaat.
    for (auto pairs:state_pairs){
        string name = "(";
        name = name + pairs.first + ",";
        name = name + pairs.second + ")";
        //volgende 2 booleans geven aan of de huidige staten van de 2 dfa's accepterend zijn.
        bool s1a = dfa1.isStateAccepting(pairs.first);
        bool s2a = dfa2.isStateAccepting(pairs.second);
        //booleans die aangeven of de 2 staten startstaten zijn.
        bool s1s = dfa1.isStateStarting(pairs.first);
        bool s2s = dfa2.isStateStarting(pairs.second);
        bool starting = s1s and s2s;
        State* state = nullptr;
        if (doorsnede){ //als het om de ddorsnede gaat
            if(s1a and s2a){
                state = new State(starting,name, true);
            }else{
                state = new State(starting,name, false);
            }
        }else{  //unie
            if(s1a or s2a){
                state = new State(starting,name, true);
            }else{
                state = new State(starting,name, false);
            }
        }
        if (starting){
            start_state = name;
            current = name;
        }
        states[name] = state;
    }

    //Loop die de transities opstelt.
    alphabet = dfa1.getAlphabet();
    for(auto c: alphabet){
        for (auto pairs:state_pairs) {
            string name = "(";
            name = name + pairs.first + ",";
            name = name + pairs.second + ")";
            string naamTo = "(";
            naamTo = naamTo + dfa1.stateGoesTo(pairs.first, c) + ",";
            naamTo = naamTo + dfa2.stateGoesTo(pairs.second, c) + ")";
            states[name]->addTransition(c, states[naamTo]);
        }
    }
}


vector<string> DFA::getAllStates(){
    vector<string> stateNames;
    for (auto s:states){
        stateNames.push_back(s.first);
    }
    sort(stateNames.begin(), stateNames.end());
    return stateNames;
}


vector<char> DFA::getAlphabet() const {
    return alphabet;
}


bool DFA::isStateAccepting(string state) {
    if(states[state]->is_accept()){
        return true;
    }else{
        return false;
    }
}


bool DFA::isStateStarting(string state) {
    if(states[state]->isStarting()){
        return true;
    }else{
        return false;
    }
}


string DFA::stateGoesTo(string name, char input) {
    return states[name]->goesTo(input);
}

DFA DFA::minimize(long &time) {

    // Voor de tijd te meten van de functie
    auto start = high_resolution_clock::now();

    map<string ,map<string ,char>> table;

    TFA(table, states);

    TFA_table = table;

    vector<string> stateNames = getAllStates();
    map<string, vector<string>> eq_states; //map die alle staten waarmee een staat equivqlent is bij zal houden,
                                           //inclusief zichzelf.

    //Hier worden alle staten die equivalent zijn met elkaar samen genomen.
    for(auto it1 = table.begin(); it1 != table.end(); it1++){
        for(auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            if(it2->second == '-'){
                //Als de staten equivalent zijn worden ze uit de oude staten verwijdert.
                auto it_pos = find(stateNames.begin(), stateNames.end(), it1->first);
                if(it_pos != stateNames.end()) {
                    stateNames.erase(it_pos);
                }
                it_pos = find(stateNames.begin(), stateNames.end(), it2->first);
                if(it_pos!= stateNames.end()){
                    stateNames.erase(it_pos);
                }
                //Als er nog geen andere staten zijn die equivalent zijn met it1->first.
                if(eq_states.find(it1->first) == eq_states.end()){
                    vector<string> eq_s = {it1->first, it2->first};
                    eq_states[it1->first] = eq_s;
                }else{
                    eq_states[it1->first].push_back(it2->first);
                }
                //Als er nog geen andere staten zijn die equivalent zijn met it2->first.
                if(eq_states.find(it2->first) == eq_states.end()){
                    vector<string> eq_s = {it1->first, it2->first};
                    eq_states[it2->first] = eq_s;
                }else{
                    eq_states[it2->first].push_back(it1->first);
                }
            }
        }
    }

    map<string, vector<string>> new_states;

    eqStatesToOne(eq_states, new_states);

    map<string, State*> minimizedStates;
    map<string, State*> transitionMap;  //Map die de transitie bijhoud van de oude staten naar de nieuwe aangemaakte staten.

    for(auto it:new_states){
        bool accept = false;
        bool starting = false;
        for(auto it1:it.second){
            if(!accept) {
                accept = states[it1]->is_accept();
            }
            if(!starting) {
                starting = states[it1]->isStarting();
            }
        }
        //Nieuwe staat van equivalente staten wordt aangemaakt.
        State* n_state = new State(starting,it.first,accept);
        minimizedStates[it.first] = n_state;
        for(auto it1:it.second){
            //Alle staten van de oude staten die in deze staten zitten worden inde transitie map gestoken.
            transitionMap[it1] = n_state;
        }
    }
    for(auto it:stateNames){
        bool accept = false;
        bool starting = false;
        if(!accept) {
            accept = states[it]->is_accept();
        }
        if(!starting) {
            starting = states[it]->isStarting();
        }
        string new_name = "{" + it + "}";
        //Nieuwe staat voor de staat die onderscheidbaar is van alle andere.
        State* n_state = new State(starting,new_name,accept);
        minimizedStates[it] = n_state;
        transitionMap[it] = n_state;
    }

    for(auto it:transitionMap){
        //De transities worden aangemaakt voor elke input character.
        for(auto c:alphabet){
            string to= states[it.first]->goesTo(c);
            it.second->addTransition(c, transitionMap[to]);
        }
    }


    DFA minimized(minimizedStates,alphabet);

    // Voor tijd te bepalen
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    time = duration.count();

    return minimized;

}

int sommatie(int i){
    if (i > 1){
        return i + sommatie(i - 1);
    }else{
        return 1;
    }
}

void DFA::distinguisible(string A, string B, map<string, map<string ,char>>& table, map<string, State*>& ss) {
    for (int i=0; i!=alphabet.size(); i++){
        //de paar van staten na het inlezen van een input character uit de oeerspronkelijke paar.
        State* s1 = ss[ss[A]->goesTo(alphabet.at(i))];
        State* s2 = ss[ss[B]->goesTo(alphabet.at(i))];
        string n1 = s1->getName();
        string n2 = s2->getName();
        char x;
        //Checken of de nieuwe paar onderscheidbaar is in de tabel.
        if (table.find(n1) != table.end() and table[n1].find(n2) != table[n1].end()){
            x = table[n1][n2];
        }else{
            x = table[n2][n1];
        }
        // Als de nieuwe paar onderscheidbaar is, dan wordt de oorspronkelijke paar ook onderscheidbaar.
        if(x == 'X'){
            table[A][B] = 'X';
        }
    }
}

void DFA::tablePrinter(map<string ,map<string ,char>>& table, map<string, State*>& statess) {

    //Itterator voor he printen van de onderste rij van de staten.
    auto it22 = statess.end();
    it22--;

    for(auto it1 = table.begin(); it1 != table.end(); it1++){
        //Als de staat de eerste staat zou zijn wordt deze niet afgedrukt als een rij.
        if(it1->first == statess.begin()->first) {
            continue;
        }else{
            cout << it1->first << '\t';
        }
        //afdrukken van de kruisjes of leeg
        for(auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            cout << it2->second << '\t';
        }
        cout << endl;
    }
    cout << '\t';
    //Afdrukken van de kolommen van de staten.
    for(auto it = statess.begin(); it != it22; it++){
        cout << it->first << '\t';
    }
    cout << endl;
}

void DFA::eqStatesToOne(map<string, vector<string>>& states, map<string, vector<string>>& new_states ) {

    for(auto it1:states){
        sort(it1.second.begin(), it1.second.end());
        string nameNewState = "{";
        for(int i = 0; i<it1.second.size(); i++){
            if (i == it1.second.size()-1){
                nameNewState = nameNewState + it1.second.at(i) + "}";
                break;
            }
            nameNewState = nameNewState + it1.second.at(i) + ", ";
        }
        //Als er nog geen staat bestaat met deze naam
        if(new_states.find(nameNewState) == new_states.end()){
            new_states[nameNewState] = it1.second;
        }
    }
}

bool DFA::operator==(const DFA &d) {

    map<string, State*> allStates;
    allStates.insert(states.begin(), states.end());
    //Alle staten worden samengenomen
    for (auto s:d.states){
        if(allStates.find(s.first) == allStates.end()){
            allStates[s.first] = s.second;
        }else{  //Indien de twee automaten staten met dezelfde namen bevatten wordt er een "-" achrer de naam toegevoegd
                // zodat deze staten onderscheid kunnen worden door de TFA
            string newName = s.first + "-";
            s.second->changeName(newName);
            allStates[newName] = s.second;
        }
    }

    map<string, map<string, char>> table;

    TFA(table, allStates);  //Uitvoren van TFA

    for(auto it1 = table.begin(); it1 != table.end(); it1++){
        for(auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            //Als de twee startstaten niet equivalent zijn...
            if(allStates[it1->first]->isStarting() and allStates[it2->first]->isStarting() and it2->second == '-'){
                tablePrinter(table, allStates);
                return true;
            }
            //Als de twee startstaen equivalent zijn...
            else if(allStates[it1->first]->isStarting() and allStates[it2->first]->isStarting() and it2->second == 'X'){
                tablePrinter(table, allStates);
                return false;
            }
        }
    }
}

void DFA::TFA(map<string, map<string, char>> &table, map<string, State*>& mapOfStates) {

    int b = 1;

    //Aanmaak van een lege tabel
    auto it11 = mapOfStates.begin();
    it11++;
    auto it22 = mapOfStates.end();
    it22--;
    for(map<string, State*>::iterator it1 = it11; it1 != mapOfStates.end(); it1++){
        map<string,char> row;
        int bb=1;
        for(map<string, State*>::iterator it2 = mapOfStates.begin(); it2 != it22; it2++){
            row[it2->first] = '-';
            bb++;
            if (bb>b){
                break;
            }
        }
        table[it1->first] = row;
        b++;
    }

    //Aanduiden van alle niet-equivalente staten.
    for(auto it1 = table.begin(); it1 != table.end(); it1++){
        State* s1 = mapOfStates[it1->first];
        for(auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            State* s2 = mapOfStates[it2->first];
            if ((!s1->is_accept() and s2->is_accept()) or (s1->is_accept() and !s2->is_accept())){
                table[it1->first][it2->first]= 'X';
            }
        }
    }

    //Checken van of de andere staten onderscheinbaar zijn.
    for (int i=0; i < sommatie(mapOfStates.size()); i++){
        for(auto it1 = table.begin(); it1 != table.end(); it1++){
            for(auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
                distinguisible(it1->first, it2->first, table, mapOfStates);
            }
        }
    }
}

void DFA::printTable() {
    tablePrinter(TFA_table, states);
}

const map<string, State *> &DFA::getStates() const {
    return states;
}

void DFA::setStates(map<string, State *> &newStates) {
    states = newStates;
}

const string &DFA::getStartState() const {
    return start_state;
}

vector<State *> DFA::getAcceptingStates() const {
    vector<State*> accepting_states = {};

    // Over alle states loopen
    for (const auto &pair : getStates())
    {
        // Als state accepting is ==> toevoegen aan vector
        if (pair.second->is_accept())
        {
            accepting_states.push_back(pair.second);
        }
    }
    return accepting_states;
}

void DFA::renameStates() {
    int asciiValue = 65;    //ASCII waarde van hoofletter A.

    map<string, State*> newNameStates;  //map voor de staten met nieuwe namen.
    int alfabetRound = 0;
    for(auto state:states){
        string newName = "";
        newName += char(asciiValue);
        newName += to_string(alfabetRound);
        if(state.first == start_state) {
            start_state = newName;
        }
        if(state.first == current){
            current = newName;
        }
        state.second->setName(newName);
        newNameStates[newName] = state.second;

        if(asciiValue < 90) {
            asciiValue++;
        }else{
            asciiValue = 65;
            alfabetRound++;
        }
    }
    states.clear();
    states = newNameStates;
}

const string &DFA::getCurrentState() const {
    return current;
}

long DFA::getMemory(vector<long> &memories) const {
    long aantal_bytes = 0;

    // Startstate = string
    aantal_bytes += sizeof(getStartState());

    // Current = string
    aantal_bytes += sizeof(getCurrentState());

    // Alphabet = chars
    for (char letter : getAlphabet()) aantal_bytes += sizeof(letter);

    // TFA_table
    for (auto pair : TFA_table)
    {
        aantal_bytes += sizeof(pair.first);
        for (auto pair1 : pair.second)
        {
            aantal_bytes += sizeof(pair1.first);
            aantal_bytes += sizeof(pair1.second);
        }
    }

    // States
    for (auto pair2 : getStates())
    {
        aantal_bytes += sizeof(pair2.first);
        aantal_bytes += sizeof(pair2.second->isStarting());
        aantal_bytes += sizeof(pair2.second->is_accept());
        aantal_bytes += sizeof(pair2.second->getName());
        aantal_bytes += sizeof(pair2.second->isState());
        for (auto pair3 : pair2.second->getTTo())
        {
            aantal_bytes += sizeof(pair3.first);
        }
    }
    memories.push_back(aantal_bytes);
    return aantal_bytes;
}

