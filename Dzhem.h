// Created by Dzhem Myumyun on 09/05/2021.
//

#ifndef PROJECTTA_DZHEM_H
#define PROJECTTA_DZHEM_H

#include "AlgoritmesControlesysteem/State.h"
#include "AlgoritmesControlesysteem/RE.h"
#include "AlgoritmesControlesysteem/json.hpp"
#include "AlgoritmesControlesysteem/ENFA.h"
#include "AlgoritmesControlesysteem/DFA.h"
#include "Datastructuur.h"
#include <string>

using namespace std;



//feature7: Controle systeem voor de net genereerde RE voor een bestemming om te controleren of deze uniek is en dus de
//          doorsnede met de bestaande RE's leeg is.

class Dzhem {

};

/**
 * Deze functie zal controleren of de gegeven RE een geldige RE is voor een nieuwe bestemming.
 * @param RE: de nieuw gegenereerde RE.
 * @param bestemmingen: Datastructuur met alle bestaande bestemmingen met elks een unieke RE.
 * @return: true of false;
 */
bool controleSysteem(string& RE, Datastructuur& bestemmingen);


#endif //PROJECTTA_DZHEM_H
