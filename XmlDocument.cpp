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
 * @param extraAllowed If true, space or slash is allowed in the token, otherwise it is not allowed
 * @return Token read
 */
string XmlDocument::readToken(char previousChar, char* nextChar, bool extraAllowed, bool quotaAllowed) {
    string buffer;
    char ch = previousChar;
    while ((ch != '\'' || extraAllowed) && (ch != '\"' || quotaAllowed) && (ch != '=' || quotaAllowed) && (ch != ' ' || extraAllowed) && (ch != '/' || extraAllowed) && (ch != EOF) && (ch != '<') && (ch != '>')) {
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
    token = readToken(ch, &ch);
    if (ch == '>' && lastReadTokenType == XmlTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES){
        lastReadTokenType = XmlTokenType::XML_OPENING_TAG_WITHOUT_ATTRIBUTES;
    }
    if (lastReadTokenType == XmlTokenType::XML_CLOSING_TAG_WITHOUT_ATTRIBUTES && ch != '>') {
        cout << "Wrong tag value";
        lastReadTokenType = XmlTokenType::XML_END;
        return "";
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
    if (ch == '\"') {
        lastReadTokenType = XmlTokenType::XML_ATTRIBUTE_VALUE;
        return "";
    }
    token = readToken(ch, &ch, true);
    if (ch != '\"') {
        cout << "Wrong attribute value";
        lastReadTokenType = XmlTokenType::XML_END;
        return "";
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
    return "";
}

/**
 * Gets next token from file.
 * @return Token read. If not successful, returns empty string.
 */
string XmlDocument::getNextToken(XmlTextType xmlTextType) {
    char ch;
    string token;
    try{
        inputStream.get(ch);
        while (ch == ' ' || ch == '\t' || ch == '\n'){
            inputStream.get(ch);
        }
        switch (ch){
            case  '<':
                return parseTag();
            case '\"':
                if (xmlTextType == XmlTextType::XML_TEXT_VALUE){
                    token = readToken(ch, &ch, true, true);
                    lastReadTokenType = XmlTokenType::XML_TEXT;
                    inputStream.putback(ch);
                    return token;
                } else {
                    return parseAttributeValue();
                }
            case  '/':
                return parseEmptyTag();
            case  '=':
                if (xmlTextType == XmlTextType::XML_TEXT_VALUE){
                    token = readToken(ch, &ch, true, true);
                    lastReadTokenType = XmlTokenType::XML_TEXT;
                    inputStream.putback(ch);
                    return token;
                } else {
                    lastReadTokenType = XmlTokenType::XML_EQUAL;
                }
                break;
            case  '>':
                lastReadTokenType = XmlTokenType::XML_OPENING_TAG_FINISH;
                return "";
            default  :
                token = readToken(ch, &ch, true);
                lastReadTokenType = XmlTokenType::XML_TEXT;
                inputStream.putback(ch);
                return token;
        }
    } catch (ifstream::failure& e) {
        lastReadTokenType = XmlTokenType::XML_END;
        return "";
    }
    return "";
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
    inputStream.exceptions(ifstream::failbit | ifstream::badbit);
    try{
        inputStream.open(fileName, ios::in);
        token = getNextToken(textType);
        while (lastReadTokenType != XmlTokenType::XML_END){
            switch (lastReadTokenType){
                case XmlTokenType::XML_OPENING_TAG_WITH_ATTRIBUTES:
                case XmlTokenType::XML_OPENING_TAG_WITHOUT_ATTRIBUTES:
                    current = new XmlElement(token, parent);
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
                        replaceEscapeCharacters(token);
                        xmlAttribute.setValue(token);
                    } else {
                        xmlAttribute.setValue("");
                    }
                    current->addAttribute(xmlAttribute);
                    textType = XmlTextType::XML_TEXT_ATTRIBUTE;
                    break;
                case XmlTokenType::XML_EQUAL:
                    textType = XmlTextType::XML_TEXT_NOT_AVAILABLE;
                    break;
                case XmlTokenType::XML_TEXT:
                    if (textType == XmlTextType::XML_TEXT_ATTRIBUTE) {
                        xmlAttribute = XmlAttribute(token);
                    } else {
                        if (textType == XmlTextType::XML_TEXT_VALUE){
                            replaceEscapeCharacters(token);
                            current->setPcData(token);
                        }
                    }
                    break;
                default:
                    cout << "This token type not supported\n";
                    break;
            }
            token = getNextToken(textType);
        }
        inputStream.close();
    } catch (ifstream::failure& e) {
        cout << "Exception opening file " << fileName;
    }
}

XmlElement *XmlDocument::getFirstChild() {
    return root;
}

XmlDocument::~XmlDocument() {
    delete root;
}

void XmlDocument::replaceEscapeCharacters(string& token) {
    while (token.find("&quot;") != string::npos){
        token.replace(token.find("&quot;"), 6, "\"");
    }
    while (token.find("&amp;") != string::npos){
        token.replace(token.find("&amp;"), 5, "&");
    }
    while (token.find("&lt;") != string::npos){
        token.replace(token.find("&lt;"), 4, "<");
    }
    while (token.find("&gt;") != string::npos){
        token.replace(token.find("&lt;"), 4, ">");
    }
    while (token.find("&apos;") != string::npos){
        token.replace(token.find("&apos;"), 6, "'");
    }
}
