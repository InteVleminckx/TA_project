//
// Created by inte.vleminckx on 6/05/2021.
//

#include "Datastructuur.h"

Node::Node(Bestemming &bestemming) {
    fKey = bestemming.getName();
    fValue = bestemming.getRegex();
    fObject = bestemming;
}

string Node::getKey() {return fKey;}

string Node::getValue() {return fValue;}

Bestemming Node::getObject() {return fObject;}

Datastructuur::Datastructuur() = default;

Datastructuur::Datastructuur(Node *root){ this->fRoot = root;}

void Datastructuur::setParent(Datastructuur *parent){fParent = parent;}

void Datastructuur::setLeftChild(Datastructuur *left){fLeftChild = left;}

void Datastructuur::setRightChild(Datastructuur *right){fRightChild = right;}

Datastructuur *Datastructuur::getParent() {return fParent;}

Datastructuur *Datastructuur::getLeftChild() {return fLeftChild;}

Datastructuur *Datastructuur::getRightChild() {return fRightChild;}

bool Datastructuur::insert(Node* object) {


    //Als de datastructuur nog geen waardes bevat.
    if (this->fRoot == nullptr)
    {
        this->fRoot = object;
        this->setParent(nullptr);
        this->setLeftChild(nullptr);
        this->setRightChild(nullptr);
        return true;
    }

    //Er bestaat al een node met dezelfde zoeksleutel in de datastructuur.
    else if (this->getBestemming(object->getObject()).first) return false;

    //De datastructuur is niet leeg en de zoeksleutel zit er nog niet in.
    else
    {
        //De nieuwe node komt rechts van de root.
        if (object->getKey() > this->fRoot->getKey())
        {
            //De huidige node heeft nog geen rechterdeelboom, de nieuwe node wordt dan de rechterdeelboom.
            if (this->getRightChild() == nullptr)
            {
                this->setRightChild(new Datastructuur(object));
                this->getRightChild()->setParent(this);
                return true;
            }

            //De huidige node heeft al wel een rechterdeelboom we gaan hierverder zoeken naar een lege plaats.
            else return this->getRightChild()->insert(object);
        }

        //De nieuwe node komt links van de root.
        else
        {
            //De huidige node heeft nog geen linkerdeelboom, de nieuwe node wordt dan de linkerdeelboom.
            if (this->getLeftChild() == nullptr)
            {
                this->setLeftChild(new Datastructuur(object));
                this->getLeftChild()->setParent(this);
                return true;
            }

           //De huidige node heeft al wel een linkerdeelboom we gaan hierverder zoeken naar een lege plaats.
            else return this->getLeftChild()->insert(object);
        }
    }
}

Datastructuur *Datastructuur::getInorderSuccessor() {

    //Er is nog een linkerdeelboom, dus de inorder is nog niet gevonden.
    if (this->getLeftChild() != nullptr) return this->getLeftChild()->getInorderSuccessor();

    //Er is geen linkerdeelboom meer dus we hebben de inordersuccessor gevonden.
    else return this;
}

bool Datastructuur::deleteNode(Bestemming &bestemming)
{

    //Als op de huidige positie nog geen deelboom aangemaakt is, dan betekent dat er nog geen node is toegevoegd
    //op de locatie waar we willen verwijderen dus dit object bestaat niet.
    if (this == nullptr) return false;

    //Als de zoeksleutel van de node die verwijderd moet worden groter is, moeten we verder gaan zoeken in de rechterdeelboom.
    else if (bestemming.getName() > this->fRoot->getKey()) this->getRightChild()->deleteNode(bestemming);

    //Als de zoeksleutel van de node die verwijderd moet worden kleiner is, moeten we verder gaan zoeken in de linkerdeelboom.
    else if (bestemming.getName() < this->fRoot->getKey()) this->getLeftChild()->deleteNode(bestemming);

    //Als het geen van deze bovenstaande is, betekent dat we de node hebben gevonden met de opgeven bestemming en kunnen we deze gaan verwijderen.
    else
    {
        //Geval geen kinderen enkel root en geen parent.
        if (this->getLeftChild() == nullptr && this->getRightChild() == nullptr && this->getParent() == nullptr)
        {
            this->fRoot = nullptr;
            return true;
        }

        //Geval geen kinderen enkel root en met parent.
        else if (this->getLeftChild() == nullptr && this->getRightChild() == nullptr && this->getParent() != nullptr)
        {
            //Linkerdeelboom
            if (this->getParent()->getLeftChild() == this) this->getParent()->setLeftChild(nullptr);

            //Rechterdeelboom
            else if (this->getParent()->getRightChild() == this) this->getParent()->setRightChild(nullptr);
        }

        //Geval root met 1 kind.
        //Er is enkel een rechterdeelboom.
        else if (this->getLeftChild() == nullptr)
        {
            this->fRoot = this->getRightChild()->fRoot;
            this->setLeftChild(this->getRightChild()->getLeftChild());
            this->setRightChild(this->getRightChild()->getRightChild());
            if (this->getLeftChild() != nullptr) this->getLeftChild()->setParent(this);
            if (this->getRightChild() != nullptr) this->getRightChild()->setParent(this);
        }

        //Er is enkel een linkerdeelboom.
        else if (this->getRightChild() == nullptr)
        {
            this->fRoot = this->getLeftChild()->fRoot;
            this->setRightChild(this->getLeftChild()->getRightChild());
            this->setLeftChild(this->getLeftChild()->getLeftChild());
            if (this->getLeftChild() != nullptr) this->getLeftChild()->setParent(this);
            if (this->getRightChild() != nullptr) this->getRightChild()->setParent(this);
        }

        //Geval root met 2 kinderen.

        //Zoek inorder succesor. -> kleinste waarde in de rechterdeelboom
        //Wissel de root de met de inordersuccesor en delete dan de inordersuccessor
        else if (this->getLeftChild() != nullptr && this->getRightChild() != nullptr)
        {
            Node* succesor = this->getRightChild()->getInorderSuccessor()->fRoot;
            Bestemming succ = Bestemming(succesor->getKey(), succesor->getValue());
            this->deleteNode(succ);
            this->fRoot = succesor;
        }
    }

    return true;
}

pair<bool, string> Datastructuur::getBestemming(Bestemming bestemming) {

    //Als de zoeksleutel groter is, zoeken we verder in de rechterdeelboom (Als deze bestaat).
    if (bestemming.getName() > this->fRoot->getKey())
    {
        //Rechterdeelboom bestaat.
        if (this->getRightChild() != nullptr) this->getRightChild()->getBestemming(bestemming);

        //Rechterdeelboom bestaat niet, dus gezochte node ook niet en returnen we false.
        else return make_pair(false, "");
    }

    //Als de zoeksleutel kleiner is, zoeken we verder in de linkerdeelboom (Als deze bestaat).
    else if (bestemming.getName() < this->fRoot->getKey())
    {
        //Linkerdeelboom bestaat.
        if (this->getLeftChild() != nullptr) this->getLeftChild()->getBestemming(bestemming);

        //Linkerdeelboom bestaat niet, dus gezochte node ook niet en returnen we false.
        else return make_pair(false, "");
    }

    //Als de zoeksleutel gelijk is, dan is de bestemming gevonden in de datastructuur en returnen we true + de value van de bestemming.
    else if (bestemming.getName() == this->fRoot->getKey()) return make_pair(true, this->fRoot->getValue());

    //Als zoeksleutel niet gevonden is, dan returnen we ook false. (Hier gaat het programma normaal gezien niet komen.)
    return make_pair(false, "");
}

void Datastructuur::inorderTraversal(vector<Bestemming> &bestemmingen) {

    if (fRoot != nullptr){
        if (this->getLeftChild() != nullptr)
        {
            this->getLeftChild()->inorderTraversal(bestemmingen);
        }

        cout << this->fRoot->getKey() << endl;
        bestemmingen.push_back(this->fRoot->getObject());

        if (this->getRightChild() != nullptr)
        {
            this->getRightChild()->inorderTraversal(bestemmingen);
        }
    }
}

