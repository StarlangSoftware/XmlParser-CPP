//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#include "XmlDocument.h"
#include "XmlTextType.h"
#include <fstream>
#include <iostream>

/**
 * Creates an empty xml document.
 * @param fileName Name of the xml file
 * @return Empty xml document. Xml file is not parsed yet.
 */
XmlDocument::XmlDocument(string fileName) {
    this->fileName = move(fileName);
    this->root = nullptr;
}

/**
 * Reads a token character by character from xml file.
 * @param previousChar Previous character read
 * @param nextChar The character after the token
 * @param spaceAllowed If true, space is allowed in the token, otherwise it is not allowed
 * @return Token read
 */
string XmlDocument::readToken(char previousChar, char* nextChar, bool spaceAllowed) {
    string buffer;
    char ch = previousChar;
    while ((ch != '\'') && (ch != '\"') && (ch != '=') && (ch != ' ' || spaceAllowed) && (ch != '/') && (ch != EOF) && (ch != '<') && (ch != '>')) {
        buffer += ch;
        inputStream.get(ch);
    }
    *nextChar = ch;
    return buffer;
}

/**
 * Parses a tag like <mytag> or </mytag>
 * @return Token read
 */
string XmlDocument::parseTag() {
    string token;
    char ch;
    inputStream.get(ch);
    if (ch == '/') {
        lastReadTokenType = XmlTokenType::XML_CLOSING_TAG_WITHOUT_ATTRIBUTES;
        inputStream.get(ch);
    } else {
        lastReadTokenType = XmlTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES;
    }
    token = readToken(ch, &ch, false);
    if (ch == '>' && lastReadTokenType == XmlTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES){
        lastReadTokenType = XmlTokenType::XML_OPENING_TAG_WITHOUT_ATTRIBUTES;
    }
    if (lastReadTokenType == XmlTokenType::XML_CLOSING_TAG_WITHOUT_ATTRIBUTES && ch != '>') {
        cout << "Wrong tag value";
        lastReadTokenType = XmlTokenType::XML_END;
        return nullptr;
    }
    else{
        return token;
    }
}

/**
 * Parses an attribute value like "attribute value" or 'attribute value'
 * @return Attribute value read
 */
string XmlDocument::parseAttributeValue() {
    string token;
    char ch;
    inputStream.get(ch);
    if (ch == '\'' || ch == '\"') {
        lastReadTokenType = XmlTokenType::XML_ATTRIBUTE_VALUE;
        return nullptr;
    }
    token = readToken(ch, &ch, true);
    if (ch != '\'' && ch != '\"') {
        cout << "Wrong attribute value";
        lastReadTokenType = XmlTokenType::XML_END;
        return nullptr;
    }
    lastReadTokenType = XmlTokenType::XML_ATTRIBUTE_VALUE;
    return token;
}

/**
 * Parses a tag like />
 * @return nullptr
 */
string XmlDocument::parseEmptyTag() {
    char ch;
    inputStream.get(ch);
    if (ch != '>') {
        cout << "Wrong tag value";
        lastReadTokenType = XmlTokenType::XML_END;
    } else {
        lastReadTokenType = XmlTokenType::XML_CLOSING_TAG_WITH_ATTRIBUTES;
    }
    return nullptr;
}

/**
 * Gets next token from file.
 * @return Token read. If not successful, returns nullptr.
 */
string XmlDocument::getNextToken() {
    char ch;
    string token;
    inputStream.get(ch);
    while (ch == ' ' || ch == '\t' || ch == '\n'){
        inputStream.get(ch);
    }
    switch (ch){
        case  '<':
            return parseTag();
        case '\"':
        case '\'':
            return parseAttributeValue();
        case  '/':
            return parseEmptyTag();
        case  '=':
            lastReadTokenType = XmlTokenType::XML_EQUAL;
            break;
        case  '>':
            lastReadTokenType = XmlTokenType::XML_OPENING_TAG_FINISH;
            return nullptr;
        case  EOF:
            lastReadTokenType = XmlTokenType::XML_END;
            return nullptr;
        default  :
            token = readToken(ch, &ch, true);
            lastReadTokenType = XmlTokenType::XML_TEXT;
            inputStream.putback(ch);
            return token;
    }
    return nullptr;
}

/**
 * Prints xml parse tree to an xml file
 * @param fileName Output file name
 */
void XmlDocument::print(string fileName) {
    ofstream outputStream;
    outputStream.open(fileName, ios::out);
    root->print(outputStream, 0);
    outputStream.close();
}

/**
 * Parses given xml document
 */
void XmlDocument::parse() {
    XmlTextType textType = XmlTextType::XML_TEXT_ATTRIBUTE;
    bool siblingClosed = false;
    string token;
    XmlAttribute xmlAttribute;
    XmlElement* sibling = nullptr, *current = nullptr, *parent = nullptr;
    inputStream.open(fileName, ios::in);
    token = getNextToken();
    while (lastReadTokenType != XmlTokenType::XML_END){
        switch (lastReadTokenType){
            case XmlTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES:
            case XmlTokenType::XML_OPENING_TAG_WITHOUT_ATTRIBUTES:
                current = new XmlElement(token, parent, lastReadTokenType == XmlTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES);
                if (parent) {
                    if (sibling && siblingClosed) {
                        sibling->setNextSibling(current);
                        sibling = current;
                    } else {
                        parent->setFirstChild(current);
                    }
                } else {
                    if (!root){
                        root = current;
                    }
                }
                parent = current;
                siblingClosed = false;
                if (lastReadTokenType == XmlTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES){
                    textType = XmlTextType::XML_TEXT_ATTRIBUTE;
                } else {
                    textType = XmlTextType::XML_TEXT_VALUE;
                }
                break;
            case XmlTokenType::XML_OPENING_TAG_FINISH:
                textType = XmlTextType::XML_TEXT_VALUE;
                siblingClosed = false;
                break;
            case XmlTokenType::XML_CLOSING_TAG_WITH_ATTRIBUTES:
                sibling = current;
                parent = current->getParent();
                textType = XmlTextType::XML_TEXT_VALUE;
                siblingClosed = true;
                break;
            case XmlTokenType::XML_CLOSING_TAG_WITHOUT_ATTRIBUTES:
                if (token == current->getName()) {
                    sibling = current;
                    parent = current->getParent();
                } else {
                    if (token == current->getParent()->getName()) {
                        sibling = parent;
                        parent = current->getParent()->getParent();
                        current = current->getParent();
                    }
                }
                siblingClosed = true;
                textType = XmlTextType::XML_TEXT_VALUE;
                break;
            case XmlTokenType::XML_ATTRIBUTE_VALUE:
                if (!token.empty()){
                    xmlAttribute.setValue(token);
                } else {
                    xmlAttribute.setValue("");
                }
                textType = XmlTextType::XML_TEXT_ATTRIBUTE;
                break;
            case XmlTokenType::XML_EQUAL:
                textType = XmlTextType::XML_TEXT_NOT_AVAILABLE;
                break;
            case XmlTokenType::XML_TEXT:
                if (textType == XmlTextType::XML_TEXT_ATTRIBUTE) {
                    xmlAttribute = XmlAttribute(token);
                    current->addAttribute(xmlAttribute);
                } else {
                    if (textType == XmlTextType::XML_TEXT_VALUE){
                        current->setPcData(token);
                    }
                }
                break;
            default:
                cout << "This token type not supported\n";
                break;
        }
        token = getNextToken();
    }
    inputStream.close();
}

XmlElement *XmlDocument::getFirstChild() {
    return root;
}
