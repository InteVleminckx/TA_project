//
// Created by inte.vleminckx on 17/05/2021.
//

#ifndef PROJECTTA_BARCODE_H
#define PROJECTTA_BARCODE_H
#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

//Class structuur van "Node's" / stukken code van de RE
//Als insperatie van het examen Inleiding Programmeren 2020
class Code {
protected:
    string fType;
public:

    /**
     * Geeft het type van operator terug.
     * @return: string, type van de operator.
     */
    virtual string getType();

    /**
     * Geeft de naam van de variable terug in ons het van is het een 1 of 0.
     * @return: char, naam van de variable.
     */
    virtual char getName(){return ' ';};

    /**
     * Geeft het linkerdeel voor de operator en het rechterdeel na de operator terug.
     * @return: pair<Code*, Code*>, linker-en rechterdeel string.
     */
    virtual pair<Code*, Code*> getLeftAndRightOperator(){return make_pair(nullptr, nullptr);};

    /**
     * Geeft de string die binnen de kleene closure staat.
     * @return: Code*, het deel binnen de kleene closure.
     */
    virtual Code* getKleeneClosure(){return nullptr;};

};

class VarCode: public Code {
    char fName;

public:

    /**
     * De constructor voor het toekennen van een variable.
     * @param input: de variable die geplaatst moet worden.
     */
    VarCode(char input);

    /**
     * Geeft de naam van de variable terug in ons het van is het een 1 of 0.
     * @return: char, naam van de variable.
     */
    char getName() override;

};


class Concatenatie: public Code {

    Code* fLeftOperator;
    Code* fRightOperator;

public:

    /**
     * Constructor voor een concatenatie, krijgt als type concatenatie en een linker en rechter Code*.
     * @param left: Het linkerdeel van de code voor de concatenatie.
     * @param right: Het rechterdeel van de code na de concatenatie.
     */
    Concatenatie(Code* left, Code* right);

    /**
     * Geeft het linkerdeel voor de operator en het rechterdeel na de operator terug.
     * @return: pair<Code*, Code*>, linker-en rechterdeel string.
     */
    pair<Code*, Code*> getLeftAndRightOperator() override;

};

class Union: public Code {
    Code* fLeftOperator;
    Code* fRightOperator;

public:

    /**
     * Constructor voor de unie, krijgt als type Union en een linker en rechter Code*.
     * @param left: Het linkerdeel van de code voor de unie.
     * @param right: Het rechterdeel van de code na de unie.
     */
    Union(Code* left, Code* right);

    /**
     * Geeft het linkerdeel voor de operator en het rechterdeel na de operator terug.
     * @return: pair<Code*, Code*>, linker-en rechterdeel string.
     */
    pair<Code*, Code*> getLeftAndRightOperator() override;
};

class KleeneClosure: public Code {

    Code* fOperator;

public:

    /**
     * Constructor voor de Kleene closure, krijgt als type KleeneClosure en Code*.
     * @param string: De code die bij de kleene closure hoort.
     */
    KleeneClosure(Code* string);

    /**
     * Geeft de string die binnen de kleene closure staat.
     * @return: Code*, het deel binnen de kleene closure.
     */
    Code* getKleeneClosure() override;
};



class Barcode {

    /**
     * Parsed een meegekregen re in deel stukken tot we een hele "boom" krijgen van verschillende operatoren + bijhorden codes.
     * @param RE: De re die geparsed moet worden.
     * @return: Code*, De geparsed code opgesplitst in allemaal verschillende delen.
     */
    static Code* parseRE(string &RE);

    /**
     * Plaatst waar over een concatenatie is een '.'.
     * @param RE: De RE waar we overal de punten gaan plaatsen.
     */
    static void placeByConcatenateAPoint(string &RE);

    /**
     * Maakt van de geparsed RE een barcode door deze te analyseren.
     * @param barcode: de string waar de nieuwe barcode wordt ingeschreven.
     * @param parsedRE: De geparsed RE.
     */
    static void generateBarcode(string &barcode, Code* parsedRE);

public:

    /**
     * Roept alle nodige functies aan om van een RE naar een barcode te gaan.
     * @param RE: De Re die geparsed moet worden.
     * @return: string, de barcode die gecreeerd is met de RE.
     */
    static string createBarcode(string RE);

};


#endif //PROJECTTA_BARCODE_H
