#include "XmlDocument.h"

//
// Created by Olcay Taner Yıldız on 30.10.2018.
//
int main(){
    string fileName = "test.xml";
    XmlDocument xmlDocument(fileName);
    xmlDocument.parse();
}
