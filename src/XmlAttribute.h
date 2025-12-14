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
    [[nodiscard]] string getName() const;
    [[nodiscard]] string getValue() const;
    void setValue(const string& _value);
    [[nodiscard]] string to_String() const;
};


#endif //XMLPARSER_XMLATTRIBUTE_H
