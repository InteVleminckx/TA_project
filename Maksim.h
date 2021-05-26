//
// Created by Maksim Karnaukh on 5/05/2021.
//

#ifndef PROJECTTA_MAKSIM_H
#define PROJECTTA_MAKSIM_H
#include <iostream>
#include <string>
#include <fstream>
#include "vector"
#include <stdlib.h>
#include <time.h>

#include "Dzhem.h" //include voor controlesysteem
#include "Datastructuur.h" //tijdelijke include, vervanging woord de dergelijke opslag van de bestemmingen.



using namespace std;

// Zaken die moeten gedaan worden:
// - Omzetten van string geaccepteerd door een RE naar barcode
// - Genereren van een RE

// - feature8: Als bijhorende feature kunnen we wanneer de RE niet geldig is, een geldige RE genereren
//   en deze teruggeven. We kunnen dit doen door telkens de doorsnede te nemen met alle bestaande RE’s en
//   deze allemaal leeg zijn hebben we een nieuwe geldige RE gegenereerd.
// - feature9: We kunnen een functie toevoegen die een overzicht van alle bestemmingen en RE’s weergeeft in een html bestand.

class Maksim {
public:


    void stringToBarcode(string &str);

    string generateRE(Datastructuur& data, vector<long>& timeBrz, vector<long>& timeTFA, vector<long>& memoryBRZ,
                      vector<long>& memoryTFA,Bestemming& best, int numberOfIterations = 0);

    string chooseOperationFirstTime(bool isConcatOnly);

    string chooseOperation(string &deelRegex, bool isConcatOnly);

    string getRandomString(int nr_iterations, bool isConcatOnly);

    void createHTMLFile(Datastructuur &datastructuur);
};

////// test datastructuur ////
//bool alfabet0 = false;
//bool alfabet1 = false;
//bool alfabet2 = true;
////srand ((int)time(NULL));
//
//if (alfabet0) {
//Datastructuur datastructuur0;
//Bestemming best; best.setName("aa"); best.setRegex("0"); Node* node = new Node(best);
//Bestemming best1; best1.setName("ab"); best1.setRegex("01"); Node* node1 = new Node(best1);
//Bestemming best2; best2.setName("bb"); best2.setRegex("10"); Node* node2 = new Node(best2);
//Bestemming best3; best3.setName("bc"); best3.setRegex("0+1"); Node* node3 = new Node(best3);
//Bestemming best4; best4.setName("cc"); best4.setRegex("0*"); Node* node4 = new Node(best4);
//Bestemming best5; best5.setName("cd"); best5.setRegex("(0+1)0"); Node* node5 = new Node(best5);
//Bestemming best6; best6.setName("dd"); best6.setRegex("1(0+1)0"); Node* node6 = new Node(best6);
//
//datastructuur0.insert(node);
//cout << "inorder: " << endl;
//datastructuur0.inorderTraversal();
//cout << endl;
//pair<bool, string> tuple = datastructuur0.getBestemming(best);
//cout << "(" << tuple.first << "," << tuple.second << ")" << endl;
//datastructuur0.deleteNode(best);
//cout << "inorder: " << endl;
//datastructuur0.inorderTraversal(); //// tot hier goed
//cout << endl;
//
////// test faalt hier
////        tuple = datastructuur0.getBestemming(best);
////        cout << "(" << tuple.first << "," << tuple.second << ")" << endl;
//////
//datastructuur0.insert(node1);
//datastructuur0.insert(node4);
//datastructuur0.insert(node2);
//datastructuur0.insert(node6);
//datastructuur0.insert(node5);
//datastructuur0.insert(node3);
//
//cout << "inorder: " << endl;
//datastructuur0.inorderTraversal(); //// tot hier goed
//cout << endl;
//
//datastructuur0.deleteNode(best1);
//datastructuur0.deleteNode(best3);
//datastructuur0.deleteNode(best5); //// tot hier goed
//
//Bestemming best7; best7.setName("ff"); best7.setRegex("010"); Node* node7 = new Node(best7);
//Bestemming best8; best8.setName("uu"); best8.setRegex("0110"); Node* node8 = new Node(best8);
//Bestemming best9; best9.setName("hj"); best9.setRegex("1010"); Node* node9 = new Node(best9);
//Bestemming best10; best10.setName("jh"); best10.setRegex("0+110"); Node* node10 = new Node(best10);
//Bestemming best11; best11.setName("vv"); best11.setRegex("0*10"); Node* node11 = new Node(best11);
//Bestemming best12; best12.setName("gg"); best12.setRegex("(0+1)010"); Node* node12 = new Node(best12);
//Bestemming best13; best13.setName("oo"); best13.setRegex("1(0+1)010"); Node* node13 = new Node(best13);
//
//datastructuur0.insert(node7);
//datastructuur0.insert(node8);
//datastructuur0.insert(node9);
//datastructuur0.insert(node10);
//datastructuur0.insert(node11);
//datastructuur0.insert(node12);
//datastructuur0.insert(node13); //// tot hier goed (alle parent pointers kloppen ook)
//
//cout << "inorder: " << endl;
//datastructuur0.inorderTraversal(); //// tot hier goed
//cout << endl;
//
//datastructuur0.deleteNode(best4); // deleten van root
////// tot hier goed
//cout << "inorder: " << endl;
//datastructuur0.inorderTraversal(); //// tot hier goed (de inorder traversal functie werkt ook zwz goed, dus ik zal die niet meer aanroepen).
//cout << endl;
//
//datastructuur0.deleteNode(best7); // deleten van interne node
//datastructuur0.deleteNode(best10); // deleten van interne node
//datastructuur0.deleteNode(best6); // deleten van interne node
//datastructuur0.deleteNode(best12); // deleten van blad
////// tot hier goed
//// root = cc, {L = bb}, {R = uu: {L = hj:R = oo}, {R = vv}}
//
//Bestemming best14; best14.setName("ko"); best14.setRegex("0101001"); Node* node14 = new Node(best14);
//Bestemming best15; best15.setName("op"); best15.setRegex("01010011"); Node* node15 = new Node(best15);
//Bestemming best16; best16.setName("nn"); best16.setRegex("1001010"); Node* node16 = new Node(best16);
//Bestemming best17; best17.setName("bh"); best17.setRegex("010100110"); Node* node17 = new Node(best17);
//Bestemming best18; best18.setName("yt"); best18.setRegex("01010101001110"); Node* node18 = new Node(best18);
//Bestemming best19; best19.setName("wwz"); best19.setRegex("010101010101101"); Node* node19 = new Node(best19);
//Bestemming best20; best20.setName("xr"); best20.setRegex("01011010010101110"); Node* node20 = new Node(best20);
//
//datastructuur0.insert(node14);
//datastructuur0.insert(node15);
//datastructuur0.insert(node16);
//datastructuur0.insert(node17);
//datastructuur0.insert(node18);
//datastructuur0.insert(node19);
//datastructuur0.insert(node20);
////// tot hier goed
//
//
//}
//
//if (alfabet1) {
//Datastructuur datastructuur1;
//
//Bestemming best; best.setName("oooo"); Node* node = new Node(best); datastructuur1.insert(node);
//Bestemming best1; best1.setName("gggg"); Node* node1 = new Node(best1); datastructuur1.insert(node1);
//Bestemming best2; best2.setName("iiii"); Node* node2 = new Node(best2); datastructuur1.insert(node2);
//Bestemming best3; best3.setName("hhhh"); Node* node3 = new Node(best3); datastructuur1.insert(node3);
//Bestemming best4; best4.setName("pppp"); Node* node4 = new Node(best4); datastructuur1.insert(node4);
//Bestemming best5; best5.setName("uuuu"); Node* node5 = new Node(best5); datastructuur1.insert(node5);
//Bestemming best6; best6.setName("ffff"); Node* node6 = new Node(best6); datastructuur1.insert(node6);
//Bestemming best7; best7.setName("bbbb"); Node* node7 = new Node(best7); datastructuur1.insert(node7);
//Bestemming best8; best8.setName("aabb"); Node* node8 = new Node(best8); datastructuur1.insert(node8);
//Bestemming best9; best9.setName("gggg"); Node* node9 = new Node(best9); datastructuur1.insert(node9); // bestaat al in de boom //// returnt false => goed
//Bestemming best10; best10.setName("aahh"); Node* node10 = new Node(best10); datastructuur1.insert(node10);
//Bestemming best11; best11.setName("qqqq"); Node* node11 = new Node(best11); datastructuur1.insert(node11);
//Bestemming best12; best12.setName("dddd"); Node* node12 = new Node(best12); datastructuur1.insert(node12);
//Bestemming best13; best13.setName("tttt"); Node* node13 = new Node(best13); datastructuur1.insert(node13);
//Bestemming best14; best14.setName("iioo"); Node* node14 = new Node(best14); datastructuur1.insert(node14);
//Bestemming best15; best15.setName("kkkk"); Node* node15 = new Node(best15); datastructuur1.insert(node15);
//Bestemming best16; best16.setName("wwww"); Node* node16 = new Node(best16); datastructuur1.insert(node16);
//Bestemming best17; best17.setName("llll"); Node* node17 = new Node(best17); datastructuur1.insert(node17);
//Bestemming best18; best18.setName("eeee"); Node* node18 = new Node(best18); datastructuur1.insert(node18);
//Bestemming best19; best19.setName("nnnn"); Node* node19 = new Node(best19); datastructuur1.insert(node19);
//Bestemming best20; best20.setName("uuuu"); Node* node20 = new Node(best20); datastructuur1.insert(node20);
//Bestemming best21; best21.setName("xxxx"); Node* node21 = new Node(best21); datastructuur1.insert(node21);
//Bestemming best22; best22.setName("xxyy"); Node* node22 = new Node(best22); datastructuur1.insert(node22);
//Bestemming best23; best23.setName("xyxy"); Node* node23 = new Node(best23); datastructuur1.insert(node23);
//Bestemming best24; best24.setName("yxyx"); Node* node24 = new Node(best24); datastructuur1.insert(node24);
//Bestemming best25; best25.setName("ttdd"); Node* node25 = new Node(best25); datastructuur1.insert(node25);
//Bestemming best26; best26.setName("ffjj"); Node* node26 = new Node(best26); datastructuur1.insert(node26);
//Bestemming best27; best27.setName("ppmm"); Node* node27 = new Node(best27); datastructuur1.insert(node27);
//Bestemming best28; best28.setName("zzaa"); Node* node28 = new Node(best28); datastructuur1.insert(node28);
//Bestemming best29; best29.setName("aazz"); Node* node29 = new Node(best29); datastructuur1.insert(node29);
//Bestemming best30; best30.setName("rrbb"); Node* node30 = new Node(best30); datastructuur1.insert(node30);
//Bestemming best31; best31.setName("njnj"); Node* node31 = new Node(best31); datastructuur1.insert(node31);
//Bestemming best32; best32.setName("klop"); Node* node32 = new Node(best32); datastructuur1.insert(node32);
//Bestemming best33; best33.setName("woof"); Node* node33 = new Node(best33); datastructuur1.insert(node33);
//Bestemming best34; best34.setName("hiih"); Node* node34 = new Node(best34); datastructuur1.insert(node34);
//
//cout << "inorder: " << endl;
//datastructuur1.inorderTraversal(); //// tot hier goed
//cout << endl;
//
//}
//if (alfabet2) {
//
//std::vector<Node*> nodes;
//std::vector<Bestemming> bestemmingen;
//
//string alphabet = "abcdefghijklmnopqrstuvwxyz";
//for (auto i = 0; i < alphabet.size(); i++) {
//string letter;
//letter += alphabet[i];
//Bestemming best;
//best.setName(letter);
//best.setRegex(letter);
//Node* node = new Node(best);
//nodes.push_back(node);
//bestemmingen.push_back(best);
//}
//Datastructuur datastructuur;
//vector<int> bezochteNummers;
//for (auto i = 0; i < alphabet.size(); i++) {
//int random = rand() % 26;
//if (!std::count(bezochteNummers.begin(), bezochteNummers.end(), random)) {
//datastructuur.insert(nodes[random]);
//bezochteNummers.push_back(random);
//}
//}
//
//datastructuur.inorderTraversal();
//
////// deze testen hieronder gaan/zouden niet werken want de getBestemming functie werkt blijkbaar op de naam
///// van bestemming toen deze zelf werd geconstruct, en niet op de naam die door de setter aan de bestemming werd gegeven.
//
////        for (auto i = 0; i < alphabet.size(); i++) {
////            Bestemming best = bestemmingen[i];
////            pair<bool, string> tuple = datastructuur.getBestemming(best);
////            cout << "(" << tuple.first << "," << tuple.second << ")" << endl;
////        }
//pair<bool, string> tuple = datastructuur.getBestemming(bestemmingen[0]);
//cout << "(" << tuple.first << "," << tuple.second << ")" << endl;
//tuple = datastructuur.getBestemming(bestemmingen[1]);
//cout << "(" << tuple.first << "," << tuple.second << ")" << endl;
//tuple = datastructuur.getBestemming(bestemmingen[2]);
//cout << "(" << tuple.first << "," << tuple.second << ")" << endl;
//
//}


#endif //PROJECTTA_MAKSIM_H
