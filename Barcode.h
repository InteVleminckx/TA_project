//
// Created by inte.vleminckx on 17/05/2021.
//

#ifndef PROJECTTA_BARCODE_H
#define PROJECTTA_BARCODE_H
#include <iostream>
#include <vector>

using namespace std;

//Class structuur van "Node's" / stukken code van de RE
//Als insperatie van het examen Inleiding Programmeren 2020
class Code {
protected:
    string fType;
public:

    virtual string getType();
};

class VarCode: public Code {
    char fName;

public:

    VarCode(char input);

};


class Concatenatie: public Code {

    Code* fLeftOperator;
    Code* fRightOperator;

public:

    Concatenatie(Code* left, Code* right);


};

class Union: public Code {
    Code* fLeftOperator;
    Code* fRightOperator;

public:

    Union(Code* left, Code* right);


};

class KleeneClosure: public Code {

    Code* fOperator;

public:
    KleeneClosure(Code* string);

};



class Barcode {

    Code* parseRE(string &RE);
    void placeByConcatenateAPoint(string &RE);


public:
    string createBarcode(string &RE);

};


#endif //PROJECTTA_BARCODE_H
