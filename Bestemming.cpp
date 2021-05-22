//
// Created by Cem Tuncay on 06/05/2021.
//

#include "Bestemming.h"

#include <utility>

Bestemming::Bestemming(string naam, string RegEx) {
    fNaam = std::move(naam);
    fRegex = std::move(RegEx);
}

void Bestemming::setName(string naam) {
    fNaam = naam;
}

string Bestemming::getName() {
    return fNaam;
}

void Bestemming::setRegex(string RegEx) {
    fRegex = RegEx;
}

string Bestemming::getRegex() {
    return fRegex;
}

void Bestemming::setDFA(DFA &dfaToCopy) {
    dfa = DFA(dfaToCopy);
}

DFA &Bestemming::getDFA() {
    return dfa;
}


Bestemming::Bestemming() = default;
