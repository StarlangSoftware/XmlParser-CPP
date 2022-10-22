//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#include "XmlAttribute.h"

/**
 * Constructor for xml attribute. Initializes the attribute.
 * @param[in] _name Name of the attribute
 * @return Allocated and initialized attribute
 */
XmlAttribute::XmlAttribute(const string& _name) {
    this->name = _name;
}

string XmlAttribute::getName() {
    return name;
}

string XmlAttribute::getValue() {
    return value;
}

void XmlAttribute::setValue(const string& _value) {
    this->value = _value;
}

string XmlAttribute::to_String(){
    return name + "=\"" + value + "\"";
}

XmlAttribute::XmlAttribute() = default;
