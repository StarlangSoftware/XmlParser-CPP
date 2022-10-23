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
    XmlElement(const string& name, XmlElement* parent);
    ~XmlElement();
    string getName() const;
    string getPcData() const;
    XmlElement* getFirstChild() const;
    XmlElement* getNextSibling() const;
    XmlElement* getParent() const;
    void setAttributeValue(const string& attributeName, const string& attributeValue);
    string getAttributeValue(const string& attributeName) const;
    int attributeSize() const;
    XmlAttribute getAttribute(int index) const;
    void print(ofstream& outputStream, int level);
    void setNextSibling(XmlElement* _nextSibling);
    void setFirstChild(XmlElement* _firstChild);
    void addAttribute(const XmlAttribute& xmlAttribute);
    void setPcData(const string& _pcData);
    bool hasAttributes() const;
};


#endif //XMLPARSER_XMLELEMENT_H
