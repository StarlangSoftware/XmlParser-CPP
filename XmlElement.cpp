//
// Created by Olcay Taner Yıldız on 12.10.2018.
//
#include<iostream>
#include<fstream>
#include "XmlElement.h"

/**
 * Constructor for xml element. Allocates memory and initializes an element.
 * @param name Name of the element
 * @param parent Parent of the Xml Element
 * @param hasAttributes If true, the element will have attributes, otherwise it won't have.
 * @return Constructed element
 */
XmlElement::XmlElement(string name, XmlElement* parent) {
    this->parent = parent;
    this->nextSibling = nullptr;
    this->firstChild = nullptr;
    this->name = move(name);
}

/**
 * Sets the value of an attribute to a given value
 * @param attributeName Name of the attribute
 * @param attributeValue New attribute value
 */
void XmlElement::setAttributeValue(string attributeName, string attributeValue) {
    for (XmlAttribute xmlAttribute : attributes){
        if (xmlAttribute.getName() == attributeName){
            xmlAttribute.setValue(attributeValue);
        }
    }
}

/**
 * Finds the attribute with the given name of an Xml element
 * @param[in] attributeName Name of the attribute
 * @return If the Xml element has such an attribute returns its value, otherwise it returns NULL
 */
string XmlElement::getAttributeValue(string attributeName) {
    for (XmlAttribute xmlAttribute : attributes){
        if (xmlAttribute.getName() == attributeName){
            return xmlAttribute.getValue();
        }
    }
    return "";
}

/**
 * Prints single xml element to the output xml file
 * @param outputStream File stream
 * @param level Level of the element
 */
void XmlElement::print(ofstream& outputStream, int level){
    int i;
    for (i = 0; i < level; i++){
        outputStream << "\t";
    }
    outputStream << "<";
    outputStream << name;
    for (XmlAttribute xmlAttribute : attributes){
        outputStream << " " << xmlAttribute.to_String();
    }
    if (firstChild == nullptr){
        if (pcData.empty()){
            outputStream << "/>\n";
        } else {
            outputStream << ">" << pcData << "</" << name << ">\n";
        }
    } else {
        outputStream << ">\n";
        firstChild->print(outputStream, level + 1);
        for (i = 0; i < level; i++){
            outputStream << "\t";
        }
        outputStream << "</" << name << ">\n";
    }
    if (nextSibling != nullptr){
        nextSibling->print(outputStream, level);
    }
}

XmlElement* XmlElement::getFirstChild() {
    return firstChild;
}

XmlElement* XmlElement::getNextSibling() {
    return nextSibling;
}

XmlElement* XmlElement::getParent() {
    return parent;
}

XmlElement::~XmlElement() {
    delete firstChild;
    delete nextSibling;
}

void XmlElement::setNextSibling(XmlElement* nextSibling) {
    this->nextSibling = nextSibling;
}

void XmlElement::setFirstChild(XmlElement* firstChild) {
    this->firstChild = firstChild;
}

string XmlElement::getName() {
    return name;
}

string XmlElement::getPcData() {
    return pcData;
}

void XmlElement::addAttribute(XmlAttribute xmlAttribute) {
    attributes.push_back(xmlAttribute);
}

void XmlElement::setPcData(string pcData) {
    this->pcData = move(pcData);
}

bool XmlElement::hasAttributes() {
    return !attributes.empty();
}
