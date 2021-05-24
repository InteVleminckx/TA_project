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

void Bestemming::setBarcode(string &barcode) {

    fBarcodes.push_back(barcode);

}

string Bestemming::getBarcode() {

    //Als er nog geen tickets zijn gekocht bestaat er nog geen barcode dus returnen we een lege string.
    if (fBarcodes.empty()) return "";


    int barcodeNumber = rand() % fBarcodes.size();
    //We nemen een barcode uit de vector en verwijderen deze nadien.
    string barcode = fBarcodes[barcodeNumber];
    fBarcodes.erase(fBarcodes.begin()+barcodeNumber);

    return barcode;

}


Bestemming::Bestemming() = default;
