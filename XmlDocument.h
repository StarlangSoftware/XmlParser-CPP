//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#ifndef XMLPARSER_XMLDOCUMENT_H
#define XMLPARSER_XMLDOCUMENT_H
#include <string>
#include "XmlElement.h"

using namespace std;

class XmlDocument {
private:
    string fileName;
    XmlElement* root;
public:
    XmlDocument(string fileName);
};


#endif //XMLPARSER_XMLDOCUMENT_H
