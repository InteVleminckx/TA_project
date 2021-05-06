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

Bestemming Node::getObject() {
    return fObject;
}


Datastructuur::Datastructuur() = default;

Datastructuur::Datastructuur(Node *root){ this->fRoot = root;}

void Datastructuur::setParent(Datastructuur *parent)
{
    fParent = parent;
}

void Datastructuur::setLeftChild(Datastructuur *left)
{
    fLeftChild = left;
}

void Datastructuur::setRightChild(Datastructuur *right)
{
    fRightChild = right;
}

Datastructuur *Datastructuur::getParent() {return fParent;}

Datastructuur *Datastructuur::getLeftChild() {return fLeftChild;}

Datastructuur *Datastructuur::getRightChild() {return fRightChild;}

bool Datastructuur::insert(Node* object) {


    //bst is leeg
    if (this->fRoot == nullptr)
    {
        this->fRoot = object;
        this->setParent(nullptr);
        this->setLeftChild(nullptr);
        this->setRightChild(nullptr);
        return true;
    }

    //er bestaat al een node met deze key
    else if (this->getValue(object->getObject()).first)
    {
        return false;
    }

    //geen root en key bestaat nog niet
    else
    {
        //rechterkant
        if (object->getKey() > this->fRoot->getKey())
        {
            //nog geen rechterkind nieuwe bst aanmaken
            if (this->getRightChild() == nullptr)
            {
                this->setRightChild(new Datastructuur(object));
                this->getRightChild()->setParent(this);
                return true;
            }

            //opnieuw inserten in rechternode
            else
            {
                return this->getRightChild()->insert(object);
            }
        }

        //linkerkant
        else
        {
            //nog geen rechterkind nieuwe bst aanmaken
            if (this->getLeftChild() == nullptr)
            {
                this->setLeftChild(new Datastructuur(object));
                this->getLeftChild()->setParent(this);
                return true;
            }

                //opnieuw inserten in rechternode
            else
            {
                return this->getLeftChild()->insert(object);
            }
        }
    }
}

Datastructuur *Datastructuur::getInorderSuccessor() {

    //inorder bevindt zich in de rechterdeelboom
    if (this->getLeftChild() != nullptr)
    {
        return this->getLeftChild()->getInorderSuccessor();
    }

    //parent is inorder
    else
    {
        return this;
    }
}

bool Datastructuur::deleteNode(Bestemming &bestemming)
{

    if (this == nullptr)
    {
        return false;
    }

    else if (bestemming.getName() > this->fRoot->getKey())
    {
        return this->getRightChild()->deleteNode(bestemming);
    }

    else if (bestemming.getName() < this->fRoot->getKey())
    {
        return this->getLeftChild()->deleteNode(bestemming);
    }

    else
    {

        //geval geen kinderen enkel root en geen parent
        if (this->getLeftChild() == nullptr && this->getRightChild() == nullptr && this->getParent() == nullptr)
        {
            this->fRoot = nullptr;
            return true;
        }

        //geval geen kinderen enkel root en met parent
        else if (this->getLeftChild() == nullptr && this->getRightChild() == nullptr && this->getParent() != nullptr)
        {

            //linkerkind
            if (this->getParent()->getLeftChild() == this)
            {
                this->getParent()->setLeftChild(nullptr);
                return true;
            }
            //rechterkind
            else if (this->getParent()->getRightChild() == this)
            {
                this->getParent()->setRightChild(nullptr);
                return true;
            }
        }

        //Geval root met 1 kind
        //enkel rechterkind
        else if (this->getLeftChild() == nullptr)
        {
            this->fRoot = this->getRightChild()->fRoot;
            this->setLeftChild(this->getRightChild()->getLeftChild());
            this->setRightChild(this->getRightChild()->getRightChild());
            return true;
        }

        //enkel linkerkind
        else if (this->getRightChild() == nullptr)
        {
            this->fRoot = this->getLeftChild()->fRoot;
            this->setRightChild(this->getLeftChild()->getRightChild());
            this->setLeftChild(this->getLeftChild()->getLeftChild());
            return true;
        }

        //geval root met 2 kinderen
        //zoek inorder succesor. -> kleinste waarde in de rechterdeelboom
        //Wissel de root de met de inordersuccesor en delete dan de inordersuccessor

        else if (this->getLeftChild() != nullptr && this->getRightChild() != nullptr)
        {
            Node* succesor = this->getRightChild()->getInorderSuccessor()->fRoot;
            this->deleteNode(bestemming);
            this->fRoot = succesor;
        }
    }
}

pair<bool, string> Datastructuur::getValue(Bestemming bestemming) {

    if (bestemming.getName() > this->fRoot->getKey())
    {
        if (this->getRightChild() != nullptr) this->getRightChild()->getValue(bestemming);
        else return make_pair(false, "");
    }

    else if (bestemming.getName() < this->fRoot->getKey())
    {
        if (this->getLeftChild() != nullptr) this->getLeftChild()->getValue(bestemming);
        else return make_pair(false, "");
    }

    else if (bestemming.getName() == this->fRoot->getKey()) return make_pair(true, this->fRoot->getValue());

    return make_pair(false, "");
}

