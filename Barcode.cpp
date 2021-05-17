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

        //We controlleren eerst op de kleene star, we kijken dus of er achteraan een * staat
        if (re[re.size()-1] == '*')
        {
            //We maken een KleenClosure node aan met alles dat voor de string staat
            //Bij de KleenStar staat ook haakjes deze verwijderen we ineens

            string reWithoutKleene = re.substr(1, re.size()-3);
            return new KleeneClosure(parseRE(reWithoutKleene));
        }

        /**
         * Omdat onze re uit haakjes kan staan maken we het ons makkelijker om deze te verwijderen als het mogelijk is
         * Als we een re van de vorm (1+0) hebben bijvoorbeeld kunnen we deze verwijderen en heeft het verder geen gevolgen.
         * Als we een re van de vorm (1+0)(0+11) hebben bijvoorbeeld kun we deze niet verwijderen want er is nog een concatenatie tussen die 2 groepen van haakjes
         */

        //We controlleren dus eerst of er vanvoor en vanachter een haakje staat in de re.
        if (re[0] == '(' && re[re.size()-1] == ')')
        {
            //Nu moeten we nog controlleren of er geen andere haakjes in de formule staan
            bool clearHaakjes = true;
            for (int i = 1; i < re.size()-1; ++i)
            {

                if (re[i] == '(' || re[i] == ')')
                {
                    clearHaakjes = false;
                    break;
                }
            }

            if (clearHaakjes) re = re.substr(1, re.size()-2);
        }

        /**
         * Nu de haakjes al dan niet zijn verwijderd moeten we opzoek gaan naar de operator
         * Dit kan enkel nog de concatenatie of de union zijn
         * union wordt herkend door de +
         * en concatenatie is er wanneer er 2 op eenvolgende variable achter elkaar komen
         * of wanneer er een '(' volgt na er een ')' is geweest
         *
         * Bij de union moeten we wel opletten want als we van de vorm (1+0)(0+1) hebben dan is het een concatenatie
         * maar dan mogen we de + niet herkennen dus vanaf we een haakje tegen komen mogen we niet verder zoeken naar een operator
         * tot we gesloten haakje tegenkomen
         */

        bool seenHaakje = false;
        char prevLetter = ' ';
        string beforeOperator;
        string afterOperator;
        string operatorName;
        bool foundOperator = false;

        for (char letter : re)
        {
            if (!foundOperator)
            {
                //Als we geen haakje tegenkomen kunnen we verder zoeken naar een operator
                if (!seenHaakje)
                {
                    if (letter == '(') seenHaakje = true;

                    if (prevLetter == ')')
                    {
                        foundOperator = true;
                        operatorName = "Concatenatie";
                    }

                    else if ((prevLetter == '1' && letter == '0') || (prevLetter == '1' && letter == '1') || (prevLetter == '1' && letter == '(') ||
                             (prevLetter == '0' && letter == '0') || (prevLetter == '0' && letter == '1') || (prevLetter == '0' && letter == '('))
                    {
                        foundOperator = true;
                        operatorName = "Concatenatie";
                    }


                    else if (letter == '+')
                    {
                        foundOperator = true;
                        operatorName = "Union";
                    }

                }
                else if (letter == ')') seenHaakje = false;


                prevLetter = letter;

                if (!foundOperator) beforeOperator.push_back(letter);
                else if (foundOperator && operatorName == "Concatenatie") afterOperator.push_back(letter);
            }

            else if (!operatorName.empty())
            {
                afterOperator.push_back(letter);
            }

        }

        //Als het een union is
        if (operatorName == "Union") return new Union(parseRE(beforeOperator), parseRE(afterOperator));

        //Anders is het een concatenatie
        else return new Concatenatie(parseRE(beforeOperator), parseRE(afterOperator));

    }
}
