//
// Created by inte.vleminckx on 6/05/2021.
//

#ifndef PROJECTTA_DATASTRUCTUUR_H
#define PROJECTTA_DATASTRUCTUUR_H

#include <iostream>
#include "Bestemming.h"
#include "vector"

using  namespace  std;

class Node
{
private:
    string fKey;
    Bestemming* fObject;


public:

    /**
     * @functie: Node
     * Constructor voor een node aan te maken, deze krijgt een bestemming binnen en haalt daar
     * de nodige parameters uit.
     * @param bestemming: bevat de naam van een bestemming en de regex voor de bijhorende halte.
     */
    Node(Bestemming &bestemming);

    /**
     * @functie: getKey
     * Deze functie geeft de zoeksleutel van een node terug, in dit geval de naam van een bestemming
     * @return : string, de zoeksleutel.
     */
    string getKey();

    /**
     * @functie: getObject
     * Deze functie geeft de bestemming zelf terug te mee opgeslagen zit in de node.
     * @return : Bestemming, de bestemming.
     */
    Bestemming* getObject();
};


class Datastructuur {

    Node* fRoot = nullptr;
    Datastructuur* fParent = nullptr;
    Datastructuur* fLeftChild = nullptr;
    Datastructuur* fRightChild = nullptr;


    /**
     * @functie: Datastructuur
     * Dit is de constructor voor een nieuwe deelboom aan te maken.
     * @param root: De node die gebruikt wordt om een deelboom aan te maken.
     */
    Datastructuur(Node* root);

    /**
     * @functie: setParent
     * Deze functie kent een parent toe aan een deelboom
     * @param parent: is de parent van de deelboom
     */
    void setParent(Datastructuur* parent);

    /**
     * @functie: setLeftChild
     * Deze functie kent een linkerdeelboom toe aan de boom
     * @param left: is de linkerdeelboom
     */
    void setLeftChild(Datastructuur* left);

    /**
     * @functie: setRightChild
     * Deze functie kent een rechterdeelboom toe aan de boom
     * @param left: is de rechterdeelboom
     */
    void setRightChild(Datastructuur* right);

    /**
     * @functie: getParent
     * Deze functie geeft de parent van een deelboom terug.
     * @return Datastructuur: de parent van een deelboom.
     */
    Datastructuur* getParent();

    /**
     * @functie: getLeftChild
     * Deze functie geeft de linkerdeelboom terug.
     * @return Datastructuur: de linkerdeelboom.
     */
    Datastructuur* getLeftChild();

    /**
     * @functie: getRightChild
     * Deze functie geeft de rechterdeelboom terug.
     * @return Datastructuur: de rechterdeelboom.
     */
    Datastructuur* getRightChild();

    /**
     * @functie: getInorderSuccessor
     * Deze functie zoekt naar de inordersuccessor van een node in de tree
     * @return: Datastructuur, deze is de deelboom van de inordersuccesor.
     */
    Datastructuur* getInorderSuccessor();

public:

    /**
     * @functie: Datastructuur
     * Dit is de constructor voor een nieuwe datastructuur aan te maken.
     */
    Datastructuur();

    /**
     * @functie: insert
     * Deze functie voegt nieuwe node's toe aan onze datastructuur.
     * @param object: een nieuwe node.
     * @return: bool, true als deze is toegevoegd. False als deze niet is toegevoegd.
     */
    bool insert(Node* object);

    /**
     * @functie: deleteNode
     * Deze functie verwijderd bestemmingen uit onze datastructuur.
     * @param naamBestemming: de van de bestemming die verwijderd moet worden.
     * @return: bool, true als deze verwijderd is. False als deze niet is verwijderd.
     */
    bool deleteNode(string naamBestemming);

    /**
     * @functie: getBestemming
     * Deze functie kijkt of de bestemming bestaat of niet in de datastructuur, als deze bestaat geeft het de regex er van terug.
     * @param bestemming: de bestemming die we willen zoeken.
     * @return bool, true als de bestemming bestaat. False als deze niet bestaat.
     * @return string, als de bestemming bestaat geeft het de regex van de bestemming.
     */
    pair<bool, Bestemming*> getBestemming(string naamBestemming);

    /**
     * @functie: inorderTraversal
     * Deze functie toont alle bestemming in gesorteerde volgorde.
     */
    void inorderTraversal(vector<Bestemming*> &bestemmingen);
};


#endif //PROJECTTA_DATASTRUCTUUR_H
