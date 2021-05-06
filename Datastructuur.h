//
// Created by inte.vleminckx on 6/05/2021.
//

#ifndef PROJECTTA_DATASTRUCTUUR_H
#define PROJECTTA_DATASTRUCTUUR_H

#include <iostream>
#include "Bestemming.h"

using  namespace  std;

class Node
{

    string fKey;
    string fValue;
    Bestemming fObject;


public:

    Node(Bestemming &bestemming);
    string getKey();
    string getValue();
    Bestemming getObject();
};


class Datastructuur {

    Node* fRoot = nullptr;
    Datastructuur* fParent = nullptr;
    Datastructuur* fLeftChild = nullptr;
    Datastructuur* fRightChild = nullptr;

    void setParent(Datastructuur* parent);
    void setLeftChild(Datastructuur* left);
    void setRightChild(Datastructuur* right);

    Datastructuur* getParent();
    Datastructuur* getLeftChild();
    Datastructuur* getRightChild();

    Datastructuur(Node* root);

    Datastructuur* getInorderSuccessor();

public:

    Datastructuur();

    bool insert(Node* object);

    bool deleteNode(Bestemming &bestemming);

    pair<bool, string> getValue(Bestemming bestemming);


};


#endif //PROJECTTA_DATASTRUCTUUR_H
