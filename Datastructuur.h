//
// Created by inte.vleminckx on 6/05/2021.
//

#ifndef PROJECTTA_DATASTRUCTUUR_H
#define PROJECTTA_DATASTRUCTUUR_H

#include <iostream>


using  namespace  std;

class Node
{

    int fKey;
    string fValue;

public:

    Node(int key, const string &value);
    int getKey();
    string getValue();
};


class Datastructuur {

    Node* fRoot = nullptr;
    Datastructuur* fParent = nullptr;
    Datastructuur* fLeftChild = nullptr;
    Datastructuur* fRightChild = nullptr;

    void setParent(Datastructuur * parent);
    void setLeftChild(Datastructuur * left);
    void setRightChild(Datastructuur * right);

    Datastructuur* getParent();
    Datastructuur* getLeftChild();
    Datastructuur* getRightChild();

    Datastructuur(Node* root);

    Datastructuur* getInorderSuccessor();

public:

    Datastructuur();

    bool insert(Node* object);

    bool deleteNode(int key);

    pair<bool, string> getValue(int key);


};


#endif //PROJECTTA_DATASTRUCTUUR_H
