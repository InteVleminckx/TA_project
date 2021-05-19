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

    virtual string getType();

    virtual char getName(){};

    virtual pair<Code*, Code*> getLeftAndRightOperator(){};

    virtual Code* getKleeneClosure(){};

};

class VarCode: public Code {
    char fName;

public:

    VarCode(char input);

    char getName() override;

};


class Concatenatie: public Code {

    Code* fLeftOperator;
    Code* fRightOperator;

public:

    Concatenatie(Code* left, Code* right);

    pair<Code*, Code*> getLeftAndRightOperator() override;

};

class Union: public Code {
    Code* fLeftOperator;
    Code* fRightOperator;

public:

    Union(Code* left, Code* right);

    pair<Code*, Code*> getLeftAndRightOperator() override;
};

class KleeneClosure: public Code {

    Code* fOperator;

public:

    KleeneClosure(Code* string);

    Code* getKleeneClosure() override;
};



class Barcode {

    Code* parseRE(string &RE);
    void placeByConcatenateAPoint(string &RE);
    void generateBarcode(string &re, Code* parsedRE);

public:
    string createBarcode(string &RE);

};


#endif //PROJECTTA_BARCODE_H
