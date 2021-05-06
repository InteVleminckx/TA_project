//
// Created by Cem Tuncay on 06/05/2021.
//

#include "Bestemming.h"

Bestemming::Bestemming(string naam, string RegEx) {
    fNaam = naam;
    fRegex = RegEx;
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


Bestemming::Bestemming() = default;
