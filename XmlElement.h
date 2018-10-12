//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#ifndef XMLPARSER_XMLELEMENT_H
#define XMLPARSER_XMLELEMENT_H
#include <string>
#include <vector>
#include "XmlAttribute.h"

using namespace std;

class XmlElement {
private:
    string name;
    string pcData;
    vector<XmlAttribute> attributes;
    XmlElement* parent;
    XmlElement* child;
    XmlElement* sibling;
};


#endif //XMLPARSER_XMLELEMENT_H
