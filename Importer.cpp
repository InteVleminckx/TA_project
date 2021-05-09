#include "Importer.h"

/**
 * Functie die een xml-file gaat uitlezen en opslaan in onze eigen datastructuur
 * @param filename = naam van de xml-file die we willen uitlezen (type = string)
 * @return none (voorlopig)
 * @exceptions none
 *
 * OPM: datastructure wordt bij & doorgegeven, dit wil zeggen dat we zowel een lege structuur kunnen
 * toevoegen als het zogezegd de eerste keer is dat we een datastructuur maken of een reeds bestaande
 * structuur meegeven om bij deze structuur extra bestemmingen toe te voegen
 */
void Importer::readXMLFile(const string &filename, Datastructuur &datastructure) {
    TiXmlDocument doc;

    // Niet inleesbaar ==> error wegsturen via cerr
    if (!doc.LoadFile(filename.c_str())) {
        cerr << doc.ErrorDesc() << endl;
    }

    // Root eruithalen (is element met naam bestemmingen)
    TiXmlElement* root = doc.FirstChildElement();

    // Checken of de root bestaat
    if (root == NULL) {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
    }

    // Checken of naam van root "bestemmingen" is
    string rootName = root->Value();
    if (rootName != "bestemmingen") {
        cerr << "Hoofdtag is niet bestemmingen" << endl;
        doc.Clear();
    }

    // Loopen over alle childtags
    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

        // Checken of childtag "halte" heet
        string elemName = elem->Value();
        if (elemName != "halte") {
            cerr << "Naam van childtag is niet halte" << endl;
        }

        // Info tussen twee tags halen
        else {
            string info = elem->FirstChild()->ToText()->Value();
            Bestemming destination;
            destination.setName(info);

            // TODO: hier RE toevoegen gegenereerd door code van Maksim
            destination.setRegex("101010");

            Node* node = new Node(destination);
            datastructure.insert(node);
        }
    }
}
