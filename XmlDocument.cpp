//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#include "XmlDocument.h"

XmlDocument::XmlDocument(string fileName) {
    this->fileName = move(fileName);
    this->root = nullptr;
}
