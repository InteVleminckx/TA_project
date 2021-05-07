#include "Importer.h"

/**
 * Functie die een xml-file gaat uitlezen en opslaan in onze eigen datastructuur
 * @param filename : naam van de xml-file die we willen uitlezen (type = string)
 * @return none (voorlopig)
 * @exceptions none
 */
void Importer::readXMLFile(const string &filename) {
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
            cout << info << endl;
            // TODO: deze info opslagen in eigen datastructuur
        }
    }
}
