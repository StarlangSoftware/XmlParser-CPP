//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#ifndef XMLPARSER_XMLATTRIBUTE_H
#define XMLPARSER_XMLATTRIBUTE_H
#include <string>

using namespace std;

class XmlAttribute {
private:
    string name;
    string value;
public:
    XmlAttribute();
    explicit XmlAttribute(const string& _name);
    string getName() const;
    string getValue() const;
    void setValue(const string& _value);
    string to_String() const;
};


#endif //XMLPARSER_XMLATTRIBUTE_H
