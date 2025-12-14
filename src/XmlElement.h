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
    [[nodiscard]] string getName() const;
    [[nodiscard]] string getPcData() const;
    [[nodiscard]] XmlElement* getFirstChild() const;
    [[nodiscard]] XmlElement* getNextSibling() const;
    [[nodiscard]] XmlElement* getParent() const;
    void setAttributeValue(const string& attributeName, const string& attributeValue);
    [[nodiscard]] string getAttributeValue(const string& attributeName) const;
    [[nodiscard]] int attributeSize() const;
    [[nodiscard]] XmlAttribute getAttribute(int index) const;
    void print(ofstream& outputStream, int level);
    void setNextSibling(XmlElement* _nextSibling);
    void setFirstChild(XmlElement* _firstChild);
    void addAttribute(const XmlAttribute& xmlAttribute);
    void setPcData(const string& _pcData);
    [[nodiscard]] bool hasAttributes() const;
};


#endif //XMLPARSER_XMLELEMENT_H
