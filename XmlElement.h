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
    XmlElement* firstChild;
    XmlElement* nextSibling;
public:
    XmlElement(string name, XmlElement* parent, bool hasAttributes);
    ~XmlElement();
    string getName();
    string getPcData();
    XmlElement* getFirstChild();
    XmlElement* getNextSibling();
    XmlElement* getParent();
    void setAttributeValue(string attributeName, string attributeValue);
    string getAttributeValue(string attributeName);
    void print(ofstream& outputStream, int level);
    void setNextSibling(XmlElement* nextSibling);
    void setFirstChild(XmlElement* firstChild);
    void addAttribute(XmlAttribute xmlAttribute);
    void setPcData(string pcData);
    bool hasAttributes();
};


#endif //XMLPARSER_XMLELEMENT_H
