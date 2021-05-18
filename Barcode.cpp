//
// Created by inte.vleminckx on 17/05/2021.
//

#include "Barcode.h"


VarCode::VarCode(char input)
{
    fName = input;
    fType = "varCode";
}

string Code::getType() {return fType;}

Concatenatie::Concatenatie(Code *left, Code *right)
{
    fLeftOperator = left;
    fRightOperator = right;
    fType = "Concatenatie";
}

Union::Union(Code *left, Code *right)
{
    fLeftOperator = left;
    fRightOperator = right;
    fType = "Union";
}

KleeneClosure::KleeneClosure(Code *string)
{
    fOperator = string;
    fType = "KleeneClosure";
}

string Barcode::createBarcode(string &RE)
{
    string barcode;

    Code* parsedRE = parseRE(RE);



    return barcode;
}

Code *Barcode::parseRE(string &re) {


    //Controlleren eerst dat de re niet leeg is. Dit mag niet
    if (re.empty())
    {
        cout << "Lege regex bij het parsen." << endl;
        return nullptr;
    }

    /**
     * Als het geen lege is kan deze lengte 1 hebben of groter als lengte 1.
     * Als het lengte 1 is dan is het maar 1 variable en is geen operator.
     * Als het een grotere lengte heeft dan is er wel een operator aanwezig.
     */

    else if (re.size() == 1)
    {
        /**
         * We moeten nog wel altijd controlleren dat we een juiste invoer krijgen
         * Onze barcode bestaat uit 1'en en 0'en dat is in ons geval het alfabet
         * van de RE.
         * Als de string geen 1 of 0 bevat dan is het geen geldige RE.
         */

        if (re != "1" && re != "0")
        {
            cout << "Geen geldige string ingeven." << endl;
            return nullptr;
        }

        //Als het aanvaardt wordt kunnen we een stuk code al aanmaken.

        else return new VarCode(re[0]);
    }

    //Als de string groter als 1 is hebben we een samengestelde formule.

    else
    {
        /**
         * We kunnen hier 3 gevallen hebben:
         * Concatenatie
         * Union
         * Kleene Star
         */

        //We plaatsen eerst tussen elke concatenatie een punt, dit maakt het ons makkelijker om naar concatenatie te zoeken
        placeByConcatenateAPoint(re);

        //We controlleren dus eerst of er vanvoor en vanachter een haakje staat in de re.
        if (re[0] == '(' && re[re.size()-1] == ')')
        {
            //Nu moeten we nog controlleren of er geen andere haakjes in de formule staan
            bool clearHaakjes = true;
            for (int i = 1; i < re.size()-1; ++i)
            {
                if (re[i] == '(' || re[i] == ')') { clearHaakjes = false; break; }
            }

            if (clearHaakjes) re = re.substr(1, re.size()-2);
        }


        int haakjesClosed = 0;
        string leftCode, rightCode, tempLeft, tempRight;

        bool seenOperator = false;
        bool isUnion = false;

        for (int i = 0; i < re.size(); ++i)
        {

            //Haakjes open tellen er 1 bij op
            if (re[i] == '(') haakjesClosed++;

            //Haakjes toe trekken er 1 vanaf
            else if (re[i] == ')') haakjesClosed--;

            //Als alle haakjes die open zijn gedaan terug gesloten zijn kunnen we naar operatoren zoeken
            if (haakjesClosed == 0)
            {
                //Als we helemaal opt einde van de re zitten en er is nog geen andere operator gezien
                //En er is een kleene star dan kunnen we een kleene star toevoegen
                if (re[i] == '*' && i == re.size()-1 && !seenOperator)
                {
                    string reWithoutKleene = re.substr(1, re.size()-3);
                    return new KleeneClosure(parseRE(reWithoutKleene));
                }

                //Als we een '.' tegenkomen hebben we een concatenatie
                //We slagen de code op een temp string want we gaan nog verder zoeken naar een plus
                //en anders moeten we nog eens opnieuw gaan zoeken naar dit stuk van de string
                if (re[i] == '.'){ tempLeft = leftCode; seenOperator = true; }

                // Als we een '+' tegenkomen hebben we een unie
                // We zeggen dat we een unie hebben gevonden en moest er een concatenatie hiervoor gevonden zijn
                // is deze niet meer geldig.
                else if(re[i] == '+') { isUnion = true;seenOperator = true; }

            }

            //Nog geen operator gevonden pushen alles in het linkerdeel
            if (!seenOperator) leftCode.push_back(re[i]);

            //We weten dat het een unie is dus pushen alles in een string die het rechterdeel bevat
            else if (seenOperator && isUnion) rightCode.push_back(re[i]);

            //Als we een concatenatie hebben gevonden pushen we alles in een temp want we kunnen nog altijd een unie tegenkomen
            //ALs we dan nog een unie tegen komen vormen tempLeft en tempRight de linkerdeel van de code voor de '+'
            //en wordt rightCode het rechterdeel
            else if (seenOperator && !isUnion) tempRight.push_back(re[i]);

        }

        if (isUnion)
        {
            //moesten tempLeft en tempRight niet leeg zijn dan betekent dat we al eens een concatenatie zijn tegenkomen
            //moest dit niet het geval zijn dan, blijft leftCode gewoon leftCode
            if (!tempLeft.empty() && !tempRight.empty()) leftCode = tempLeft+tempRight;

            //We verwijderen de operator nog van de string
            rightCode = rightCode.substr(1, rightCode.size());
            return new Union(parseRE(leftCode), parseRE(rightCode));
        }

        else
        {
            //We stellen leftcode nog gelijk aan tempLeft
            leftCode = tempLeft;

            //We verwijderen de operator nog van de string
            rightCode = tempRight.substr(1, tempRight.size());

            return new Concatenatie(parseRE(leftCode), parseRE(rightCode));
        }
    }
}

void Barcode::placeByConcatenateAPoint(string &RE) {

    string newRE;

    if (RE[0] == '.') RE.substr(1, RE.size());

    char prevLetter;

    for (char i : RE)
    {
        if ((prevLetter == '1' && i == '1') || (prevLetter == '1' && i == '0') || (prevLetter == '1' && i == '(') ||
            (prevLetter == '0' && i == '1') || (prevLetter == '0' && i == '0') || (prevLetter == '0' && i == '(') ||
            (prevLetter == ')' && i == '1') || (prevLetter == ')' && i == '0') || (prevLetter == ')' && i == '(') ||
            (prevLetter == '*' && i == '1') || (prevLetter == '*' && i == '0') || (prevLetter == '*' && i == '('))
        {
            newRE.push_back('.');
        }
        newRE.push_back(i);
        prevLetter = i;
    }

    RE = newRE;
}