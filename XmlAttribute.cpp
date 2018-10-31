//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#include "XmlAttribute.h"

/**
 * Constructor for xml attribute. Initializes the attribute.
 * @param[in] name Name of the attribute
 * @return Allocated and initialized attribute
 */
XmlAttribute::XmlAttribute(string name) {
    this->name = move(name);
}

string XmlAttribute::getName() {
    return name;
}

string XmlAttribute::getValue() {
    return value;
}

void XmlAttribute::setValue(string value) {
    this->value = move(value);
}

string XmlAttribute::to_String(){
    return name + "=\"" + value + "\"";
}

XmlAttribute::XmlAttribute() {
}
